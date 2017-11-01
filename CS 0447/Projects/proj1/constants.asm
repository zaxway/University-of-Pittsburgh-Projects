# Display size
.eqv DISPLAY_W       64
.eqv DISPLAY_H       64
.eqv DISPLAY_W_MASK  63
.eqv DISPLAY_H_MASK  63
.eqv DISPLAY_W_SHIFT 6

# LED Colors
.eqv COLOR_BLACK   0
.eqv COLOR_RED     1
.eqv COLOR_ORANGE  2
.eqv COLOR_YELLOW  3
.eqv COLOR_GREEN   4
.eqv COLOR_BLUE    5
.eqv COLOR_MAGENTA 6
.eqv COLOR_WHITE   7

# Input key codes
.eqv KEY_NONE 0x00
.eqv KEY_U    0xE0
.eqv KEY_D    0xE1
.eqv KEY_L    0xE2
.eqv KEY_R    0xE3
.eqv KEY_B    0x42

# Cell types
.eqv CELL_NONE 0
.eqv CELL_WALL 1

# Board constants
.eqv BOARD_W          64
.eqv BOARD_H          64
.eqv BOARD_W_MASK     63
.eqv BOARD_H_MASK     63
.eqv BOARD_W_SHIFT    6
.eqv BOARD_SPACE_SIZE 4096

# Object types
.eqv OBJ_NONE     0
.eqv OBJ_PLAYER   1
.eqv OBJ_KEY      2
.eqv OBJ_DOOR     3
.eqv OBJ_TREASURE 4
.eqv OBJ_DRAGON   5

# Object fields (all bytes)
.eqv OBJ_TYPE  0x00
.eqv OBJ_STATE 0x01
.eqv OBJ_X     0x02
.eqv OBJ_Y     0x03
.eqv OBJ_W     0x04
.eqv OBJ_H     0x05
.eqv OBJ_VAR1  0x06
.eqv OBJ_VAR2  0x07

# Other object constants
.eqv OBJ_SIZE       8
.eqv OBJ_SIZE_SHIFT 3
.eqv MAX_OBJECTS    32
# 32 * 8
.eqv OBJECT_SPACE_SIZE 256
.eqv NULL 0

# State constants
.eqv STATE_INIT 0

# Game states
.eqv GAME_INIT    0
.eqv GAME_RUNNING 1
.eqv GAME_WON     2
.eqv GAME_OVER    3