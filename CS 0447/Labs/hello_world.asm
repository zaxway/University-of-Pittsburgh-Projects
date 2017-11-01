.data
	msg: .asciiz "Please enter an integer: "
	msg_2: .asciiz "Please eneter second integer: "
	msg_3: .asciiz "Your result from subraction"
.text
	# Print the message
	la $a0, msg # Put the message address in a0
	li $v0, 4   # Put the "print string" syscall code in v0
	syscall     # Call it!
	
	#user enters in integer
	la $v0, 5
	syscall #Call the code
	
	move $s0, $v0
	
	# Print second message
	la $a0, msg_2
	li $v0, 4
	syscall 
	
	# User enters in the integer
	la $v0, 5
	syscall
	
	# subract
	sub $s0, $s0, $v0
	
	# Print subraction result
	la $a0, msg_3
	li $v0, 4
	syscall
	
	move $a0, $s0
	la $v0, 1
	syscall
	
	
	
	# Terminate the program
	li $v0, 10  # Put the "exit" syscall code in v0
	syscall     # Call it!
