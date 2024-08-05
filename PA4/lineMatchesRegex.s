/*
 * Filename: lineMatchesRegex.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

@ Constants for formal parameters
	.equ	PARAM_SPACE, 8
	.equ	PATTERN_OFFSET, -8
	.equ	LINE_OFFSET, -12

@ Constants for extra arguments
	.equ	ARG_SPACE, 8
	.equ	ARG_FIVE_OFFSET, 0

	.global	lineMatchesRegex	@ Specify lineMatchesRegex as global
					@   symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: lineMatchesRegex()
 * Function Prototype: int lineMatchesRegex( const regex_t * pattern
 * 					     const char * line );
 * Description: Checks if a line matches the regex pattern by calling
 *              regexec( pattern, line, 0, 0, 0 ).
 * Parameters: pattern - regex pattern
 * 	       line - string to check if matches pattern
 * Side Effects - None
 * Error Conditions: None
 * Return Value: 1 if the line matches the regex pattern, otherwise return 0
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern, used to load and store value of pattern, also
 *           stores return value
 *	r1 - arg 2 -- line, used to load and store value of line
 *	r2 - used to store 3rd argument of regexec call
 *	r3 - used to store 4th argument of regexec call
 *
 * Stack variables:
 *   pattern - [fp -8] -- regex pattern
 *   line - [fp -12] -- string to check if pattern matches it
 *   arg5 - [sp 0] -- 5th argument of regexec call
 */
lineMatchesRegex:
@ Standard Prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ Allocate 2 formal parameters

	@ Allocate space on stack for extra arguments
	sub	sp, sp, ARG_SPACE		@ Allocate 1 extra argument

	@ Store formal parameters
	str	r0, [fp, PATTERN_OFFSET]	@ store r0 to pattern
	str	r1, [fp, LINE_OFFSET]		@ store r1 to line

	@ Store extra argument
	mov	r3, 0				@ set r3 to 0
	str	r3, [sp, ARG_FIVE_OFFSET]	@ store r3 to arg 5

	@ Load arguments to pass into regexec()
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern to r0
	ldr	r1, [fp, LINE_OFFSET]		@ load line to r1
	mov	r2, 0				@ set r2 to 0
	mov	r3, 0				@ set r3 to 0

	bl	regexec				@ call regexec with register and
						@   5th arg on stack

	@ If regexec returns 0, return 1
	cmp	r0, 0				@ compare regexec return value
						@   with 0
	bne	noMatch				@ if no match, branch to noMatch
	mov	r0, 1				@ set return value to 1
	b	epilogue			@ branch to epilogue

noMatch:
	@ If regexec returns 1, return 0
	mov	r0, 0				@ set r0 to 0

epilogue:
@ Standard Epilogue
	sub	sp, fp, FP_OFFSET		@ set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
