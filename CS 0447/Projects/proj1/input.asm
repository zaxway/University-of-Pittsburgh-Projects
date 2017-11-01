# int Input_GetKeypress()
# 	Returns the last key pressed in $v0, or 0 if no key was pressed.
.globl Input_GetKeypress
Input_GetKeypress:
	li	$t0, 0xFFFF0000
	lw	$t1, 0($t0)
	beqz	$t1, _no_key

	sw	$zero, 0($t0)
	lw	$v0, 4($t0)
	jr	$ra

_no_key:
	li	$v0, 0
	jr	$ra