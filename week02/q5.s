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
