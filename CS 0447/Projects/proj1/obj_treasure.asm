# Treasure object is super simple!

.eqv TREASURE_WIDTH           3
.eqv TREASURE_HEIGHT          2
.eqv TREASURE_STATE_NORMAL    1

.data
	Treasure_States:
	.word _treasure_state_init
	.word _treasure_state_normal
.text

.globl Obj_Treasure
Obj_Treasure:
	enter $s0
	move	$s0, $a0
	STATE_SWITCH $s0, Treasure_States

_treasure_state_init:
	li	$t0, TREASURE_STATE_NORMAL
	sb	$t0, OBJ_STATE($s0)
	li	$t0, TREASURE_WIDTH
	sb	$t0, OBJ_W($s0)
	li	$t0, TREASURE_HEIGHT
	sb	$t0, OBJ_H($s0)

	lbu	$a0, OBJ_X($s0)
	lbu	$a1, OBJ_Y($s0)
	lbu	$a2, OBJ_W($s0)
	lbu	$a3, OBJ_H($s0)
	li	$v0, COLOR_ORANGE
	jal	Display_FillRect

	# fall into normal state
_treasure_state_normal:
	j	_treasure_exit

_treasure_exit:
	leave $s0

# ======================================================================================================================
# Treasure_CollideWithPlayer(Obj* player:a0, Obj* treasure:a1)
# The player collided with this treasure. Tada, game won!

.globl Treasure_CollideWithPlayer
Treasure_CollideWithPlayer:
	li	$t0, GAME_WON
	la	$t1, g_game_state
	sb	$t0, 0($t1)
	jr	$ra