	# Print the number
	li $a0, 62345 # Put the number in a0
	li $v0, 1     # Put the "print int" syscall code in v0
	syscall       # Call it!
	
	# Terminate the program
	li $v0, 10 # Put the "exit" syscall code in v0
	syscall    # Call it!