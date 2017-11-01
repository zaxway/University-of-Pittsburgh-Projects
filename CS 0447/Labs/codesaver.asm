    	move $s1, $a0 #x : s1
    	move $s2, $a1 #y : s2
    checkers:
    	beq $s1, 50, check1
    	beq $s1, 51, check1
    	beq $s1, 52, check1
    moving:
    	jal Input_GetKeypress
    	move $s0, $v0
    	beq $s0, KEY_U, upkey
    	beq $s0, KEY_D, downkey
    	beq $s0, KEY_L, leftkey
    	beq $s0, KEY_R, rightkey
    	
    	check1:
    		beq $s2, 61, end2
    		beq $s2, 62, end2
    		j moving
    	upkey:
    		addi $s1, $s1, -1
    		j checkers
    	downkey:
    		addi $s1, $s1, 1
    		j checkers
    	leftkey:
    		addi $s2, $s2, -1
    		j checkers
    	rightkey:
    		addi $s2, $s2, 1
    		j checkers
    		
    end2:
    	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	addi $sp, $sp, 16
    	jr $ra
    	
    	
    	
    	
    	
    	li $a0, 18
	li $a1, 29
	li $a2, COLOR_BLUE
	jal Display_SetLED
	li $a0, 19
	li $a1, 29
	li $a2, COLOR_BLUE
	jal Display_SetLED
	li $a0, 20
	li $a1, 29
	li $a2, COLOR_BLUE
	jal Display_SetLED
	li $a0, 17
	li $a1, 29
	li $a2, COLOR_BLUE
	jal Display_SetLED
