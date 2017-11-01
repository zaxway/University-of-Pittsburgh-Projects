# lab3 starter code
# 9/22/16

.data
	welcome: .asciiz "Welcome to the matter classification program!\n" 
	q1:  .asciiz "Can substances within the sample be separated by physical means? (no = 0, yes = 1)\n"
	q2a:  .asciiz "Does the sample contain more than one kind of atom? (no = 0, yes = 1)\n" 
	q2b:  .asciiz "Is the distribution of substances nonuninform throughout? (no = 0, yes = 1)\n" 
	pure_output: .asciiz "This is a pure substance.\n"
	mix_output: .asciiz "This is a mixture.\n"
	element_output: .asciiz "It is an element.\n"
	compound_output: .asciiz "It is a compound.\n"
	homogeneous_output: .asciiz "It is homogeneous.\n"
	heterogeneous_output: .asciiz "It is heterogeneous.\n"


.text
	# print welcome message and ask first question
	li $v0, 4
	la $a0, welcome
	syscall
	la $a0, q1
	syscall
	li $v0, 5
	syscall
	

	# store result in bit 1 of $t0 (where bit 0 = Least Significant Bit)
	add $t0, $zero, $v0
	sll $t0, $t0, 1

	# ask second question
	bne $v0, $zero, q1_yes
	q1_no: la $a0, q2a
	j q2_ask
	q1_yes: la $a0, q2b
	q2_ask: li $v0, 4
	syscall
	li $v0, 5
	syscall

	# store result in bit 0 of $t0 (the LSB)
	or $t0, $t0, $v0

	## add new instructions here
	
	andi $s0, $t0, 2
	beq $t0, $zero, pure1
	la $a0, mix_output
	li $v0, 4
	syscall
	 
	
	j mixed
	
	pure1: 
		li $v0, 4
		la $a0, pure_output
		syscall
	
	andi $s0, $t0, 1
	beq $t0, $zero, pure2
	la $a0, compound_output
	li $v0, 4
	syscall
	
	pure2:
		li $v0, 4
		la $a0, element_output
		syscall
	
	j end

	
	mixed:
		andi $s0, $t0, 1
		beq $t0, $zero, mix1
		la $a0, homogeneous_output
		li $v0, 4
		syscall
		
		mix1:
			li $v0, 4
			la $a0, heterogeneous_output
			syscall




	end:


	# exit
	addi $v0, $zero, 10
	syscall