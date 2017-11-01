.data
	msg: .asciiz "Hello, world!"
.text
	#Print the message
	la $a0, msg #put the messege address in a0
	li $v0, 4 # put the "print string" syscall code in a0
	# Part 1
	la $t0, 7($a0) # Capitalizes w
	li $t0, 0x00000057
	sb $t0, 7($a0)
	
	la $t0, 5($a0) # Replaces commma
	li $t0, 0x0000003a
	sb $t0, 5($a0)
	
	la $t0, 12($a0)
	li $t0, 0x0000002e
	sb $t0, 12($a0)
	
	la $t0, 13($a0)
	li $t0, '\n'
	sb $t0, 13($a0)
	
	syscall
	syscall
	
	# terminate the program
	li $v0, 10
	syscall
	
	