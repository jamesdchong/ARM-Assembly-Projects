/*
 * Filename: average3.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/5/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex -a53	@ Version of our Pis
	.syntax	unified 	@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offest from sp to set fp
	.equ	NUM_ELEMENTS, 3	@ Number of elements summed; used for average

	.global	average3	@ Specify average3 as a global symbol

	.text			@ Switch to Text segment
	.align 2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: average3()
 * Function Prototype: int average3( int a, int b, int c );
 * Description: Returns the integer average of the three formal parameters
 * Parameters: a - the first value to sum
 *             b - the second value to sum
 *             c - the third value to sum
 * Side Effects: None
 * Error Conditions: None
 * Return Value: The average of the three formal parameters
 *
 * Registers used:
 * 	r0 - arg 1 -- a
 *	r1 - arg 2 -- b and as temporary register for the divisor (NUM_ELEMENTS)
 *	r2 - arg 3 -- c
 *	r3 - holds the intermediate sum and final average of a, b, and c
 */

average3:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Incoming parameters in r0, r1, r2
	add	r3, r0, r1		@ Add param1 and param2; result into r3
	add	r3, r3, r2		@ Add param3 and sum stored in r3;
					@   result into r3

	@ Compute the average of the three numbers
	mov	r1, NUM_ELEMENTS	@ Move constant into register for sdiv
	sdiv	r0, r3, r1		@ Put result into r0

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
