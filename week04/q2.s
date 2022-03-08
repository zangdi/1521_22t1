	.text
main:
	li	$t0, 0		# store row in $t0

loop0:
	bge	$t0, 6, end0	# if (row >= 6) goto end0;

	li	$t1, 0		# store col in $t1

loop1:
	bge	$t1, 12, end1	# if (col >= 12) goto end1;

	li	$v0, 11

	mul	$t2, $t0, 12	# calculate how much flag[row] is higher than flag
	add	$t3, $t2, $t1	# calculate how much flag[row][col] is higher than flg
	lb	$a0, flag($t3)	# load value from flag[row][col] into $t4

	syscall			# printf("%c", flag[row][col]);


	addi	$t1, $t1, 1
	b	loop1

end1:
	li	$v0, 11
	li	$a0, '\n'
	syscall

	addi	$t0, $t0, 1
	b	loop0

end0:
	jr	$ra


	.data
flag:
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
