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
