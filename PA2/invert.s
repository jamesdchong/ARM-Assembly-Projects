/*
 * Filename: invert.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/4/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for formal parameters
	.equ	PARAM_SPACE, 8
	.equ	PATTERN_OFFSET, -8

@ Constants
	.equ	MASK, 0xFFFFFFFF

	.global	invert		@ Specify invert as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: invert()
 * Function Prototype: void invert( unsigned int pattern[] );
 * Description: Inverts all the bits in pattern (0 to 1 and 1 to 0).
 * Parameters: pattern[] - array holding two unsigned hex values
 * Side Effects - None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[]
 *	r1 - used to hold mask 0xFFFFFFFF, or bits of all ones
 *	r2 - used to hold mask 0xFFFFFFFF, or bits of all ones
 */
invert:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for formal params
	sub	sp, sp, PARAM_SPACE		@ allocate space for param

	@ Store formal parameter
	str	r0, [fp, PATTERN_OFFSET]	@ store param1

	@ Call toggle function passing in pattern and ones as part0, part1
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern to r0
	mov	r1, MASK			@ sets r1 to all ones
	mov	r2, MASK			@ sets r2 to all ones
	bl	toggle				@ calls toggle to invert bits

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
