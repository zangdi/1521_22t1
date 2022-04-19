# Week 10 Tute


### 1.How is the assignment going?
### Does anyone have hints or advice for other students?
### Has anyone discovered interesting cases that have to be handled?



___
### 2. What is the difference between concurrency and parallelism?
Concurrency is running code "at the same time". It does not necessarily have to all run simultaenously. It might just be running one thread for a bit of time, then running another thread.

Parallelism means actually running code simultaneously. Multiple cores are needed to do this.

___
### 3. How can we make our programs concurrent in C?
Use POSIX threads

Remember to compile with the `-pthread` flag
```sh
dcc -pthread program.c -o program
```

For details about the types, functions and macros available with `pthread.h`, look at [`man 7posix pthread.h`](https://man7.org/linux/man-pages/man0/pthread.h.0p.html).

___
### 4. Write a C program that creates a thread that infinitely prints some message provided by main (eg. `"Hello\n"`), while the main (default) thread infinitely prints a different message (eg. `"there!\n"`).
```C
#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {
    char *string = data;

    while (1) {
        printf("%s\n", string);
    }

    return NULL;
}

int main(void) {
    // create a thread
    pthread_t thread;
    char *there = "there!";
    pthread_create(&thread, NULL, thread_run, there);

    pthread_t thread2;
    char *world = "world";
    pthread_create(&thread2, NULL, thread_run, world);

    // print out hello infinitely
    while (1) {
        printf("Hello\n");
    }
}
```

___
### 5. The following C program attempts to say hello from another thread:
``` C
#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {
    printf("Hello from thread!\n");

    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_create(
        &thread,    // the pthread_t handle that will represent this thread
        NULL,       // thread-attributes -- we usually just leave this NULL
        thread_run, // the function that the thread should start executing
        NULL        // data we want to pass to the thread -- this will be
                    // given in the `void *data` argument above
    );

    return 0;
}
```
### However, when running this program after compiling with clang, the thread doesn't say hello.

``` sh
$ clang -pthread program.c -o program
$ ./program
$ ./program
$ ./program
```
### Why does our program exhibit such behaviour?

### How can we fix it?

Main thread finishes before created thread had a chance to print!

Use `pthread_join` to wait for a thread to finish:
```C
#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {
    printf("Hello from thread!\n");

    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_create(
        &thread,    // the pthread_t handle that will represent this thread
        NULL,       // thread-attributes -- we usually just leave this NULL
        thread_run, // the function that the thread should start executing
        NULL        // data we want to pass to the thread -- this will be
                    // given in the `void *data` argument above
    );

    pthread_join(thread, NULL);

    return 0;
}
```

___
### 6. Concurrency can allow our programs to perform certain actions simultaneously that were previously tricky for us to do as COMP1521 students.

### For example, with our current C knowledge, we cannot execute any code while waiting for input (with, for example, `scanf`, `fgets`, etc.).

### Write a C program that creates a thread which infinitely prints the message `"feed me input!\n"` once per second ([`sleep`](http://man7.org/linux/man-pages/man3/sleep.3.html)), while the main (default) thread continuously reads in lines of input, and prints those lines back out to stdout with the prefix: `"you entered: "`.

```C
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_LEN 1024

void *thread_run(void *data) {
    while (1) {
        printf("feed me input!\n");
        sleep(1);
    }

    return 0;
}

int main(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_run, NULL);

    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, stdin)) {
        printf("you entered: %s", line);
    }

    pthread_cancel(thread);

    return 0;
}
```

___
### 7. The following C program attempts to increment a global variable in two different threads, 5000 times each.
``` C
#include <stdio.h>
#include <pthread.h>

int global_total = 0;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sleep for 1 nanosecond
        nanosleep (&(struct timespec){.tv_nsec = 1}, NULL);
        
        // increment the global total by 1
        global_total++;
    }

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, add_5000_to_counter, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, add_5000_to_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // if program works correctly, should print 10000
    printf("Final total: %d\n", global_total);
}
```
### Since the global starts at 0, one may reasonably assume the value would total to 10000.

### However, when running this program, it often gives differing values each individual execution:
``` sh
$ dcc -pthread program.c -o program
$ ./program
Final total: 9930
$ ./program
Final total: 9983
$ ./program
Final total: 9994
$ ./program
Final total: 9970
$ ./program
Final total: 10000
$ ./program
Final total: 9996
$ ./program
Final total: 9964
$ ./program
Final total: 9999
```
### Why does our program exhibit such behaviour?

Incrementing a variable:
- Take value from memeory and store in register
- Increment register
- Store value from register back into memory

#### Example execution
Thread 1:
- takes value of global_total to be 0

Thread 2:
- takes value of global_total to be 0
- stores value of global_total as (global_total + 1) 1

Thread 1:
- store value of global total as (global_total + 1) 1

Then the increment that thread 2 does effectively doesn't happen :(

#### Possible Solutions
Option 1 (Use a lock):
- Grab the lock
- Take value from memeory and store in register
- Increment register
- Store value from register back into memory
- Release the lock

Option 2 (Use atomic types):
- Increment in 1 step

___
### 8. How can we use "mutual exclusion" to fix the previous program?
```C
#include <stdio.h>
#include <pthread.h>

int global_total = 0;
pthread_mutex_t global_total_mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sleep for 1 nanosecond
        nanosleep (&(struct timespec){.tv_nsec = 1}, NULL);
        
        // increment the global total by 1
        pthread_mutex_lock(&global_total_mutex);
        global_total++;
        pthread_mutex_unlock(&global_total_mutex);
    }

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, add_5000_to_counter, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, add_5000_to_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // if program works correctly, should print 10000
    printf("Final total: %d\n", global_total);
}
```

___
### 9. How can we use atomic types to fix the previous program?
```C
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int global_total = 0;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sleep for 1 nanosecond
        nanosleep (&(struct timespec){.tv_nsec = 1}, NULL);
        
        // increment the global total by 1
        // global_total++;  // This is also atomic
        // global_total -= 1;   // This is atomic
        // global_total = global_total + 1; // This is not atomic

        atomic_fetch_add(&global_total, 1);
    }

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, add_5000_to_counter, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, add_5000_to_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // if program works correctly, should print 10000
    printf("Final total: %d\n", global_total);
}
```
___
### 10. Without writing code, what is a deadlock, and what does a simple case look like?
Locks: A, B, C

- Thread 1: has lock A, wants lock B
- Thread 2: has lock B, wants lock C
- Thread 3: has lock C, wants lock A

Deadlock: all locks are taken, but threads need another lock

How can we fix this?
- Establish a global ordering of locks, e.g. if you need multiple locks, acquire A, then B, then C

Then, same situation would be

- Thread 1: has lock A, wants lock B
- Thread 2: has lock B, wants lock C
- Thread 3: wants lock A and lock C

Then the program can run to completion:
- Thread 2: can get lock C and then return locks C and B when it finishes
- Thread 1: can get lock B and then return locks B and A when it finishes
- Thread 3: can get lock A and C and then return C and A when it finishes
