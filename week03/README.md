# Week 3 Tute

___
### 2. If the data segment of a particular MIPS program starts at the address 0x10000020, then what addresses are the following labels associated with, and what value is stored in each 4-byte memory cell?
``` assembly
    .data
a:  .word   42
b:  .space  4
c:  .asciiz "abcde"
    .align  2
d:  .byte   1, 2, 3, 4
e:  .word   1, 2, 3, 4
f:  .space  1
```


| Address | Label | Contents |
|:---:|:---:|:---:|
| 0x10000020 | a | 42 |
| 0x10000024 | b | ???? |
| 0x10000028 | c | 'a', 'b', 'c', d' |
| 0x1000002C | - | 'e', '\0', ?, ? |
| 0x10000030 | d | 1, 2, 3, 4 |
| 0x10000034 | e | 1 |
| 0x10000038 | - | 2 |
| 0x1000003C | - | 3 |
| 0x10000040 | - | 4 |
| 0x10000044 | f | ? ??? |


___
### 3. Give MIPS directives to represent the following variables:
### Assume that we are placing the variables in memory, at an appropriately-aligned address, and with a label which is the same as the C variable name.
| part | C | MIPS |
|:---:|:---|:---|
| a | `int u;` | `u:    .space  4`
| b | `int v = 42;` | `v:   .word   42`
| c | `char w;` | `w:   .space  1`
| d | `char x = 'a';` | `x: .byte   'a'`
| e | `double y;` | `y: .space  8`
| f | `int z[20];` | `z:    .space  80`


___
### 4. Consider the following memory state:
```
Address       Data Definition
0x10010000    aa:  .word 42
0x10010004    bb:  .word 666
0x10010008    cc:  .word 1
0x1001000C         .word 3
0x10010010         .word 5
0x10010014         .word 7
```
### What address will be calculated, and what value will be loaded into register $t0, after each of the following statements (or pairs of statements)?


#### a)
```
la   $t0, aa
```
`$t0 = 0x10010000`

#### b)
```
lw   $t0, bb
```
`$t0 = 666`

#### c)
```
lb   $t0, bb
```

#### d)
```
lw   $t0, aa+4
```
`$t0 = 666`

#### e)
```
la   $t1, cc
lw   $t0, ($t1)
```
`$t1 = 0x10010008`

`$t0 = 1`

#### f)
```
la   $t1, cc
lw   $t0, 8($t1)
```
`$t1 = 0x10010008`

`$t0 = 5`

#### g)
```
li   $t1, 8
lw   $t0, cc($t1)
```
`$t1 = 8`

`$t0 = 5`

#### h)
```
la   $t1, cc
lw   $t0, 2($t1)
```
`$t1 = 0x10010008`


___
### 5. Translate this C program to MIPS assembler
``` C
#include <stdio.h>

int main(void) {
    int i;
    int numbers[10] = {0};

    i = 0;
    while (i < 10) {
        scanf("%d", &numbers[i]);
        i++;
    }

    i = 9;
    while (i >= 0) {
        printf("%d\n", numbers[i]);
        i--;
    }
}
```

C Using `goto`
```C
#include <stdio.h>

int main(void) {
    int i;
    int numbers[10] = {0};

    i = 0;

loop0:
loop0_condition:
    if (i >= 10) goto end0;
loop0_body:
    scanf("%d", &numbers[i]);
loop0_increment:
    i++;
loop0_repeat:
    goto loop0;

end0:
    i = 9;

loop1:
    if (i < 0) goto end1;
    printf("%d\n", numbers[i]);
    i--;
    goto loop1;

end1:
    return 0;
}
```

MIPS
```MIPS
        .text
main:
        li      $t0, 0  # store i = 0 in $t0

loop0:
        bge     $t0, 10, end0   # if (i >= 10) stop loop

        li      $v0, 5  # store 5 in $v0 to read int
        syscall
        move    $t2, $v0

        mul     $t1, $t0, 4     # calculates how much higher than array we need
        sw      $t2, numbers($t1)       # calculate address of numbers[i] and store $t2 into &numbers[i]

        addi    $t0, $t0, 1     # i++;

        b       loop0

end0:

        li      $t0, 9  # store i = 9 in $t0
loop1:
        bltz    $t0, end1

        mul     $t1, $t0, 4
        la      $t2, numbers
        add     $t3, $t2, $t1   # calculates address of numbers[i]
        lw      $t4, ($t3)      # grab value from &numbers[i] and store into $t4

        li      $v0, 1
        move    $a0, $t4
        syscall

        addi    $t0, $t0, -1    # i--;

        j       loop1

end1:
        li      $v0, 0
        jr      $ra


        .data:
numbers:
        .word   0, 0, 0, 0, 0, 0, 0, 0, 0, 0
```
