/*
 * Filename: printPattern.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/4/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 24
	.equ	HEX_RESULT_OFFSET, -8
	.equ	BIT_RESULT_OFFSET, -12
	.equ	MASK_HEX_OFFSET, -16
	.equ	MASK_BIT_OFFSET, -20
	.equ	I_OFFSET, -24
	.equ	J_OFFSET, -28

@ Constants for formal parameters
	.equ	PARAM_SPACE, 16
	.equ	PATTERN_OFFSET, -32
	.equ	ON_OFFSET, -36
	.equ	OFF_OFFSET, -40

@ Constants
	.equ	MASK_HEX, 0xFF000000
	.equ	MASK_BIT, 0x80

	.equ	ON_BIT, 0x1

	.equ	NUMBER_OF_BYTES, 4
	.equ	NUMBER_OF_BITS, 8

	.equ	NUM_BYTES_MINUS_ONE, 3

	.equ	NEWLINE_CHAR, '\n'

	.equ	PATTERN_INDEX_TWO, 4

	.equ	BYTE_SIZE, 8
	.equ	BYTE_SIZE_MINUS_ONE, 7

	.global	printPattern	@ Specify printPattern as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: printPattern()
 * Function Prototype: void printPattern( unsigned int pattern[], char on,
 * 				       	  char off );
 * Description: Prints out the pattern as an 8x8 grid. Each bit in pattern will
 * 		represented by a character, with each byte being a row in the
 * 		grid. If the bit is 1, print on, otherwise print off.
 * Parameters: pattern[] - array holding two unsigned hex values
 * 	       on - char printed when particular bit in pattern is 1
 * 	       off - char printed when particular bit in pattern is 0
 * Side Effects - Prints the pattern to stdout as 8x8 grid that prints on when
 * 		  bit is 1, prints off when bit is 0.
 * Error Conditions: None
 * Return Value: None
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[], used various times to store temporary values
 *	r1 - arg 2 -- on, used various times to store temporary values
 *	r2 - arg 3 -- off, used various times to store temporary values
 *	r3 - used various times to store temporary values 
 */
printPattern:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ allocate 6 local vars

	@ Allocate space on stack for formal params
	sub	sp, sp, PARAM_SPACE		@ allocate 3 params

	@ Store formal parameters
	str	r0, [fp, PATTERN_OFFSET] 	@ store param1
	str	r1, [fp, ON_OFFSET]		@ store param2
	str	r2, [fp, OFF_OFFSET]		@ store param3

	@ Initialize local vars
	mov	r3, 0				@ sets r3 to 0
	str	r3, [fp, HEX_RESULT_OFFSET]	@ stores r3 to hexResult

	mov	r3, 0				@ sets r3 to 0
	str	r3, [fp, BIT_RESULT_OFFSET]	@ stores r3 to bitResult

	mov	r3, MASK_HEX			@ sets r3 to 0xFF000000
	str	r3, [fp, MASK_HEX_OFFSET]	@ stores r3 to maskHex

	mov	r3, MASK_BIT			@ sets r3 to 0x80
	str	r3, [fp, MASK_BIT_OFFSET]	@ stores r3 to maskBit

	mov	r3, 0				@ sets r3 to 0
	str	r3, [fp, I_OFFSET]		@ stores r3 to i

	mov	r3, 0				@ sets r3 to 0
	str	r3, [fp, J_OFFSET]		@ stores r3 to j

	@ Set up outer for loop
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	mov	r2, NUMBER_OF_BYTES		@ sets r2 to 4
	cmp	r3, r2				@ compare i with 4
	bge	end_outer_loop			@ branch to end_outer_loop if i
						@   is greater than 4

outer_loop:
	@ Cycle through each byte of pattern[0]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, 0]			@ load pattern[0] to r2
	str	r2, [fp, HEX_RESULT_OFFSET]	@ store r2 to hexResult

	@ Mask hexResult
	ldr	r3, [fp, HEX_RESULT_OFFSET]	@ load hexResult to r3
	ldr	r2, [fp, MASK_HEX_OFFSET]	@ load maskHex to r2
	and	r3, r2, r3			@ and bit operator on hexResult
						@   and maskHex
	str	r3, [fp, HEX_RESULT_OFFSET]	@ store r3 to hexResult

	@ Logical shift right maskHex
	ldr	r3, [fp, MASK_HEX_OFFSET]	@ load maskHex to r3
	lsr	r3, r3, NUMBER_OF_BITS		@ logical shift right maskHex
						@   8 bits
	str	r3, [fp, MASK_HEX_OFFSET]	@ store r3 to maskHex

	@ Logical shift right hexResult
	ldr	r3, [fp, I_OFFSET]		@ load i to r3
	mov	r2, NUM_BYTES_MINUS_ONE		@ sets r2 to 3
	sub	r3, r2, r3			@ subtract i from 3
	mov	r2, BYTE_SIZE			@ sets r2 to 8
	mul	r3, r2, r3			@ multiply 8 with r3
	ldr	r2, [fp, HEX_RESULT_OFFSET]	@ loads hexResult to r2
	lsr	r2, r2, r3			@ logical shift right hexResult
						@   8 * ( 3 - i ) bits
	str	r2, [fp, HEX_RESULT_OFFSET]	@ store r2 to hexResult

	@ Set up inner for loop
	ldr	r3, [fp, J_OFFSET]		@ load j to r3
	mov	r2, BYTE_SIZE			@ sets r2 to 8
	cmp	r3, r2				@ compare j with 8
	bge	end_inner_loop			@ branch to end_inner_loop if j
						@   greater than 8

inner_loop:
	@ Cycle through each bit of every byte
	ldr	r3, [fp, HEX_RESULT_OFFSET]	@ loads hexResult to r3
	str	r3, [fp, BIT_RESULT_OFFSET]	@ sets r3 to bitResult

	@ Mask bitResult
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	ldr	r2, [fp, MASK_BIT_OFFSET]	@ loads maskBit to r2
	and	r3, r2, r3			@ and bit operator on bitResult
						@   and maskBit
	str	r3, [fp, BIT_RESULT_OFFSET]	@ store r3 to bitResult

	@ Logical shift right maskBit
	ldr	r3, [fp, MASK_BIT_OFFSET]	@ load maskBit to r3
	lsr	r3, r3, 1			@ logical shift right maskBit
						@   1 bit
	str	r3, [fp, MASK_BIT_OFFSET]	@ stores r3 to maskBit

	@ Logical shift right bitResult
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	mov	r0, BYTE_SIZE_MINUS_ONE		@ sets r0 to 7
	ldr	r1, [fp, J_OFFSET]		@ loads j to r1
	sub	r2, r0, r1			@ sub 1 from num of bytes to r2
	lsr	r3, r3, r2			@ logical shift right bitResult
						@   7 bits
	str	r3, [fp, BIT_RESULT_OFFSET]	@ stores r3 to bitResult

	@ Calls outputChar with on char if bit is 0x1
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	cmp	r3, ON_BIT			@ compares bitResult with 0x1
	bne	else				@ branch to end_if if not equal
	ldr	r0, [fp, ON_OFFSET]		@ loads on char to r0
	bl	outputChar			@ calls outputChar
	b	end_if				@ always branch to end_if

else:
	@ Calls ouputChar with off char if bit is 0x0
	ldr	r0, [fp, OFF_OFFSET]		@ loads off char to r0
	bl	outputChar			@ calls outputChar

end_if:
	@ Increment j
	ldr	r3, [fp, J_OFFSET]		@ loads j to r3
	add	r3, r3, 1			@ increment j
	str	r3, [fp, J_OFFSET]		@ stores r3 to j

	@ Check inner loop condition
	ldr	r3, [fp, J_OFFSET]		@ loads j to r3
	cmp	r3, BYTE_SIZE 			@ compare r3 with 8
	blt	inner_loop			@ branch to inner_loop if r3 is
						@   less than 8	

end_inner_loop:
	@ Print new line
	mov	r0, NEWLINE_CHAR		@ sets r0 to new line char
	bl	outputChar			@ calls outputChar

	@ Reset j
	ldr	r3, [fp, J_OFFSET]		@ load j to r3
	mov	r3, 0				@ set r3 to 0
	str	r3, [fp, J_OFFSET]		@ store 0 to j

	@ Reset maskBit
	ldr	r3, [fp, MASK_BIT_OFFSET]	@ loads maskBit to r3
	mov	r3, MASK_BIT			@ sets r3 to 0x80
	str	r3, [fp, MASK_BIT_OFFSET]	@ stores r3 to maskBit

	@ Increment i
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	add	r3, r3, 1			@ increment i
	str	r3, [fp, I_OFFSET]		@ stores r3 to i

	@ Check outer loop condition
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	cmp	r3, NUMBER_OF_BYTES		@ compare i with 4
	blt	outer_loop			@ branch to outer_loop with i
						@   is less than 4

end_outer_loop:
	@ Reset i
	ldr	r3, [fp, I_OFFSET]		@ load i to r3
	mov	r3, 0				@ sets r3 to 0
	str	r3, [fp, I_OFFSET]		@ stores 0 to i

	@ Reset maskHex
	ldr	r3, [fp, MASK_HEX_OFFSET]	@ load maskHex to r3
	mov	r3, MASK_HEX			@ sets r3 to maskHex
	str	r3, [fp, MASK_HEX_OFFSET]	@ stores r3 to maskHex

	@ Set up outer for loop
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	mov	r2, NUMBER_OF_BYTES		@ sets r2 to 4
	cmp	r3, r2				@ compare i with 4
	bge	end_outer_loop_1		@ branch to end_outer_loop_1 if
						@   i is greater than 4

outer_loop_1:
	@ Cycle through each byte of pattern[1]
	ldr	r3, [fp, PATTERN_OFFSET]	@ load pattern to r3
	ldr	r2, [r3, PATTERN_INDEX_TWO]	@ load pattern[1] to r2
	str	r2, [fp, HEX_RESULT_OFFSET]	@ store r2 to hexResult

	@ Mask hexResult
	ldr	r3, [fp, HEX_RESULT_OFFSET]	@ load hexResult to r3
	ldr	r2, [fp, MASK_HEX_OFFSET]	@ load maskHex to r2
	and	r3, r2, r3			@ and bit operator on hexResult
						@   and maskHex
	str	r3, [fp, HEX_RESULT_OFFSET]	@ store r3 to hexResult

	@ Logical shift right maskHex
	ldr	r3, [fp, MASK_HEX_OFFSET]	@ load maskHex to r3
	lsr	r3, r3, NUMBER_OF_BITS		@ logical shift right maskHex
						@   8 bits
	str	r3, [fp, MASK_HEX_OFFSET]	@ store r3 to maskHex

	@ Logical shift right hexResult
	ldr	r3, [fp, I_OFFSET]		@ load i to r3
	mov	r2, NUM_BYTES_MINUS_ONE		@ sets r2 to 3
	sub	r3, r2, r3			@ subtract i from 3
	mov	r2, BYTE_SIZE			@ sets r2 to 8
	mul	r3, r2, r3			@ multiply 8 with r3
	ldr	r2, [fp, HEX_RESULT_OFFSET]	@ loads hexResult to r2
	lsr	r2, r2, r3			@ logical shift right hexResult
						@   8 * ( 3 - i ) bits
	str	r2, [fp, HEX_RESULT_OFFSET]	@ store r2 to hexResult

	@ Set up inner for loop
	ldr	r3, [fp, J_OFFSET]		@ load j to r3
	mov	r2, BYTE_SIZE			@ sets r2 to 8
	cmp	r3, r2				@ compare j with 8
	bge	end_inner_loop_1		@ branch to end_inner_loop_1 if
						@   j greater than 8

inner_loop_1:
	@ Cycle through each bit of every byte
	ldr	r3, [fp, HEX_RESULT_OFFSET]	@ loads hexResult to r3
	str	r3, [fp, BIT_RESULT_OFFSET]	@ sets r3 to bitResult

	@ Mask bitResult
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	ldr	r2, [fp, MASK_BIT_OFFSET]	@ loads maskBit to r2
	and	r3, r2, r3			@ and bit operator on bitResult
						@   and maskBit
	str	r3, [fp, BIT_RESULT_OFFSET]	@ store r3 to bitResult

	@ Logical shift right maskBit
	ldr	r3, [fp, MASK_BIT_OFFSET]	@ load maskBit to r3
	lsr	r3, r3, 1			@ logical shift right maskBit
						@   1 bit
	str	r3, [fp, MASK_BIT_OFFSET]	@ stores r3 to maskBit

	@ Logical shift right bitResult
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	mov	r0, BYTE_SIZE_MINUS_ONE		@ sets r0 to 7
	ldr	r1, [fp, J_OFFSET]		@ loads j to r1
	sub	r2, r0, r1			@ sub 1 from num of bytes to r2
	lsr	r3, r3, r2			@ logical shift right bitResult
						@   7 bits
	str	r3, [fp, BIT_RESULT_OFFSET]	@ stores r3 to bitResult

	@ Calls outputChar with on char if bit is 0x1
	ldr	r3, [fp, BIT_RESULT_OFFSET]	@ loads bitResult to r3
	cmp	r3, ON_BIT			@ compares bitResult with 0x1
	bne	else_1				@ branch to end_if if not equal
	ldr	r0, [fp, ON_OFFSET]		@ loads on char to r0
	bl	outputChar			@ calls outputChar
	b	end_if_1			@ always branch to
						@  end_if_1

else_1:
	@ Calls ouputChar with off char if bit is 0x0
	ldr	r0, [fp, OFF_OFFSET]		@ loads off char to r0
	bl	outputChar			@ calls outputChar

end_if_1:
	@ Increment j
	ldr	r3, [fp, J_OFFSET]		@ loads j to r3
	add	r3, r3, 1			@ increment j
	str	r3, [fp, J_OFFSET]		@ stores r3 to j

	@ Check inner loop condition
	ldr	r3, [fp, J_OFFSET]		@ loads j to r3
	cmp	r3, BYTE_SIZE 			@ compare r3 with 8
	blt	inner_loop_1			@ branch to inner_loop_1 if r3
						@   is less than 8	

end_inner_loop_1:
	@ Print new line
	mov	r0, NEWLINE_CHAR		@ sets r0 to new line char
	bl	outputChar			@ calls outputChar

	@ Reset j
	ldr	r3, [fp, J_OFFSET]		@ load j to r3
	mov	r3, 0				@ set r3 to 0
	str	r3, [fp, J_OFFSET]		@ store 0 to j

	@ Reset maskBit
	ldr	r3, [fp, MASK_BIT_OFFSET]	@ loads maskBit to r3
	mov	r3, MASK_BIT			@ sets r3 to 0x80
	str	r3, [fp, MASK_BIT_OFFSET]	@ stores r3 to maskBit

	@ Increment i
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	add	r3, r3, 1			@ increment i
	str	r3, [fp, I_OFFSET]		@ stores r3 to i

	@ Check outer loop condition
	ldr	r3, [fp, I_OFFSET]		@ loads i to r3
	cmp	r3, NUMBER_OF_BYTES		@ compare i with 4
	blt	outer_loop_1			@ branch to outer_loop_1 with i
						@   is less than 4

end_outer_loop_1:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@   for return
