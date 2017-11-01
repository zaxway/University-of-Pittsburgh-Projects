# (checking for player distance and moving etc.)

.eqv DRAGON_WIDTH           2
.eqv DRAGON_HEIGHT          2
.eqv DRAGON_STATE_ROAMING   1
.eqv DRAGON_STATE_CHASING   2

# movement timer
.eqv DRAGON_VAR_MOVE_TIMER OBJ_VAR1

# when roaming, move only every 8 ticks.
.eqv DRAGON_ROAMING_MOVE_DELAY 8

# when chasing, move every other tick.
.eqv DRAGON_CHASING_MOVE_DELAY 2

# chase if the player is 8 spaces away or less.
.eqv DRAGON_CHASE_RADIUS 8

.data
	Dragon_States:
	.word _dragon_state_init
	.word _dragon_state_roaming
	.word _dragon_state_chasing
.text

.globl Obj_Dragon
Obj_Dragon:
	enter	$s0, $s1, $s2
	move	$s0, $a0
	STATE_SWITCH $s0, Dragon_States

_dragon_state_init:
	li	$t0, DRAGON_STATE_ROAMING
	sb	$t0, OBJ_STATE($s0)
	li	$t0, DRAGON_WIDTH
	sb	$t0, OBJ_W($s0)
	li	$t0, DRAGON_HEIGHT
	sb	$t0, OBJ_H($s0)
	li	$t0, DRAGON_ROAMING_MOVE_DELAY
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)

	# fall into normal state
_dragon_state_roaming:
	la	$s1, g_object_space # player is slot 0

	# dx = abs(player_x - self_x)
	lb	$t0, OBJ_X($s0)
	lb	$t1, OBJ_X($s1)
	sub	$t0, $t0, $t1
	abs	$t0, $t0
	# if(dx <= range
	bgt	$t0, DRAGON_CHASE_RADIUS, _dragon_roam_move

	# dy = abs(player_y - self_y)
	lb	$t0, OBJ_Y($s0)
	lb	$t1, OBJ_Y($s1)
	sub	$t0, $t0, $t1
	abs	$t0, $t0
	#                  && dy <= range)
	bgt	$t0, DRAGON_CHASE_RADIUS, _dragon_roam_move

	# Chase the player!
	li	$t0, 1
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)
	li	$t0, DRAGON_STATE_CHASING
	sb	$t0, OBJ_STATE($s0)

	j	_dragon_state_chasing
	# else
_dragon_roam_move:
	#	dec move timer
	lb	$t0, DRAGON_VAR_MOVE_TIMER($s0)
	dec	$t0
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)

	#	if move timer == 0
	bnez	$t0, _dragon_draw_and_exit
	#		reset move timer
	li	$t0, DRAGON_ROAMING_MOVE_DELAY
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)

	#		move in random direction
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_BLACK
	jal	Display_FillRect

	li	$a0, 0
	li	$v0, sys_randInt
	syscall

.data
	# just a handy way to write a little less code for moving the dragon randomly.
	Dragon_Move_Table:
	.byte 1 0
	.byte 0 1
	.byte -1 0
	.byte 0 -1
.text
	andi	$a0, $a0, 3
	sll	$a0, $a0, 1
	la	$t0, Dragon_Move_Table
	add	$t0, $t0, $a0
	lb	$t1, OBJ_X($s0)
	lb	$t2, 0($t0)
	add	$s1, $t1, $t2
	lb	$t1, OBJ_Y($s0)
	lb	$t2, 1($t0)
	add	$s2, $t1, $t2

	# check for wall collision and stop if so
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	Object_CheckWallCollision
	bnez	$v0, _dragon_draw_and_exit

	sb	$s1, OBJ_X($s0)
	sb	$s2, OBJ_Y($s0)
	j	_dragon_draw_and_exit

_dragon_state_chasing:
	# dec move timer
	lb	$t0, DRAGON_VAR_MOVE_TIMER($s0)
	dec	$t0
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)

	#	if move timer == 0
	bnez	$t0, _dragon_draw_and_exit
	#	reset move timer
	li	$t0, DRAGON_CHASING_MOVE_DELAY
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)

	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_BLACK
	jal	Display_FillRect

	la	$s1, g_object_space # player is slot 0

	#	dx:t0 = player x - self x
	lb	$t0, OBJ_X($s1)
	lb	$t1, OBJ_X($s0)
	sub	$t0, $t0, $t1

	#	dy:t1 = player y - self y
	lb	$t1, OBJ_Y($s1)
	lb	$t2, OBJ_Y($s0)
	sub	$t1, $t1, $t2

	abs	$t2, $t0
	abs	$t3, $t1

	bgt	$t2, DRAGON_CHASE_RADIUS, _dragon_stop_chasing
	ble	$t3, DRAGON_CHASE_RADIUS, _dragon_keep_chasing

_dragon_stop_chasing:
	li	$t0, DRAGON_ROAMING_MOVE_DELAY
	sb	$t0, DRAGON_VAR_MOVE_TIMER($s0)
	li	$t0, DRAGON_STATE_ROAMING
	sb	$t0, OBJ_STATE($s0)
	j	_dragon_draw_and_exit

_dragon_keep_chasing:
	lb	$s1, OBJ_X($s0)
	lb	$s2, OBJ_Y($s0)

	#	if abs dx > abs dy
	ble	$t2, $t3, _dragon_chase_y
	bge	$t0, $0, _dragon_chase_right
	dec	$s1
	j	_dragon_chase_try_move
_dragon_chase_right:
	inc	$s1
	j	_dragon_chase_try_move
_dragon_chase_y:
	bge	$t1, $0, _dragon_chase_down
	dec	$s2
	j	_dragon_chase_try_move
_dragon_chase_down:
	inc	$s2

_dragon_chase_try_move:
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	Object_CheckWallCollision
	bnez	$v0, _dragon_draw_and_exit

	sb	$s1, OBJ_X($s0)
	sb	$s2, OBJ_Y($s0)
	j	_dragon_draw_and_exit

_dragon_draw_and_exit:
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_YELLOW
	jal	Display_FillRect
	j	_dragon_exit

_dragon_exit:
	leave	$s0, $s1, $s2

# ======================================================================================================================
# Dragon_CollideWithPlayer(Obj* player:a0, Obj* key:a1)
# The player collided with this dragon. Game over!

.globl Dragon_CollideWithPlayer
Dragon_CollideWithPlayer:
	li	$t0, GAME_OVER
	la	$t1, g_game_state
	sb	$t0, 0($t1)
	jr	$ra
