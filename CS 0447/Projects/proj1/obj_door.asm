# Dooooooooors!

.eqv DOOR_LONG_SIDE       3
.eqv DOOR_SHORT_SIDE      1
.eqv DOOR_STATE_NORMAL    1
.eqv DOOR_STATE_DELETE    2
.eqv DOOR_VAR_TYPE        OBJ_VAR1 # what type of door (red/green/blue) it is

.data
	Door_States:
	.word _door_state_init
	.word _door_state_normal
	.word _door_state_delete

	door_color_by_type:
	.byte COLOR_BLUE
	.byte COLOR_GREEN
	.byte COLOR_RED
.text

.globl Obj_Door
Obj_Door:
	enter $s0
	move	$s0, $a0
	STATE_SWITCH $s0, Door_States

_door_state_init:
	li	$t0, DOOR_STATE_NORMAL
	sb	$t0, OBJ_STATE($s0)
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	lbu	$v0, DOOR_VAR_TYPE($s0)
	la	$t0, door_color_by_type
	add	$t0, $t0, $v0
	lbu	$v0, 0($t0)
	jal	Display_FillRect

	# fall into normal state
_door_state_normal:
	# the door just ... sits there....
	j	_door_exit

_door_state_delete:
	# delete itself. clear LEDs and delete object
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_BLACK
	jal	Display_FillRect
	move	$a0, $s0
	jal	Object_Delete

_door_exit:
	leave $s0

# ======================================================================================================================
# Door_CollideWithPlayer(Obj* player:a0, Obj* door:a1)
# The player collided with this door.

.globl Door_CollideWithPlayer
Door_CollideWithPlayer:
	# Check if the player has the key to this door
	lbu	$t0, DOOR_VAR_TYPE($a1)
	la	$t1, player_key_inv
	add	$t1, $t1, $t0
	lbu	$t1, 0($t1)
	bnez	$t1, _door_have_key

	# player doesn't have key, make them stop
	la	$t0, player_last_key
	li	$t1, KEY_NONE
	sb	$t1, 0($t0)
	j	_door_collide_exit

_door_have_key:
	# player does have key, set my state to delete
	li	$t0, DOOR_STATE_DELETE
	sb	$t0, OBJ_STATE($a1)
_door_collide_exit:
	jr	$ra