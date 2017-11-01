.include "convenience.asm"
.include "constants.asm"

.data
.include "globals.asm"

.text

.include "input.asm"
.include "display.asm"
.include "objects.asm"
.include "board.asm"

.eqv GAME_TICK_MS 100

.globl main
main:
	# sys_seedRand(0, 0)
	li	$a0, 0
	li	$a1, 0
	li	$v0, sys_seedRand
	syscall

	# Board_Init()
	jal	Board_Init

	# Board_DrawAll()
	jal	Board_DrawAll

	# g_game_state = GAME_RUNNING
	li	$t0, GAME_RUNNING
	la	$t1, g_game_state
	sb	$t0, 0($t1)

	# last_frame_time = 0
	li	$s0, 0
loop:
	# wait until GAME_TICK_MS ms have passed
	li	$v0, sys_time
	syscall
	sub	$t0, $a0, $s0
	bltu	$t0, GAME_TICK_MS, loop
	move	$s0, $a0

	# update everything
	jal	Object_UpdateAll

	# loop while the game is still running
	la	$t0, g_game_state
	lbu	$t0, 0($t0)
	beq	$t0, GAME_RUNNING, loop

	exit