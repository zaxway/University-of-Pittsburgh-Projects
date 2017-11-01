# ======================================================================================================================
# Object_Invalid(Obj* this:a0)
# "Update routine" for an invalid (empty) object slot. Prints an error message and quits.

.data
	msg_invalid_object: .asciiz "Trying to update empty object in slot "
.text
.globl Obj_Invalid
Obj_Invalid:
	# we can smash these cause we're crashing anyway
	move	$s0, $a0
	print_string msg_invalid_object
	la	$t0, g_object_space
	sub	$t0, $s0, $t0
	srl	$t0, $t0, OBJ_SIZE_SHIFT
	print_int $t0
	exit	1
