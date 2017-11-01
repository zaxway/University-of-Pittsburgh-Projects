.data
	_board_layout: .ascii
	"****************************************************************"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*      P     *                  *                              *"
	"*            *                                                 *"
	"*            *                                                 *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *        G         *                              *"
	"*            *                  *                              *"
	"******  ******                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  *                              *"
	"*            *                  ************************       *"
	"*            *     L            *                      *       *"
	"*            *                  *                      *       *"
	"*            *                  *                      *       *"
	"*            ********************         G            *       *"
	"*                               *                      *       *"
	"*                               *                      *       *"
	"*                                                 K    *       *"
	"*                                                      *       *"
	"*                               *                      *       *"
	"*                               *                      *       *"
	"*                               *                      *       *"
	"*                               *                      *       *"
	"*                               *                      *       *"
	"******D  ***********************************************       *"
	"*                                                              *"
	"*                                                              *"
	"*                                                              *"
	"*                                                              *"
	"*                                                              *"
	"*                         **************                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            e                       *"
	"***************************                                    *"
	"*                         *                                    *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *     G      *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*       G                 *            *                       *"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            ***********F  ***********"
	"*                         *            *                       *"
	"*                         *            *                       *"
	"*                         *            *          T            *"
	"*  M                      *            *                       *"
	"*                                      *                       *"
	"*                                      *                       *"
	"****************************************************************"

	msg_invalid_cell: .asciiz " << invalid cell type.\n"
.text

# ======================================================================================================================
# Board_Init()
# Initializes the board space from the board data and creates the initial objects.
.globl Board_Init
Board_Init:
	enter	$s0, $s1, $s2, $s3

	# s0: board space; s1: layout; s2: loop index
	la	$s0, g_board
	la	$s1, _board_layout
	li	$s2, 0

_init_loop:
	lbu	$t0, 0($s1)
	beq	$t0, ' ', _cell_empty
	beq	$t0, '*', _cell_wall
	beq	$t0, 'P', _obj_player
	beq	$t0, 'K', _obj_key
	beq	$t0, 'L', _obj_key
	beq	$t0, 'M', _obj_key
	beq	$t0, 'D', _obj_door
	beq	$t0, 'd', _obj_door
	beq	$t0, 'E', _obj_door
	beq	$t0, 'e', _obj_door
	beq	$t0, 'F', _obj_door
	beq	$t0, 'f', _obj_door
	beq	$t0, 'G', _obj_dragon
	beq	$t0, 'T', _obj_treasure
	print_char_reg $t0
	print_string msg_invalid_cell
	exit	1

_cell_empty:
	li	$t0, CELL_NONE
	sb	$t0, 0($s0)
	j	_next

_cell_wall:
	li	$t0, CELL_WALL
	sb	$t0, 0($s0)
	j	_next

_obj_player:
	li	$a0, OBJ_PLAYER
	jal	Object_New
	# calculate x and y from the loop index
	srl	$t0, $s2, BOARD_W_SHIFT
	sb	$t0, OBJ_Y($v0)
	and	$t0, $s2, BOARD_W_MASK
	sb	$t0, OBJ_X($v0)
	j	_next

_obj_key:
	# key type derived from letter (K = 0, L = 1, M = 2)
	sub	$s3, $t0, 'K'
	li	$a0, OBJ_KEY
	jal	Object_New
	srl	$t0, $s2, BOARD_W_SHIFT
	sb	$t0, OBJ_Y($v0)
	and	$t0, $s2, BOARD_W_MASK
	sb	$t0, OBJ_X($v0)
	sb	$s3, OBJ_VAR1($v0)
	j	_next

_obj_door:
	move	$s3, $t0
	li	$a0, OBJ_DOOR
	jal	Object_New

	# door type derived from letter (D = 0, E = 1, F = 2; uppercase = horiz; lowercase = vert)
	bge	$s3, 'd', _obj_door_vert
	# horizontal
	sub	$s3, $s3, 'D'
	li	$t1, DOOR_LONG_SIDE
	li	$t2, DOOR_SHORT_SIDE
	j	_obj_door_finish
_obj_door_vert:
	sub	$s3, $s3, 'd'
	li	$t1, DOOR_SHORT_SIDE
	li	$t2, DOOR_LONG_SIDE
_obj_door_finish:
	sb	$t1, OBJ_W($v0)
	sb	$t2, OBJ_H($v0)
	sb	$s3, OBJ_VAR1($v0)
	srl	$t0, $s2, BOARD_W_SHIFT
	sb	$t0, OBJ_Y($v0)
	and	$t0, $s2, BOARD_W_MASK
	sb	$t0, OBJ_X($v0)
	j	_next

_obj_dragon:
	li	$a0, OBJ_DRAGON
	jal	Object_New
	srl	$t0, $s2, BOARD_W_SHIFT
	sb	$t0, OBJ_Y($v0)
	and	$t0, $s2, BOARD_W_MASK
	sb	$t0, OBJ_X($v0)
	j	_next

_obj_treasure:
	li	$a0, OBJ_TREASURE
	jal	Object_New
	srl	$t0, $s2, BOARD_W_SHIFT
	sb	$t0, OBJ_Y($v0)
	and	$t0, $s2, BOARD_W_MASK
	sb	$t0, OBJ_X($v0)

_next:
	inc	$s0
	inc	$s1
	inc	$s2
	blt	$s2, BOARD_SPACE_SIZE, _init_loop

	leave	$s0, $s1, $s2, $s3

# ======================================================================================================================
# Board_DrawAll()
# Writes to every location in the LED display with the blank and wall spaces.

.globl Board_DrawAll
Board_DrawAll:
	enter	$s0, $s1

	# s0: board, s1: offset
	la	$s0, g_board
	li	$s1, 0
_draw_loop:
	move	$a0, $s1
	lbu	$a1, 0($s0)
	beqz	$a1, _draw_pixel
	li	$a1, COLOR_WHITE
_draw_pixel:
	jal	Display_SetLEDOffset

	inc	$s0
	inc	$s1
	blt	$s1, BOARD_SPACE_SIZE, _draw_loop

	leave	$s0, $s1

# ======================================================================================================================
# Board_GetCell(int x:a0, int y:a1): int:v0
# Returns the type of cell at (x, y).

.globl Board_GetCell
Board_GetCell:
	sll	$t0, $a1, BOARD_W_SHIFT
	or	$t0, $t0, $a0
	la	$t1, g_board
	add	$t0, $t0, $t1
	lbu	$v0, 0($t0)
	jr	$ra

