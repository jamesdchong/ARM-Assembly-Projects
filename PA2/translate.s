/*
 * Filename: translate.s
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
	.equ	PARAM_SPACE, 16
	.equ	PATTERN_OFFSET, -8
	.equ	H_OFFSET_OFFSET, -12
	.equ	V_OFFSET_OFFSET, -16

	.global	translate	@ Specify translate as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: translate()
 * Function Prototype: void translate( unsigned int pattern[], int hOffset,
 * 				       int vOffset );
 * Description: Translates pattern horizontally with hOffset and vertically with
 * 		vOffset. A translation is the same as scrolling the image, but
 * 		scrolling can go in both directions (horizontal and vertical).
 * 		The same positive/negative offset and wrapping rules apply as in
 * 		scrollHorizontal and scrollVertical.
 * Parameters: pattern[] - array holding two unsigned hex values
 * 	       hOffset - translates pattern horizontally
 * 	       vOffset - translates pattern vertically
 * Side Effects - None
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[], used to hold pattern and pass to both
 *		      scrollHorizontal and scrollVertical
 *	r1 - arg 2 -- hOffset, used to hold hOffset when calling
 *		      scrollHorizontal and hold vOffset when calling
 * 		      scrollVertical
 *	r2 - arg 3 -- vOffset
 */
translate:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for formal params
	sub	sp, sp, PARAM_SPACE		@ allocate space for params

	@ Store formal params
	str	r0, [fp, PATTERN_OFFSET]	@ store param1
	str	r1, [fp, H_OFFSET_OFFSET]	@ store param2
	str	r2, [fp, V_OFFSET_OFFSET]	@ store param3

	@ Scroll horizontally with hOffset
	ldr	r0, [fp, PATTERN_OFFSET]	@ loads pattern to r0
	ldr	r1, [fp, H_OFFSET_OFFSET]	@ loads hOffset to r1
	bl	scrollHorizontal		@ calls scrollHorizontal

	@ Scroll vertically with vOffset
	ldr	r0, [fp, PATTERN_OFFSET]	@ loads pattern to r0
	ldr	r1, [fp, V_OFFSET_OFFSET]	@ loads vOffset to r1
	bl	scrollVertical			@ calls scrollVertical

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
