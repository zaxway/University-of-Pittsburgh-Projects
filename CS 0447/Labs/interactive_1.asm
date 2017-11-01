.text
	# get first number.
	li $v0, 5
	syscall
	
	# stash first number in $s0.
	move $s0, $v0
	
	# get second number.
	li $v0, 5
	syscall
	
	# add first and second numbers, print result.
	add $a0, $s0, $v0
	li $v0, 1
	syscall
	
	# exit program.
	li $v0, 10
	syscall