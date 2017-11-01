.data

	msg: .asciiz "Please enter a non-negative integer: "
.text

.globl main
main:
	li $v0, 4
	la $a0, msg
	syscall
	li $v0, 5
	move $a0, $v0
	syscall
	jal fib
	
fib:
	beq $a0, 0, blockA
	
	block A:
		jr $ra
	
	