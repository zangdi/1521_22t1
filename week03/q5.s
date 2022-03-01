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
