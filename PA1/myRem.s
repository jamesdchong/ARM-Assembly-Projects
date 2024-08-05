/*
 * Filename: myRem.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	myRem		@ Specify myRem as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: myRem()
 * Function Prototype: int myRem( int dividend, int divisor );
 * Description: Calculates the remainder using the divident and divisor formal
 * 		parameters
 * Parameters: dividend - number to be divided by another number
 *             divisor - number by which another number is to be divided
 * Side Effects - None
 * Error Conditions: None
 * Return Value: The remainder of the division
 * 
 * Registers used:
 *	r0 - arg 1 -- dividend and holds the return value of the remainder
 *	r1 - arg 2 -- divisor
 *	r2 - holds quotient of division of dividend by divisor
 *	r3 - temporary register for the quotient times the divisor
 */
myRem:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Compute the remainder from dividing the dividend by the divisor
	sdiv	r2, r0, r1		@ Divide dividend by divisor; quotient
					@   into r2
	mul	r3, r2, r1		@ Multiply quotient by divisor;
					@   temporary result into r3
	sub	r0, r0, r3		@ Subtract temporary result from
					@   dividend; remainder into r0

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc} 		@ Restore fp; restore lr into pc for
					@   return
