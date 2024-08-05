/*
 * Filename: intervalContains.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.global	intervalContains	@ Specify intervalContains as global
					@   symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: intervalContains()
 * Function Prototype: int intervalContains( int start, int end, int value );
 * Description: Determines whether or not value is inside the interval
 *		[start, end]. This interval is inclusive on both ends
 * Parameters: start - beginning of the interval
 *	       end - end of the interval
 * 	       value - value passed in to see if it is within the interval
 * Side Effects - None
 * Error Conditions: If start is greater than end, return -1 for error
 * Return Value: -1 if interval is invalid, 1 if value in within the interval, 0
 * if value is not within the interval
 * 
 * Registers used:
 *	r0 - arg 1 -- start, and holds return value of 0 if value is not with
 *	interval, 1 if it is within the interval, or -1 if end is less than
 *	start, ultimately holding the return value of the function
 *	r1 - arg 2 -- end
 *	r2 - arg 3 -- value
 *	r3 - temporary holding register for the return value of 0, 1, or -1
 */
intervalContains:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Checks valid start and end values
	mov	r3, -1			@ Sets r3 to -1
	cmp	r1, r0			@ Compare start with end value
	blt	epilogue		@ If end is less than start, return -1

	@ Checks valid value greater than start
	mov	r3, 0			@ Sets r3 to 0
	cmp	r2, r0			@ Compare value with start
	blt	epilogue		@ If the value is less than start,
					@   return 0

	@ Checks valid value less than end
	mov	r3, 0			@ Sets r3 to 0
	cmp	r2, r1			@ Compare value with end
	bgt	epilogue		@ If the value is greater than end,
					@   return 0

	@ If valid, start, end and value, return 1
	mov	r3, 1			@ If end is greater than or equal to
					@   start and the value is within the
					@   interval, return 1

epilogue:
	@ Serves a branch to skip to when returning value early
	mov	r0, r3			@ Moves the contents of r3 into r0,
					@   whether it is 1, 0, or -1

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
