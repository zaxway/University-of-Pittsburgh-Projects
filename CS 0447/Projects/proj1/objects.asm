
# You can use jr to jump to any address, not just to return.
# It's commonly used to implement switches (or "jump tables" in assembly).
# A jump table is just an array of pointers to code.
.macro jumptable_t0 %reg %table
	# multiply index by sizeof(word)
	sll	%reg, %reg, 2
	# get the address out of the table
	la	$t0, %table
	add	%reg, %reg, $t0
	lw	%reg, 0(%reg)
	# jump to it
	jr	%reg
.end_macro

.macro jumptable_t1 %reg %table
	sll	%reg, %reg, 2
	la	$t1, %table
	add	%reg, %reg, $t1
	lw	%reg, 0(%reg)
	jr	%reg
.end_macro

# used to switch on what the object's current state is (used in object routines).
.macro STATE_SWITCH %this %table
	lbu	$t0, OBJ_STATE(%this)
	jumptable_t1, $t0, %table
.end_macro

# Allllll the kindsa objects.
.include "obj_invalid.asm"
.include "obj_player.asm"
.include "obj_key.asm"
.include "obj_door.asm"
.include "obj_treasure.asm"
.include "obj_dragon.asm"

.data
	# Jump table for all the object update routines.
	# We just switch on the object's 'type' field and run the right routine.
	_object_jump_table:
	.word Obj_Invalid
	.word Obj_Player
	.word Obj_Key
	.word Obj_Door
	.word Obj_Treasure
	.word Obj_Dragon

	msg_no_empty_slot: .asciiz "Could not find an empty object slot"
.text

# ======================================================================================================================
# Object_New(int type:a0): Obj*:v0
# Tries to allocate a new object of the given type.
# Returns a pointer to the object (zeroed with type set), or crashes if it couldn't.
.globl Object_New
Object_New:
	# Loop through object space and find a slot with a type of 0.
	# t0: object pointer
	la	$t0, g_object_space

	# t9: loop index
	li	$t9, 0

	# if the type is OBJ_PLAYER, start at slot 0; otherwise start at slot 1.
	beq	$a0, OBJ_PLAYER, _new_loop
	li	$t9, 1
	addi	$t0, $t0, OBJ_SIZE
_new_loop:
	lbu	$t2, OBJ_TYPE($t0)
	beqz	$t2, _found_space
	addi	$t0, $t0, OBJ_SIZE
	addi	$t9, $t9, 1
	blt	$t9, MAX_OBJECTS, _new_loop

	# Failed to find an open slot.
	print_string msg_no_empty_slot
	exit	1

_found_space:
	# Yay, we found one!
	move	$v0, $t0

	# Clear the memory.
	li	$t9, OBJ_SIZE
_clear_loop:
	sb	$zero, 0($t0)
	inc	$t0
	dec	$t9
	bnez	$t9, _clear_loop

	# Set the type, and return.
	sb	$a0, OBJ_TYPE($v0)
	jr	$ra

# ======================================================================================================================
# Object_Delete(Obj* this:a0)
# Deletes the given object. Just wipes out the type field so it no longer does anything.
.globl Object_Delete
Object_Delete:
	sb	$zero, OBJ_TYPE($a0)
	jr	$ra

# ======================================================================================================================
# Object_UpdateAll()
# Updates all objects. Loops through the object array and calls the routine of each one that exists.
.globl Object_UpdateAll
Object_UpdateAll:
	enter	$s0, $s1

	# s0: current object; s1: index

	# Update all non-player objects first, then update the player. This avoids weird rendering issues
	la	$s0, g_object_space
	addi	$s0, $s0, OBJ_SIZE
	li	$s1, 1
_update_loop:
	lbu	$t0, 0($s0)
	beqz	$t0, _no_update

	# to do a "call jumptable" you have to load $ra yourself.
	move	$a0, $s0
	la	$ra, _no_update
	jumptable_t1 $t0, _object_jump_table

_no_update:
	addi	$s0, $s0, OBJ_SIZE
	inc	$s1
	blt	$s1, MAX_OBJECTS, _update_loop

	# Now we update the player.
	la	$a0, g_object_space
	jal	Obj_Player

	leave	$s0, $s1

# ======================================================================================================================
# Object_CheckWallCollision(Obj* this:a0, int newX:a1, int newY:a2): bool:v0
# Checks if the object would collide with the wall if it moved to (newX, newY).
# Returns true if so, and false if there is no collision.
.globl Object_CheckWallCollision
Object_CheckWallCollision:
	enter	$s0, $s1, $s2, $s3, $s4

	# s0: y
	# s1: x
	# s2: newX
	# s3: maxX
	# s4: maxY

	# stash newX
	move	$s2, $a1
	# maxX = newX + this.w
	lbu	$t0, OBJ_W($a0)
	add	$s3, $t0, $a1
	# maxY = newY + this.h
	lbu	$t0, OBJ_H($a0)
	add	$s4, $t0, $a2

	# loop over all cells that this object encompasses and sees if there's a wall in any of them.
	move	$s0, $a2
_check_coll_y_loop:
	move	$s1, $s2
_check_coll_x_loop:
	move	$a0, $s1
	move	$a1, $s0
	jal	Board_GetCell
	beqz	$v0, _no_cell
	li	$v0, 1
	j	_check_coll_exit
_no_cell:
	inc	$s1
	blt	$s1, $s3, _check_coll_x_loop

	inc	$s0
	blt	$s0, $s4, _check_coll_y_loop

	li	$v0, 0
_check_coll_exit:
	leave	$s0, $s1, $s2, $s3, $s4

# ======================================================================================================================
# Object_CheckObjCollision(Obj* this:a0, int newX:a1, int newY:a2): Obj*:v0
# Checks if the object would collide with another object in a higher slot if it moved to (newX, newY).
# Returns the colliding object's address if so, and NULL if there is no collision.

.globl Object_CheckObjCollision
Object_CheckObjCollision:
	enter	$s0, $s1, $s2, $s3, $s4, $s5
	move	$s0, $a0
	move	$s2, $a1
	move	$s3, $a2
	lbu	$s4, OBJ_W($s0)
	add	$s4, $s4, $s2
	lbu	$s5, OBJ_H($s0)
	add	$s5, $s5, $s3

	# s0: this
	# s1: other
	# s2: this.x1
	# s3: this.y1
	# s4: this.x2
	# s5: this.y2

	# for(s1 = last_object_slot; s1 > s0; s1 -= obj_size)
	la	$s1, g_object_space
	addi	$s1, $s1, OBJECT_SPACE_SIZE
	addi	$s1, $s1, -OBJ_SIZE

_check_obj_coll_loop:
	ble	$s1, $s0, _check_obj_coll_loop_exit
	lbu	$t0, OBJ_TYPE($s1)
	beqz	$t0, _check_obj_coll_loop_next

	# t2: other.x1
	# t3: other.y1
	# t4: other.x2
	# t5: other.y2
	lbu	$t2, OBJ_X($s1)
	lbu	$t3, OBJ_Y($s1)
	lbu	$t4, OBJ_W($s1)
	add	$t4, $t4, $t2
	lbu	$t5, OBJ_H($s1)
	add	$t5, $t5, $t3

	# do these two rectangles overlap?

	#if(this.x1 >= other.x2 || other.x1 >= this.x2 || this.y1 >= other.y2 || other.y1 >= this.y2) not overlapping
	bge	$s2, $t4, _check_obj_coll_loop_next
	bge	$t2, $s4, _check_obj_coll_loop_next
	bge	$s3, $t5, _check_obj_coll_loop_next
	bge	$t3, $s5, _check_obj_coll_loop_next
	move	$v0, $s1
	j	_check_obj_coll_exit

_check_obj_coll_loop_next:
	addi	$s1, $s1, -OBJ_SIZE
	j	_check_obj_coll_loop

_check_obj_coll_loop_exit:
	li	$v0, NULL
_check_obj_coll_exit:
	leave	$s0, $s1, $s2, $s3, $s4, $s5