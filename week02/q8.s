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
