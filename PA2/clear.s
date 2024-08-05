/*
 * Filename: clear.s
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

	.global	clear		@ Specify clear as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: clear()
 * Function Prototype: void clear( unsigned int pattern[], unsigned int part0,
 * 				   unsigned int part1 );
 * Description: Works similar to set(), except this function turns off the
 * 		specified bits in pattern with the bit patterns part0 and part1.
 *		If a bit value in part0 or part1 is 1, then its corresponding
 *		bit in pattern should become 0. However, if the bit value in
 *		part0 or part1 is 0, then its corresponding bit in pattern
 *		should remain the same.
 * Parameters: pattern[] - array holding two unsigned hex values
 * 	       part0 - hex value to invert and use the and bit operator along
 * 	       	       with the first element of the pattern array
 * 	       part1 - hex value to invert and use the and bit operator along
 * 	               with the second element of the pattern array
 * Side Effects - None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[]
 *	r1 - arg 2 -- part0, used to store each final hex value after using and
 *		      bit operator
 *	r2 - arg 3 -- part1, used to hold elements of pattern array
 *	r3 - used to store part0 and part1 values while using not, and bit
 * 	     operator
 */
clear:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ Allocate 1 local var

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ Allocate space for params

	@ Store formal params on stack
	str	r0, [fp, PATTERN_OFFSET]	@ store param1
	str	r1, [fp, PART_ZERO_OFFSET]	@ store param2
	str	r2, [fp, PART_ONE_OFFSET]	@ store param3

	@ Invert and use and bit operator on part0, first element of pattern
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r2, [r0, FIRST_ELEMENT_OFFSET]	@ load first element of array to
						@   r2
	ldr	r3, [fp, PART_ZERO_OFFSET]	@ load part0 to r3
	mvn	r3, r3				@ invert part0
	and	r1, r2, r3			@ use and bit operator on r2, r3
	str	r1, [r0, FIRST_ELEMENT_OFFSET]	@ store r3 to first element in
						@   pattern array
	str	r0, [fp, NEW_PATTERN_OFFSET]	@ store r0 to new pattern array

	@ Invert and use and bit operator on part1, second element of pattern
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r2, [r0, SECOND_ELEMENT_OFFSET]	@ load second element of array
						@   to r2
	ldr	r3, [fp, PART_ONE_OFFSET]	@ load part1 to r3
	mvn	r3, r3				@ invert part1
	and	r1, r2, r3			@ use and bit operator on r2, r3
	str	r1, [r0, SECOND_ELEMENT_OFFSET]	@ store r3 to second element in
						@   pattern array
	str	r0, [fp, NEW_PATTERN_OFFSET]	@ store r0 to new pattern array

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
