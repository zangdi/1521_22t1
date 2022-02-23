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
