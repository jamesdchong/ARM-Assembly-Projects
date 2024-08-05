/*
 * Filename: myURem.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/11/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.global	myURem			@ Specify myURem as global symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: myURem()
 * Function Prototype: int myURem( unsigned int dividend,
 * 				   unsigned int divisor );
 * Description: Calculates remainder when dividing dividend by divisor, where
 * 		dividend, divisor, and the remainder are all unsigned integers.
 * Parameters: dividend - number to be divided by another number
 *	       divisor - number by which another number is to be divided
 * Side Effects - None
 * Error Conditions: divisor is zero
 * Return Value: The remainder
 * 
 * Registers used:
 *	r0 - arg 1 -- dividend, used to store return value of the remainder of
 *	              unsigned division
 *	r1 - arg 2 -- divisor
 *	r2 - Used to store result of unsigned division of dividend by divisor
 *	r3 - Used to store the product of quotient and divisor, used later to
 *	     calculate remainder
 *
 * Stack variables: None
 */
myURem:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Compute the remainder from dividing the dividend by the divisor
	udiv	r2, r0, r1		@ Unsigned division: dividend by divisor
	mul	r3, r2, r1		@ Multiply quotient by divisor;
					@   temporary result into r3
	sub	r0, r0, r3		@ Subtract temporary result from
					@   dividend; remainder into r0

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
