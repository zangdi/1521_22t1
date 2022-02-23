# Week 2 Tute


___
### 2. Often when writing large MIPS programs, you will make accidental errors that cause your program to misbehave.
### Discuss what tools are available to help debug broken MIPS code.

Try `1521 mipsy` on CSE. It is a command line MIPS emulator which can be used for debugging. Use `help` to learn more about the commands.

`QTspim` is a graphical MIPS emulator which can be used for debugging.

___
### 5. Translate this C program so it uses goto rather than if/else.
### Then translate it to MIPS assembler.
``` C
#include <stdio.h>

int main(void) {
    int x, y;
    printf("Enter a number: ");
    scanf("%d", &x);

    if (x > 46340) {
        printf("square too big for 32 bits\n");
    } else {
        y = x * x;
        printf("%d\n", y);
    }

    return 0;
}
```

Translated C
```C
#include <stdio.h>

int main(void) {
    int x, y;
    printf("Enter a number: ");
    scanf("%d", &x);

    if (x > 46340) goto square_too_big;
    y = x * x;
    printf("%d\n", y);
    goto end;

square_too_big:
    printf("square too big for 32 bits\n");

end:
    return 0;
}

```

MIPS
```MIPS
    .text:
main:
    li  $v0, 4      # indicate print string
    la  $a0, prompt # load prompt into $a0 for printing
    syscall

    li  $v0, 5      # indicate read integer
    syscall
    move    $t0, $v0    # store x in $t0

    bgt $t0, 46340, square_too_big  # jump to square_too_big if too big
    mul $t1, $t0, $t0   # store y in $t1

    li  $v0, 1      # indicate print integer
    move    $a0, $t1    # moves y into $a0 for printing
    syscall

    li  $v0, 11     # indicate print character
    li  $a0, '\n'   # load '\n' into $a0 for printing
    syscall

    j   end         # jumps to the end


square_too_big:
    li  $v0, 4
    la  $a0, too_big_string
    syscall

end:
    li  $v0, 0      # loading up 0 to return
    jr  $ra


    .data
prompt:
    .asciiz "Enter a number: "

too_big_string:
    .asciiz "square too big for 32 bits\n"
```


___
### 6. Translate this C program so it uses goto rather than if/else.
### Then translate it to MIPS assembler.
``` C
#include <stdio.h>

int main(void) {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    if (x > 100 && x < 1000) {
        printf("medium\n");
    } else {
        printf("small/big\n");
    }
}
```
### Consider this alternate version of the above program, use its approach to produce simpler MIPS assembler.
``` C
#include <stdio.h>

int main(void) {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    char *message = "small/big\n";
    if (x > 100 && x < 1000) {
        message = "medium";
    }

    printf("%s", message);
}
```

Translated C
```C
#include <stdio.h>

int main(void) {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    char *message = "small/big\n";
    if (x <= 100) goto end;
    if (x >= 1000) goto end;
    message = "medium";


end:
    printf("%s", message);
}
```

MIPS
```MIPS
    .text
main:
    li  $v0, 4      # indicate print string
    la  $a0, prompt # load prompt into $a0 for printing
    syscall

    li  $v0, 5      # indicate read integer
    syscall
    move    $t0, $v0    # store x in $t0

    la  $t1, small_big_string   # store message in register $t1
    ble $t0, 100, end   # jump to end if x <= 100
    bge $t0, 1000, end  # jump to end if x >= 1000

    la  $t1, medium     # store medium message in register $t1

end:
    li  $v0, 4      # indicate print string
    move    $a0, $t1    # store message in $a0 for printing
    syscall

    jr  $ra


    .data
prompt:
    .asciiz "Enter a number: "

small_big_string:
    .asciiz "small/big"

medium_string:
    .asciiz "medium"
```

___
### 7. Translate this C program so it uses goto rather than if/else.
### Then translate it to MIPS assembler.
``` C
#include <stdio.h>

int main(void) {
    for (int x = 24; x < 42; x += 3) {
        printf("%d\n",x);
    }
}
```

Translated C
```C
#include <stdio.h>

int main(void) {
    int x = 24;

loop:
    if (x >= 42) goto end;
    printf ("%d\n", x);
    x += 3;
    goto loop;

end:
    return 0;
}
```

MIPS
```MIPS
    .text
main:
    li  $t0, 24     # store x in register $t0

loop:
    bge $t0, 42, end    # stop looping if x >= 42

    li  $v0, 1      # store 1 in $v0 to print integer
    move    $a0, $t0    # load x into $a0 for printing
    syscall

    li  $v0, 11     # store 11 in $v0 to print character
    li  $a0, '\n'   # load '\n' into $a0 for printing
    syscall

    addi    $t0, $t0, 3     # x += 3
    j   loop

end:
    li  $v0, 0
    jr  $ra
```

___
### 8. Translate this C program so it uses goto rather than if/else.
### Then translate it to MIPS assembler.
``` C
// print a triangle
#include <stdio.h>

int main (void) {
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    };
    return 0;
}
```

Translated C
```C
// print a triangle
#include <stdio.h>

int main (void) {
    int i = 1;

loop0:
    if (i > 10) goto end0;
    int j = 0;

loop1:
    if (j >= i) goto end1;
    printf("*");
    j++;
    goto loop1;

end1:
    printf("\n");
    i++;
    goto loop0;

end0:
    return 0;
}
```

MIPS
```MIPS
    .text
main:
    li  $t0, 1      # store i in $t0

loop0:
    bgt $t0, 10, end0   # jump to end0 if i > 10
    li  $t1, 0      # store j in $t1

loop1:
    bge $t1, $t0, end1  # jump to end1 if j >= i

    li  $v0, 11     # store 11 in $v0 to print character
    li  $a0, '*'    # store * in $a0 for printing
    syscall

    addi    $t1, $t1, 1 # j++
    b   loop1

end1:
    li  $v0, 11     # store 11 in $v0 to print character
    li  $a0, '\n'    # store '\n' in $a0 for printing
    syscall

    addi    $t0, $t0, 1 # i++
    b   loop0

end0:
    li  $v0, 0      # load 0 for returning
    jr  $ra         # return 0
```

