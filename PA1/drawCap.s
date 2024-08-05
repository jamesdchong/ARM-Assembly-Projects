/*
 * Filename: drawCap.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/18/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 32
	.equ	TIP_CHAR_OFFSET, -8
	.equ	LEFT_SLASH_CHAR_OFFSET, -12
	.equ	RIGHT_SLASH_CHAR_OFFSET, -16
	.equ	START_ITER_OFFSET, -20
	.equ	END_ITER_OFFSET, -24
	.equ	INCR_OFFSET, -28
	.equ	CAP_SIZE_OFFSET, -32
	.equ	I_OFFSET, -36

@ Constants for parameters
	.equ	PARAM_SPACE, 16
	.equ	SIZE_OFFSET, -40
	.equ	FILL_CHAR_OFFSET, -44
	.equ	DIRECTION_OFFSET, -48

@ Constants
	.equ	HALF_DIVISOR, 2	@ Used for dividing variable size in half
	.equ	DOUBLE, 2	@ Used for doubling values

	.equ	DIR_UP, 0	@ Cool S cap up direction
	.equ	DIR_DOWN, 1	@ Cool S cap down direction

@ Cool S whitespace, tip, and border characters
	.equ	SPACE_CHAR, ' '
	.equ	NEWLINE_CHAR, '\n'
	.equ	FORWARD_SLASH_CHAR, '/'
	.equ	BACK_SLASH_CHAR, '\\'
	.equ	CARAT_CHAR, '^'
	.equ	V_CHAR, 'v'

	.global	drawCap		@ Specify drawCap as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: drawCap()
 * Function Prototype: void drawCap( int size, char fillChar, int direction );
 * Description: Prints out individual characters such that the Cool S caps will
 * 		be displayed based on the user-supplied values.
 * Parameters: size - size of the cool s
 * 	       fillChar - the character used to draw the cool s
 * 	       direction - direction of cool s: up if 0, down if 1
 * Side Effects - prints Cool S cap to stdout
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- size, used various times to store temporary values
 *	r1 - arg 2 -- fillChar, used various times to store temporary values
 *	r2 - arg 3 -- direction, used various times to store temporary values
 *	r3 - used for storing local vars and formal params onto stack
 */
drawCap:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ Allocate 8 int local variables

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ Allocate space for r0-r2

	str	r0, [fp, SIZE_OFFSET]		@ store param1
	str	r1, [fp, FILL_CHAR_OFFSET]	@ store param2
	str	r2, [fp, DIRECTION_OFFSET]	@ store param3

	@ Update capSize var
	mov	r1, HALF_DIVISOR		@ store HALF_DIVISOR into r1
	ldr	r0, [fp, SIZE_OFFSET]		@ load size to r0
	sdiv	r3, r0, r1			@ capSize = size / HALF_DIVISOR
	str	r3, [fp, CAP_SIZE_OFFSET]	@ store capSize

	@ Drawing the top cap
	ldr	r2, [fp, DIRECTION_OFFSET]	@ load direction to r2
	cmp	r2, DIR_UP			@ Compare direction with up dir
	bne	else_1				@ Branch to else_1 if not equal

	mov	r3, CARAT_CHAR			@ store carat char to r3
	str	r3, [fp, TIP_CHAR_OFFSET]	@ store r3 into tipChar

	mov	r3, FORWARD_SLASH_CHAR			@ store forward slash
							@   char to r3
	str	r3, [fp, LEFT_SLASH_CHAR_OFFSET]	@ store r3 into
							@   leftSlashChar

	mov	r3, BACK_SLASH_CHAR			@ store back slash char
							@   to r3
	str	r3, [fp, RIGHT_SLASH_CHAR_OFFSET]	@ store r3 into
							@   rightSlashChar
	
	mov	r3, 0				@ store 0 to r3
	str	r3, [fp, START_ITER_OFFSET]	@ store r3 into startIter

	ldr	r3, [fp, CAP_SIZE_OFFSET]	@ load capSize to r3
	add	r3, r3, 1			@ add capSize plus 1; store r3
	str	r3, [fp, END_ITER_OFFSET]	@ store r3 into endIter

	mov	r3, 1				@ store 1 to r3
	str	r3, [fp, INCR_OFFSET]		@ store r3 into incr

	b	end_if_1			@ branch to end_if_1

else_1:
@ Else block
	mov	r3, V_CHAR			@ store v char to r3
	str	r3, [fp, TIP_CHAR_OFFSET]	@ store r3 into tipChar

	mov	r3, BACK_SLASH_CHAR			@ store back slash char
							@   to r3
	str	r3, [fp, LEFT_SLASH_CHAR_OFFSET]	@ store r3 into
							@   leftSlashChar

	mov	r3, FORWARD_SLASH_CHAR			@ store forward slash
							@   char to r3
	str	r3, [fp, RIGHT_SLASH_CHAR_OFFSET]	@ store r3 into
							@   rightSlashChar

	ldr	r3, [fp, CAP_SIZE_OFFSET]	@ load capSize to r3
	str	r3, [fp, START_ITER_OFFSET]	@ store r3 to startIter

	mov	r3, -1				@ store -1 to r3
	str	r3, [fp, END_ITER_OFFSET]	@ store r3 into endIter

	mov	r3, -1				@ store -1 to r3
	str	r3, [fp, INCR_OFFSET]		@ store r3 into incr

end_if_1:
	@ Start drawing the cap
	ldr	r3, [fp, START_ITER_OFFSET]	@ load startIter to r3
	str	r3, [fp, I_OFFSET]		@ store r3 to i

	ldr	r0, [fp, I_OFFSET]		@ load i to r0
	ldr	r1, [fp, END_ITER_OFFSET]	@ load endIter to r1
	cmp	r0, r1				@ compare r0 and r1
	beq	end_loop			@ if r0 and r1 are equal, branch
						@   to end_loop

loop:
	@ Draw the leading whitespace
	mov	r0, SPACE_CHAR			@ store space char to r0
	ldr	r1, [fp, CAP_SIZE_OFFSET]	@ load capSize to r1
	ldr	r2, [fp, I_OFFSET]		@ load i to r2
	sub	r1, r1, r2			@ subtract i from capSize; store
						@   to r1
	bl	outputCharNTimes		@ call function with params in
						@   r0, r1

	@ Draw the actual cap content, conditionally the tip if it's the
	@   first/last iteration
	ldr	r3, [fp, I_OFFSET]		@ load i to r3
	cmp	r3, 0				@ compare r3 with 0
	bne	else_2				@ if r3 and 0 is not equal,
						@   branch to else_2
	ldr	r0, [fp, TIP_CHAR_OFFSET]	@ load tipChar to r0
	bl	outputChar			@ call function with param in r0
	b	end_if_2			@ branch to the end of the
						@   if-else statement

else_2:
	ldr	r0, [fp, LEFT_SLASH_CHAR_OFFSET]	@ load left slash char
							@   to r0

	bl	outputChar			@ call function with param in r0
	ldr	r0, [fp, FILL_CHAR_OFFSET]	@ load fillChar to r0
	ldr	r3, [fp, I_OFFSET]		@ load i to r3
	mov	r2, DOUBLE			@ store DOUBLE into r2
	mul	r1, r2, r3			@ multiply r2 times r3
	sub	r1, r1, 1			@ subtract 1 from r1,store in r1
	bl	outputCharNTimes		@ call function with params in
						@   r0, r1

	ldr	r0, [fp, RIGHT_SLASH_CHAR_OFFSET]	@ load right slash char
							@   to r0
	bl	outputChar				@ call function with
							@   param in r0

end_if_2:
	@ Draw the trailing whitespace
	mov	r0, SPACE_CHAR			@ store space char into r0
	ldr	r1, [fp, CAP_SIZE_OFFSET]	@ load capSize into r1
	ldr	r2, [fp, I_OFFSET]		@ load i into r2
	sub	r1, r1, r2			@ subtract r2 from r1
	bl	outputCharNTimes		@ calls function with params in
						@   r0, r1
	mov	r0, NEWLINE_CHAR		@ stores newline char in r0
	bl	outputChar			@ call function with param in r0

	@ Increment i with incr
	ldr	r2, [fp, I_OFFSET]		@ load i into r2
	ldr	r3, [fp, INCR_OFFSET]		@ load incr into r3
	add	r2, r2, r3			@ add i and incr, store in r2
	str	r2, [fp, I_OFFSET]		@ store r2 to i

	@ Check loop condition
	ldr	r0, [fp, I_OFFSET]		@ load i into r0
	ldr	r1, [fp, END_ITER_OFFSET]	@ load endIter into r1
	cmp	r0, r1				@ compare i and endIter
	bne	loop				@ branch to loop if not equal

end_loop:
@ End of loop

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
