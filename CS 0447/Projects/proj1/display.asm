.eqv DISPLAY_BASE_ADDR 0xFFFF0008

# void Display_FillRect(int x:a0, int y:a1, int w:a2, int h:a3, int color:v0)
# Fills a rectangle of LEDs with the given color.
.globl Display_FillRect
Display_FillRect:
	# turn w/h into x2/y2
	add	$a2, $a2, $a0
	add	$a3, $a3, $a1

	# turn y1/y2 into addresses
	li	$t0, DISPLAY_BASE_ADDR
	sll	$a1, $a1, DISPLAY_W_SHIFT
	add	$a1, $a1, $t0
	add	$a1, $a1, $a0
	sll	$a3, $a3, DISPLAY_W_SHIFT
	add	$a3, $a3, $t0

	move	$t0, $a1
_fill_loop_y:
	move	$t1, $t0
	move	$t2, $a0
_fill_loop_x:
	sb	$v0, 0($t1)
	inc	$t1
	inc	$t2
	blt	$t2, $a2, _fill_loop_x

	addi	$t0, $t0, DISPLAY_W
	blt	$t0, $a3, _fill_loop_y

	jr	$ra

# void _setLED(int x, int y, int color)
#   sets the LED at (x,y) to color
#   color: 0=black, 1=red, 2=orange, 3=yellow, 4=green, 5=blue, 6=magenta, 7=white
#
# arguments: $a0 is x, $a1 is y, $a2 is color
# trashes:   $t0-$t3
# returns:   none
.globl Display_SetLED
Display_SetLED:
	sll	$t0, $a1, DISPLAY_W_SHIFT
	add	$t0, $t0, $a0
	li	$t1, DISPLAY_BASE_ADDR
	add	$t1, $t1, $t0
	sb	$a2, 0($t1)
	jr	$ra

# like _setLED, but takes a row-major offset into the LEDs as if they were a single-dimensional array of LEDs.
# void _setLED_Offset(int offset:a0, int color:a1)
.globl Display_SetLEDOffset
Display_SetLEDOffset:
	li	$t1, DISPLAY_BASE_ADDR
	add	$t1, $t1, $a0   # pixel addr
	sb	$a1, 0($t1)     # set pixel
	jr	$ra