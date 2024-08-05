/*
 * Filename: isDividable.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

	.global	isDividable	@ Specify isDividable as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: isDividable()
 * Function Prototype: int isDividable( int dividend, int divisor );
 * Description: Tests if the dividend is evenly dividable by the divisor
 * Parameters: dividend - number to be divided by another number
 *             divisor - number by which another number is to be divided
 * Side Effects - None
 * Error Conditions: If the divisor is 0, return -1.
 * Return Value: -1 if error, 1 if dividable, 0 if not dividable
 * 
 * Registers used:
 *	r0 - arg 1 -- dividend,  and ultimately holds the return value of -1 if
 *	the divisor is 0, 0 if the division does not divide evenly, and 1 if
 * 	the division divides evenly
 *	r1 - arg 2 -- divisor
 *	r2 - temporary register for holding the return value of 0, 1, or -1
 */
isDividable:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Checks if divisor is 0
	mov	r2, -1			@ Initially sets r2 to -1
	cmp	r1, 0			@ Compares divisor to 0
	beq	epilogue		@ If the divisor is 0, return -1

	@ Calls myRem to calculate the remainder of the division
	bl	myRem			@ Calls myRem function, storing
					@   remainder in r0

	@ If the remainder calculated evenly divides, set r2 to 1
	mov	r2, 1			@ Sets r2 to 1
	cmp	r0, 0			@ Checks to see if it divides evenly
					@   (remainder is 0)
	beq	epilogue		@ If it divides evenly, return 1

	@ If the remainder calculated does not evenly divide, set r2 to 0
	mov	r2, 0			@ Sets r2 to 0 if the divisor is not 0
					@   and it does not divide evenly

epilogue:
	@ Serves as a branch to skip to when returning value early
	mov	r0, r2			@ Moves the contents of r2 into r0,
					@   whether it is 1, 0, or -1

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
