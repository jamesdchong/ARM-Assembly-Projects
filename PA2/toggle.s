/*
 * Filename: toggle.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 4
	.equ	NEW_PATTERN_OFFSET, -8

@ Constants for formal parameters
	.equ	PARAM_SPACE, 12
	.equ	PATTERN_OFFSET, -16
	.equ	PART_ZERO_OFFSET, -20
	.equ	PART_ONE_OFFSET, -24

@ Constants
	.equ	FIRST_ELEMENT_OFFSET, 0
	.equ	SECOND_ELEMENT_OFFSET, 4

	.global	toggle		@ Specify toggle as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: toggle()
 * Function Prototype: void toggle( unsigned int pattern[], unsigned int part0,
 * 				    unsigned int part1 );
 * Description: Toggles all the bits in pattern specified in part0 and part1. If
 * 		the bit value in part0 or part1 is 1, then its corresponding bit
 * 		in pattern should invert (i.e. 1 becomes 0, and 0 becomes 1).
 * 		However, if the bit value in part0 or part1 is 0, then the
 * 		corresponding bit in pattern should remain the same
 * Parameters: pattern[] - array holding two unsigned hex values
 * 	       part0 - hex value to use exclusive or bit operator along with the
 *		       first element of the pattern array
 * 	       part1 - hex value to use exclusive or bit operator along with the
 * 	               second element of the pattern array
 * Side Effects - None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[]
 *	r1 - arg 2 -- part0, used to store each final hex value after using 
 *		      exclusive or bit operator
 *	r2 - arg 3 -- part1, used to hold elements of pattern array
 *	r3 - used to store part0 and part1 values while using exclusive or bit
 * 	     operator
 */
toggle:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ Allocate 1 local var

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ Allocate space for r0-r2

	@ Store formal params on stack
	str	r0, [fp, PATTERN_OFFSET]	@ store param1
	str	r1, [fp, PART_ZERO_OFFSET]	@ store param2
	str	r2, [fp, PART_ONE_OFFSET]	@ store param3

	@ Use exclusive or bit operator on part0, first element of pattern
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r2, [r0, FIRST_ELEMENT_OFFSET]	@ load first element of array to
						@   r2
	ldr	r3, [fp, PART_ZERO_OFFSET]	@ load part0 to r3
	eor	r1, r2, r3			@ use exclusive or bit operator
						@   on r2, r3
	str	r1, [r0, FIRST_ELEMENT_OFFSET]	@ store r3 to first element in
						@   pattern array
	str	r0, [fp, NEW_PATTERN_OFFSET]	@ store r0 to new pattern array

	@ Use exclusive or bit operator on part1, second element of pattern
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r2, [r0, SECOND_ELEMENT_OFFSET]	@ load second element of array
						@   to r2
	ldr	r3, [fp, PART_ONE_OFFSET]	@ load part1 to r3
	eor	r1, r2, r3			@ use exclusive or bit operator
						@   on r2, r3
	str	r1, [r0, SECOND_ELEMENT_OFFSET]	@ store r3 to second element in
						@   pattern array
	str	r0, [fp, NEW_PATTERN_OFFSET]	@ store r0 to new pattern array

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
