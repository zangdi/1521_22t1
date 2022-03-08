	.text
main:
main_prologue:
	begin
	push	$ra		# save $ra since we need to call sum4

main_body:
	li	$a0, 11
	li	$a1, 13
	li	$a2, 17
	li	$a3, 19
	jal	sum4		# calls sum4(11, 13, 17, 19)

	move	$a0, $v0	# stores z in $a0
	li	$v0, 1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall

main_epilogue:
	pop	$ra
	end

	jr	$ra


sum4:
sum4_prologue:
	# need to save variables: c, d, e, f
	begin
	push	$ra		# save $ra since we need to call sum2
	push	$s0		# store c in $s0
	push	$s1		# store d in $s1
	push	$s2		# store e in $s2
	push	$s3		# store f in $s3

	move	$s0, $a2	# move c into $s0
	move	$s1, $a3	# move d into $s1

sum4_body:
	jal	sum2		# call sum2(a, b)

	move	$s2, $v0	# stores e in $s2

	move	$a0, $s0
	move	$a1, $s1
	jal	sum2		# call sum2(c, d)

	move	$s3, $v0	# stores f in $s3

	move	$a0, $s2
	move	$s1, $s3
	jal	sum2		# calls sum2(e, f)

sum4_epilogue:
	pop	$s3
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end

	jr	$ra


sum2:
	addi	$v0, $a0, $a1
	jr	$ra
