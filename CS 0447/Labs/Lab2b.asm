# Lab2b.asm

.text
	# set $v0 to syscall code
	li $v0, 1
	
	# Use a loop to print all digits 0-9 to the I/O window 
	add $t0, $zero, $zero # initialize $t0 --> acts as a counter
	addi $t1, $zero, 10 # initialize $t1 --> termination condition
	
	top:
	slti $t3, $t0, 10 # just know that $t3 is a boolean that returns 0 or 1 only for true and false
	beq $t3, 0, end #if it equals 0, end the program
	
	add $a0, $t0, $zero # set syscall argument to the value of $t0
	
	syscall #print to screen
	
	addi $t0, $t0, 3 #increment to $t0
	bne $t0, $t1, top # do not branch if $t0 = termination condition
	
end:	# Terminate the program
	li $v0, 10
	syscall
