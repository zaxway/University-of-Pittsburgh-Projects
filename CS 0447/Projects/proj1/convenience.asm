.include "syscalls.asm"

.macro print_int %reg
	move $a0, %reg
	li $v0, sys_printInt
	syscall
.end_macro

.macro print_int_binary %reg
	move $a0, %reg
	li $v0, sys_printBin
	syscall
.end_macro

.macro print_int_hex %reg
	move $a0, %reg
	li $v0, sys_printHex
	syscall
.end_macro

.macro print_string %str
	la $a0, %str
	li $v0, sys_printString
	syscall
.end_macro

.macro print_char %c
	li $a0, %c
	li $v0, sys_printChar
	syscall
.end_macro

.macro print_char_reg %reg
	move $a0, %reg
	li $v0, sys_printChar
	syscall
.end_macro

.macro read_int %reg
	li $v0, sys_readInt
	syscall
	move %reg, $v0
.end_macro

.macro exit
	li $v0, sys_exit
	syscall
.end_macro

.macro exit %code
	li $a0, %code
	li $v0, sys_exit2
	syscall
.end_macro


.macro inc %reg
	addi %reg, %reg, 1
.end_macro

.macro dec %reg
	addi %reg, %reg, -1
.end_macro

.macro enter
	addi $sp, $sp, -4
	sw $ra, 0($sp)
.end_macro

.macro enter %r1
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw %r1, 4($sp)
.end_macro

.macro enter %r1, %r2
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw %r1, 4($sp)
	sw %r2, 8($sp)
.end_macro

.macro enter %r1, %r2, %r3
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw %r1, 4($sp)
	sw %r2, 8($sp)
	sw %r3, 12($sp)
.end_macro

.macro enter %r1, %r2, %r3, %r4
	addi $sp, $sp, -20
	sw $ra, 0($sp)
	sw %r1, 4($sp)
	sw %r2, 8($sp)
	sw %r3, 12($sp)
	sw %r4, 16($sp)
.end_macro

.macro enter %r1, %r2, %r3, %r4, %r5
	addi $sp, $sp, -24
	sw $ra, 0($sp)
	sw %r1, 4($sp)
	sw %r2, 8($sp)
	sw %r3, 12($sp)
	sw %r4, 16($sp)
	sw %r5, 20($sp)
.end_macro

.macro enter %r1, %r2, %r3, %r4, %r5, %r6
	addi $sp, $sp, -28
	sw $ra, 0($sp)
	sw %r1, 4($sp)
	sw %r2, 8($sp)
	sw %r3, 12($sp)
	sw %r4, 16($sp)
	sw %r5, 20($sp)
	sw %r6, 24($sp)
.end_macro

.macro leave
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
.end_macro

.macro leave %r1
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	addi $sp, $sp, 8
	jr $ra
.end_macro

.macro leave %r1, %r2
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	lw %r2, 8($sp)
	addi $sp, $sp, 12
	jr $ra
.end_macro

.macro leave %r1, %r2, %r3
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	lw %r2, 8($sp)
	lw %r3, 12($sp)
	addi $sp, $sp, 16
	jr $ra
.end_macro

.macro leave %r1, %r2, %r3, %r4
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	lw %r2, 8($sp)
	lw %r3, 12($sp)
	lw %r4, 16($sp)
	addi $sp, $sp, 20
	jr $ra
.end_macro

.macro leave %r1, %r2, %r3, %r4, %r5
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	lw %r2, 8($sp)
	lw %r3, 12($sp)
	lw %r4, 16($sp)
	lw %r5, 20($sp)
	addi $sp, $sp, 24
	jr $ra
.end_macro

.macro leave %r1, %r2, %r3, %r4, %r5, %r6
	lw $ra, 0($sp)
	lw %r1, 4($sp)
	lw %r2, 8($sp)
	lw %r3, 12($sp)
	lw %r4, 16($sp)
	lw %r5, 20($sp)
	lw %r6, 24($sp)
	addi $sp, $sp, 28
	jr $ra
.end_macro