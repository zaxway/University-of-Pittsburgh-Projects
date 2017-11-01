# Player object does a lot of stuff.

.eqv PLAYER_WIDTH      1
.eqv PLAYER_HEIGHT     1

.eqv PLAYER_STATE_NORMAL 1

.data
	player_last_key: .byte KEY_NONE
	player_key_inv: .byte 0:3

	Player_States:
	.word _player_state_init
	.word _player_state_normal
.text

.globl Obj_Player
Obj_Player:
	# s0: this
	# s1: newX
	# s2: newY
	enter	$s0, $s1, $s2
	move	$s0, $a0
	STATE_SWITCH $s0, Player_States

_player_state_init:
	li	$t0, PLAYER_STATE_NORMAL
	sb	$t0, OBJ_STATE($s0)
	li	$t0, PLAYER_WIDTH
	sb	$t0, OBJ_W($s0)
	li	$t0, PLAYER_HEIGHT
	sb	$t0, OBJ_H($s0)

	# fall into normal state
_player_state_normal:
	lbu	$s1, OBJ_X($s0)
	lbu	$s2, OBJ_Y($s0)
	jal	Player_CheckInput
	beq	$v0, KEY_U, _move_up
	beq	$v0, KEY_D, _move_down
	beq	$v0, KEY_L, _move_left
	beq	$v0, KEY_R, _move_right
	j	_player_check_obj_coll
_move_up:
	dec	$s2
	j	_move_common
_move_down:
	inc	$s2
	j	_move_common
_move_left:
	dec	$s1
	j	_move_common
_move_right:
	inc	$s1
_move_common:
	# did we run into a wall?
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	Object_CheckWallCollision
	beqz	$v0, _player_check_obj_coll

	# if so, stop the player.
	li	$t0, KEY_NONE
	la	$t1, player_last_key
	sb	$t0, 0($t1)

_player_check_obj_coll:
	# did we touch an object?
	move	$a0, $s0
	move	$a1, $s1
	move	$a2, $s2
	jal	Object_CheckObjCollision
	beqz	$v0, _player_move_to_new_cell

	# we touched an object and have its address.
	# call its collision routine.
	move	$a0, $s0
	move	$a1, $v0
	jal	Player_CollidedWithObject

_player_move_to_new_cell:
	# check this again because the wall/door collision may or may not have stopped the player.
	la	$t0, player_last_key
	lb	$t0, 0($t0)
	beq	$t0, KEY_NONE, _player_draw_and_exit

	# erase old LED and store new location in player's x/y.
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	li	$a2, COLOR_BLACK
	jal	Display_SetLED
	sb	$s1, OBJ_X($s0)
	sb	$s2, OBJ_Y($s0)

_player_draw_and_exit:
	# draw new LED.
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	li	$a2, COLOR_MAGENTA
	jal	Display_SetLED
	leave	$s0, $s1, $s2

# ======================================================================================================================
# Player_CheckInput(): int
# Checks if the user has pressed any keys. Returns the last key the user pressed.
Player_CheckInput:
	enter

	# get the input; if they didn't press a key, get the last key; if they did, store it.
	jal	Input_GetKeypress
	la	$t0, player_last_key
	beqz	$v0, _get_last_key
	sb	$v0, 0($t0)
	j 	_check_input_exit

_get_last_key:
	lbu	$v0, 0($t0)

_check_input_exit:
	leave

# ======================================================================================================================
# Player_CollidedWithObject(Obj* self:a0, Obj* other:a1)
# A collision has occurred with 'other'; respond accordingly.
.data
	# Each object has a collided routine (in each object's file) that is called by this function.
	collide_jump_table:
	.word _player_coll_invalid # OBJ_NONE
	.word _player_coll_invalid # OBJ_PLAYER
	.word Key_CollideWithPlayer
	.word Door_CollideWithPlayer
	.word Treasure_CollideWithPlayer
	.word Dragon_CollideWithPlayer

	msg_invalid_collision: .asciiz "Unimplemented collision with object of type "

.text
Player_CollidedWithObject:
	enter
	lbu	$t0, OBJ_TYPE($a1)
	la	$ra _player_coll_exit
	jumptable_t1 $t0, collide_jump_table

_player_coll_invalid:
	print_string msg_invalid_collision
	lbu	$t0, OBJ_TYPE($a1)
	print_int $t0
	exit 1

_player_coll_exit:
	leave