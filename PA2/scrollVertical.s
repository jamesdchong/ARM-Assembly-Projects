/*
 * Filename: scrollVertical.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 24
	.equ	LSB_ONE_OFFSET, -8
	.equ	LSB_TWO_OFFSET, -12
	.equ	MSB_ONE_OFFSET, -16
	.equ	MSB_TWO_OFFSET, -20
	.equ	I_OFFSET, -24

@ Constants for formal parameters
	.equ	PARAM_SPACE, 8
	.equ	PATTERN_OFFSET, -32
	.equ	OFFSET_OFFSET, -36

@ Constants
	.equ	SHIFT_LSB, 24
	.equ	SHIFT_MSB, 24
	.equ	SHIFT_PATTERN, 8
	.equ	PATTERN_ELEMENT_OFFSET, 4
	.equ	MSB_MASK, 0xFF000000
	.equ	LSB_MASK, 0x000000FF

	.global	scrollVertical	@ Specify scrollVertical as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: scrollVertical()
 * Function Prototype: void scrollVertical( unsigned int pattern[],
 *                                          int offset );
 * Description: Scroll pattern vertically based on offset. If offset is
 * 		positive, scroll down and wrap the bits around to the top. If
 * 		offset is negative, scroll up and wrap the bits around to the
 * 		bottom.
 * Parameters: pattern[] - two element array holding two halves of a pattern
 *             offset - number of positions
 * Side Effects: None 
 * Error Conditions: None
 * Return Value: None
 *
 * Registers used:
 *	r0 - arg 1 -- pattern[], used various times to use and store temporary
 *		      values
 *	r1 - arg 2 -- offset, used various times to use and store temporary
 *		      values
 *	r2 - used for accessing and storing individual elements of pattern array
 *	r3 - used for accessing and storing pattern array
 */
scrollVertical:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ allocate 3 local vars

	@ Allocate space of stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ allocate space for r0-r1

	@ Store formal parameters
	str	r0, [fp, PATTERN_OFFSET]	@ store param1
	str	r1, [fp, OFFSET_OFFSET]		@ store param2

	@ Check if offset is positive or negative and branch respectively
	ldr	r3, [fp, OFFSET_OFFSET]		@ load offset into r3
	cmp	r3, 0				@ see if r3 is neg or pos
	blt	negative_offset			@ branch to negative_offset if
						@   offset is negative

positive_offset:
	@ Set up for loop
	mov	r3, 0				@ set r3 to 0
	str	r3, [fp, I_OFFSET]		@ i = 0;

	ldr	r2, [fp, I_OFFSET]		@ get current value of i
	ldr	r3, [fp, OFFSET_OFFSET]		@ get value of offset
	cmp	r2, r3				@ compare i with offset
	bge	end_loop			@ branch to end_loop if i is
						@   greater than offset

loop_1:
	@ Mask pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, 0]			@ load first element of pattern
						@   to r2
	ldr	r1, =LSB_MASK			@ load LSB mask to r1
	and	r1, r2, r1			@ use and bit operator to obtain
						@   LSB of pattern[0]
	str	r1, [fp, LSB_ONE_OFFSET]	@ store into first LSB

	@ Logical shift left first LSB
	ldr	r3, [fp, LSB_ONE_OFFSET]	@ load first LSB to r3
	lsl	r3, r3, SHIFT_LSB		@ shift first LSB 24 bits to
						@   left
	str	r3, [fp, LSB_ONE_OFFSET]	@ store r3 to first LSB
	
	@ Mask pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	ldr	r1, =LSB_MASK			@ load LSB mask to r1
	and	r1, r2, r1			@ use and bit operator to obtain
						@   LSB of pattern[1]
	str	r1, [fp, LSB_TWO_OFFSET]	@ store into second LSB

	@ Logical shift left second LSB
	ldr	r3, [fp, LSB_TWO_OFFSET]	@ load second LSB to r3
	lsl	r3, r3, SHIFT_LSB		@ shift second LSB 24 bits to
						@   left
	str	r3, [fp, LSB_TWO_OFFSET]	@ store r3 to second LSB

	@ Logical shift right pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, 0]			@ load first element of pattern
	lsr	r2, r2, SHIFT_PATTERN		@ logical shift right pattern[0]
						@   8 bits to the right
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r2, [r3, 0]			@ store r2 to first element of
						@   pattern
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern

	@ Add second LSB to pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, 0]			@ load first element of pattern
	ldr	r1, [fp, LSB_TWO_OFFSET]	@ load second LSB to r1
	orr	r0, r2, r1			@ use or bit operator to obtain
						@   scrolled pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r0, [r3, 0]			@ store r0 to pattern[0]
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern array

	@ Logical shift right pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	lsr	r2, r2, SHIFT_PATTERN		@ logical shift right pattern[1]
						@   8 bits to the right
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ store r2 into second
							@   element of pattern
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern
	
	@ Add first LSB to pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	ldr	r1, [fp, LSB_ONE_OFFSET]	@ load first LSB to r1
	orr	r0, r2, r1			@ use or bit operator to obtain
						@   scrolled pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r0, [r3, PATTERN_ELEMENT_OFFSET]	@ store r0 to second
							@   element of pattern
	str	r3, [fp, PATTERN_OFFSET]	@ store second element of
						@   pattern to pattern

	@ Increment i
	ldr	r3, [fp, I_OFFSET]		@ get current value of i
	add	r3, r3, 1			@ increment i
	str	r3, [fp, I_OFFSET]		@ store r3 to i

	@ Check if loop needs to be run again
	ldr	r2, [fp, I_OFFSET]		@ get current value of i
	ldr	r3, [fp, OFFSET_OFFSET]		@ get value of offset
	cmp	r2, r3				@ compare i and offset
	blt	loop_1				@ branch back to loop_1 if i is
						@   less than offset

end_loop_1:
	b	end				@ branch to the end

negative_offset:
	@ Set up for loop
	mov	r3, 0				@ set r3 to 0
	str	r3, [fp, I_OFFSET]		@ i = 0;

	ldr	r3, [fp, OFFSET_OFFSET]		@ load offset to r3
	mov	r2, -1				@ set r2 to -1
	mul	r3, r3, r2			@ make offset positive
	str	r3, [fp, OFFSET_OFFSET]		@ store r3 to offset
	ldr	r2, [fp, I_OFFSET]		@ load i to r2
	cmp	r2, r3				@ compare i and offset
	bge	end_loop			@ branch to end_loop if i is 
						@   greater than offset

loop_2:
	@ Mask pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, 0]			@ load first element of pattern
						@   to r2
	ldr	r1, =MSB_MASK			@ load MSB mask to r1
	and	r1, r2, r1			@ use and bit operator to obtain
						@   LSB of pattern[0]
	str	r1, [fp, MSB_ONE_OFFSET]	@ store into first MSB

	@ Logical shift right first MSB
	ldr	r3, [fp, MSB_ONE_OFFSET]	@ load first MSB to r3
	lsr	r3, r3, SHIFT_MSB		@ shift first LSB 24 bits to
						@   right
	str	r3, [fp, MSB_ONE_OFFSET]	@ store r3 to first MSB
	
	@ Mask pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	ldr	r1, =MSB_MASK			@ load MSB mask to r1
	and	r1, r2, r1			@ use and bit operator to obtain
						@   MSB of pattern[1]
	str	r1, [fp, MSB_TWO_OFFSET]	@ store into second MSB

	@ Logical shift right second MSB
	ldr	r3, [fp, MSB_TWO_OFFSET]	@ load second MSB to r3
	lsr	r3, r3, SHIFT_MSB		@ shift second MSB 24 bits to
						@   right
	str	r3, [fp, MSB_TWO_OFFSET]	@ store r3 to second MSB

	@ Logical shift left pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, 0]			@ load first element of pattern
	lsl	r2, r2, SHIFT_PATTERN		@ logical shift left pattern[0]
						@   8 bits to the left
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r2, [r3, 0]			@ store r2 into first element of
						@   pattern
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern
	
	@ Add second MSB to pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, 0]			@ load first element of pattern
	ldr	r1, [fp, MSB_TWO_OFFSET]	@ load second MSB to r1
	orr	r0, r2, r1			@ use or bit operator to obtain
						@   scrolled pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r0, [r3, 0]			@ store r0 to pattern[0]
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern array

	@ Logical shift left pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	lsl	r2, r2, SHIFT_PATTERN		@ logical shift left pattern[1]
						@   8 bits to the left
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ store r2 to pattern[1]
	str	r3, [fp, PATTERN_OFFSET]	@ store r3 to pattern
	
	@ Add first MSB to pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	ldr	r2, [r3, PATTERN_ELEMENT_OFFSET]	@ load second element of
							@   pattern to r2
	ldr	r1, [fp, MSB_ONE_OFFSET]	@ load first MSB to r1
	orr	r0, r2, r1			@ use or bit operator to obtain
						@   scrolled pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern into r3
	str	r0, [r3, PATTERN_ELEMENT_OFFSET]	@ store r0 to second
							@   element of pattern
	str	r3, [fp, PATTERN_OFFSET]	@ store second element of
						@   pattern to pattern
	@ Increment i
	ldr	r3, [fp, I_OFFSET]		@ get current value of i
	add	r3, r3, 1			@ increment i
	str	r3, [fp, I_OFFSET]		@ store r3 to i

	@ Check if loop needs to be run again
	ldr	r2, [fp, I_OFFSET]		@ get current value of i
	ldr	r3, [fp, OFFSET_OFFSET]		@ get value of offset
	cmp	r2, r3				@ compare i and offset
	blt	loop_2				@ branch back to loop_2 if i is
						@   less than offset

end_loop:
	b	end				@ branch to the end

end:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
