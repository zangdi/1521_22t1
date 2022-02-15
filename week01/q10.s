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