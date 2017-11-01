.data
	msg_enterNumber1: .asciiz "Enter a number: "
	msg_enterNumber2: .asciiz "Enter another number: "
	msg_sum:          .asciiz "The sum is: "
	
.text
	# print first message.
	la $a0, msg_enterNumber1
	li $v0, 4
	syscall
	
	# get first number.
	li $v0, 5
	syscall
	
	# stash first number in $s0.
	move $s0, $v0

	# print second message.
	la $a0, msg_enterNumber2
	li $v0, 4
	syscall
		
	# get second number.
	li $v0, 5
	syscall
	
	# add first and second numbers, and store back in #$s0
	add $s0, $s0, $v0
	
	# print final message
	la $a0, msg_sum
	li $v0, 4
	syscall
	
	# print sum
	move $a0, $s0
	li $v0, 1
	syscall
	
	# exit program.
	li $v0, 10
	syscall