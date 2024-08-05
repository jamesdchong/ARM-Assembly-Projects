/*
 * Filename: outputChar.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

	.section	.rodata		@ Put string literal into code

fmt:	.asciz "%c"			@ Format String

	.global	outputChar		@ Specify outputChar as global symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: outputChar()
 * Function Prototype: void outputChar( char ch );
 * Description: Prints the ch to stdout
 * Parameters: ch - character passed in to be printed out
 * Side Effects - outputChar prints to stdout
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- character ch, and stores address of format char
 *	r1 - stores the character ch
 */
outputChar:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Sends ch to printf to be printed to stdout
	mov	r1, r0			@ Moves char param to r1 as arg to
					@   printf
	ldr	r0, =fmt		@ Gets address of format string
	bl	printf			@ Callls printf

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
