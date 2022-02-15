# Week 1 Tute

The class website can be found [here](https://cgi.cse.unsw.edu.au/~cs1521/22T1/).
It contains links to all the information you need, including course outline, lectures, lecture slides, tute questions, lab questions, etc.

The course forum can be found [here](https://edstem.org/au/courses/7762/discussion/).
If you have any questions about the content or any tute questions and lab exercises, please ask there.

### 2. Consider the following C program skeleton:
``` C
int  a;
char b[100];

int fun1() {
    int c, d;
    ...
}

double e;

int fun2() {
    int f;
    static int ff;
    ...
    fun1();
    ...
}

int g;

int main(void) {
    char h[10];
    int i;
    ...
    fun2()
    ...
}
```
### Now consider what happens during the execution of this program and answer the following:

### a. Which variables are accessible from within `main()`?
`a, b, e, g` are global variables which are above `main`

`h, i` are local variables

### b. Which variables are accessible from within `fun2()`?
`a, b, e` are global variables which are above `fun2`

`f, ff` are local variables

Note that `g` is a global variable but cannot be accessed as it is below `fun2`

### c. Which variables are accessible from within `fun1()`?
`a, b` are global variables which are above `fun1`

`c, d` are local variables

Note that `e, g` are global variables but cannot be accessed as they are below `fun1`

### d. Which variables are removed when `fun1()` returns?
`c, d`

### e. Which variables are removed when `fun2()` returns?
`f`

Sidenote: `static` variables in a function are like global variables but can only be accessed in the function which they are declared.
The first time a function is called, `static` variables will be initialised to 0 if there is not assignment in the same line as the declaration or whatever value it is assigned to be.
In further calls to the function, the variable will be updated and maintain the value it was between function calls.

### f. How long does the variable `f` exist during program execution?
It will exist whenever `fun2` exists.

When `fun2` calls `fun1`, `fun2` still exists on the stack under `fun1`'s stack so `f` will still exist.
However, when the program returns from `fun2`, `f` will no longer exist.

### g. How long does the variable `g` exist during program execution?
Since `g` is a global variable, it will exist for the entire duration of program execution.


### 3.Explain the differences between the properties of the variables s1 and s2 in the following program fragment:
``` C
#include <stdio.h>

char *s1 = "abc";

int main(void) {
    char *s2 = "def";
    // ...
}
```

### Where is each variable located in memory? Where are the strings located?
Memory is structured like this diagram

![0x0000( Code | Data | Heap ->         <- Stack ] 0xFFFF>)](week01.png)

+ Code contains the code which is being executed.
+ Data contains global variables and string literals
+ Heap contains variables which have been dynamically allocated and grows upwards
+ Stack contains information for the functions, including local variables and grows downwards

Since `s1` is a global variables, it is stored in the data segment.

Since `s2` is a local variable, it is stored in the stack.

The string literals are stored in the data segment.


### 4. Consider the following C program:
``` C
#include <stdio.h>

int main(void)
{
    int nums[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    for (int i = 0; i < 10; i++) {
        printf("%d\n", nums[i]);
    }
    return 0;
}
```
### This program uses a `for` loop to print each element in the array
### Rewrite this program using a [recursive function](https://en.wikipedia.org/wiki/Recursion_(computer_science))

A recursive function is a function that calls itself.

Any iterative loop (`for` or `while` loop) can be written as a recursive function.

The key elements of a recursive function are:
+ a base step (where the recursion stops)
+ actions which are taken at each specific stage of the recurstion
+ a recursive call (where the function calls itself)

```C
#include <stdio.h>


void print_array(int nums[], int index) {
    if (index == 10) {
        return;
    }

    printf("%d\n", nums[index]);
    print_array(nums, index + 1);
}


int main(void)
{
    int nums[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    print_array(nums, 0);
    return 0;
}
```


### 5. Consider the following C program:
``` C
#include <stdio.h>

int main(void) {
    char str[10];
    str[0] = 'H';
    str[1] = 'i';
    printf("%s", str);
    return 0;
}
```
### What will happen when the above program is compiled and executed?
`printf` expects strings to be terminated with a null-terminator (`'\0'`).

Since `str[2]` and beyond are uninitialised, `str[2]` probably won't be a null-terminator.

If the code is compiled with `dcc`, it will stop with an error because `str[2]` is uninitialised.

However, if the code is compiled with `gcc`, it will keep printing junk until it reaches a `'\0'` byte or the operating system kills it because of an illegal memory access.

### 6. How do you correct the program?
``` C
#include <stdio.h>

int main(void) {
    char str[10];
    str[0] = 'H';
    str[1] = 'i';
    str[2] = '\0';
    printf("%s", str);
    return 0;
}
```

### 7. For each of the following commands, describe what kind of output would be produced:
#### a) `gcc -E x.c`
Runs pre-processor, output will be modified C code in `stdout` with `#define` symbols replaced and all contents of `#include` files

#### b) `gcc -S x.c`
Generate `x.s` file which contains assembly code from the C code, will be different based on machine architecture.

#### c) `gcc -c x.c`
Generate `x.o` file which has relocatable machine code from the C code. Needs to be combined with a linker file with library functions to have executable.

#### d) `gcc x.c`
Produce executable file a.out which has all machine code needed to run the C code.

### Use the following simple C code as an example:
``` C
#include <stdio.h>
#define N 10

int main(void) {
    char str[N] = { 'H', 'i', '\0' };
    printf("%s\n", str);
    return 0;
}
```


### 8. What are `mipsy`, `spim`, `qtspim` & `xspim`.
They are the different MIPS emulators available on CSE.

`mipsy` is a new one that's been developed my Zac who is a course admin for 1521.
It's got nice features to help debug your programs.
However, it is pretty new so there may be bugs.
If you encounter any bugs, please post them on the course forum

`spim` is the main MIPS emulator that will be in use.
Make sure your code works with `spim` because that is what it will be run on.

`qtspim` and `xspim` are GUI versions of `spim` and can be nice to visualise what is going on with your code.

### 9. The MIPS processor has 32 general purpose 32-bit registers, referenced as $0 .. $31. Some of these registers are intended to be used in particular ways by programmers and by the system. For each of the registers below, give their symbolic name and describe their intended use:

| part | number | symbol | use |
|:---:|:---:|:---:|:---|
| a. | `$0` | `$zero` | will always be 0 |
| b. | `$1` | `$at` | assembler uses it, don't touch it! |
| c. | `$2` | `$v0` | first (of two) value register which stores return value from syscall or function |
| d. | `$4` | `$a0` | first (of four) argument register for syscall or function |
| e. | `$8` | `$t0` | first (of ten) temporary register to store values which will change between function calls |
| f. | `$16` | `$s0` | first (of eight) saved register to store values which will stay the same between function calls |
| g. | `$26` | `$k0` | first (of two) kernel register which the kernel uses, don't touch it! |
| h. | `$29` | `$sp` | stack pointer, top of the stack, we'll look at it in more detail in the coming weeks |
| i. | `$31` | `$ra` | return address |

Refer to the [SPIM guide](https://cgi.cse.unsw.edu.au/~cs1521/21T3/resources/spim-guide.html) for more details.


### 10. Translate this C program to MIPS assembler
```C
// print the square of a number
#include <stdio.h>

int main(void) {
    int x, y;
    printf("Enter a number: ");
    scanf("%d", &x);
    y = x * x;
    printf("%d\n", y);
    return 0;
}
```
### Store variable x in register $t0 and store variable y in register $t1.

```MIPS
    .text
main:
    li  $v0, 4      # load number 4 into $v0 to indicate print string syscall
    la  $a0, prompt # load the address of prompt into $a0 so we can print it
    syscall

    li  $v0, 5      # load number 5 into $v0 to indicate read int syscall
    syscall

    move    $t0, $v0    # copy value from register $v0 into register $t0
    mul $t1, $t0, $t0   # multiplies value from $t0 and $t0 and store into $t1

    li  $v0, 1      # load number 1 into $v0 to indicate print int syscall
    move    $a0, $t1    # copy value from register $t1 into register $a0
    syscall

    li  $v0, 11     # load number 11 into $v0 to indicate print char syscall
    li  $a0, '\n'   # load newline character into register $a0
    syscall

    li  $v0, 0  # store 0 in return value register to return
    jr  $ra     # return from function


    .data
prompt:
    .asciiz "Enter a number: "
```

___
## Command Line Arguments Example
```C
#include <stdio.h>

// argc is number of command line arguments
// argv is array of strings, each string is a command line argument

// char **argv or char argv[][] or char *argv[] are equivalent
// (all arrays of strings)

// ./hello how are you
// argc: 4
// argv[0] = "./hello"
// argv[1] = "how"
// argv[2] = "are"
// argv[3] = "you"

int main(int argc, char *argv[]) {


    return 0;
}
```
