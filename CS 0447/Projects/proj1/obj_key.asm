.eqv KEY_WIDTH           2
.eqv KEY_HEIGHT          1
.eqv KEY_STATE_NORMAL    1
.eqv KEY_STATE_DELETE    2
.eqv KEY_VAR_TYPE        OBJ_VAR1 # what type (red/green/blue) this key is
.eqv KEY_VAR_FLASH_DELAY OBJ_VAR2 # a timer used to flash the key object
.eqv KEY_FLASH_PERIOD    5 # key is on for 5 ticks, off for 5 ticks

.data
	Key_States:
	.word _key_state_init
	.word _key_state_normal
	.word _key_state_delete

	key_color_by_type:
	.byte COLOR_BLUE
	.byte COLOR_GREEN
	.byte COLOR_RED
.text

.globl Obj_Key
Obj_Key:
	enter $s0
	move	$s0, $a0
	STATE_SWITCH $s0, Key_States

_key_state_init:
	li	$t0, KEY_STATE_NORMAL
	sb	$t0, OBJ_STATE($s0)
	li	$t0, KEY_WIDTH
	sb	$t0, OBJ_W($s0)
	li	$t0, KEY_HEIGHT
	sb	$t0, OBJ_H($s0)
	li	$t0, KEY_FLASH_PERIOD
	sb	$t0, KEY_VAR_FLASH_DELAY($s0)
	# fall into normal state
_key_state_normal:
	# decrement the flash delay timer until it hits 0
	lbu	$t0, KEY_VAR_FLASH_DELAY($s0)
	dec	$t0
	sb	$t0, KEY_VAR_FLASH_DELAY($s0)
	bnez	$t0, _key_still_have_time

	# when it hits 0, reset the delay to 2 * the period
	li	$t0, KEY_FLASH_PERIOD
	sll	$t0, $t0, 1
	sb	$t0, KEY_VAR_FLASH_DELAY($s0)

_key_still_have_time:
	# they key is on for half the time and off for half the time
	blt	$t0, KEY_FLASH_PERIOD, _key_draw
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_BLACK
	jal	Display_FillRect
	j	_key_exit

_key_draw:
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	lbu	$v0, KEY_VAR_TYPE($s0)
	la	$t0, key_color_by_type
	add	$t0, $t0, $v0
	lbu	$v0, 0($t0)
	jal	Display_FillRect
	j	_key_exit

_key_state_delete:
	# key enters this state when player touches it.
	# just clears its LEDs and deletes itself.
	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_BLACK
	jal	Display_FillRect
	move	$a0, $s0
	jal	Object_Delete

_key_exit:
	leave $s0

# ======================================================================================================================
# Key_CollideWithPlayer(Obj* player:a0, Obj* key:a1)
# The player collided with this key.

.globl Key_CollideWithPlayer
Key_CollideWithPlayer:
	# Set my state to delete and add myself to the player's inventory.
	li	$t0, KEY_STATE_DELETE
	sb	$t0, OBJ_STATE($a1)
	lbu	$t0, KEY_VAR_TYPE($a1)
	la	$t1, player_key_inv
	add	$t1, $t1, $t0
	li	$t0, 1
	sb	$t0, 0($t1)
	jr	$ra