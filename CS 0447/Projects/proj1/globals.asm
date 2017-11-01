	# memory to hold objects.
	g_object_space: .byte 0:OBJECT_SPACE_SIZE
	# memory to hold the board (walls).
	g_board:	.byte 0:BOARD_SPACE_SIZE
	# what state the game is currently in.
	g_game_state:	.byte GAME_INIT