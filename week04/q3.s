	.text

	# max gets called with 2 arguments:
	# $a0: int a[];
	# $a1: int length;
max:
max_prologue:
	# save: first_element
	begin
	push	$ra		# need to call function
	push	$s0		# save first_element in $s0
	push	$s1		# save a into $s1
	push	$s2		# save length into $s2

	move	$s1, $a0
	move	$s2, $a1

max_body:
	lw	$s0, ($a0)	# stores first_element = a[0] in $s0

	bne	$a1, 1, length_greater;
	move	$v0, $s0	# store first_elemnt in $v0 to return
	b	max_epilogue	# going to return

length_greater:
	addi	$a0, $a0, 4	# address of a[1]
	addi	$a1, $a1, -1	# length - 1
	jal	max		# call max(&a[1], length - 1)
				# max_so_far is stored in $v0

	ble	$s0, $v0, max_epilogue
	move	$v0, $s0	# stores first_element in return register

max_epilogue:
	# clean up stack
	pop	$s2		# restore $s2
	pop	$s1		# restore $s1
	pop	$s0		# restore $s0
	pop	$ra		# restore $ra
	end

	jr	$ra		# actually returns
