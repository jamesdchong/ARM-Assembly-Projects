/*
 * Filename: compareWordData.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/11/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Our Raspberry Pi
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 8
	.equ	RESULT_OFFSET, -8

@ Constants for formal parameters
	.equ	PARAM_SPACE, 8
	.equ	W1_OFFSET, -16
	.equ	W2_OFFSET, -20

@ Constants
	.equ	MAX_WORD_SIZE, 48

	.global	compareWordData		@ Specify compareWordData as global
					@   symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: compareWordData()
 * Function Prototype: int compareWordData( const void * w1, const void * w2 );
 * Description: First, compares wordData_t's hash values, and if they have the
 * 		same hash value, then compare wordData_t's words using strncmp.
 * Parameters: w1 - wordData_t pointer to be compared to w2
 * 	       w2 - wordData_t pointer to be compared to w1
 * Side Effects - None
 * Error Conditions: None
 * Return Value: -1 if:
 * 		   the wordData_t that w1 points to has a smaller hashValue
 * 		   than the wordData_t that w2 points to, or the hashValues
 * 		   are the same but strncmp returns a value < 0.
 * 		 1 if:
 * 		   the wordData_t that w1 points to has a larger hashValue than
 * 		   the wordData_t that w2 points to, or the hasValues are the
 * 		   same but strncmp returns a value > 0.
 * 		 0 if:
 * 		   the hasValues are the same and strncmp returns 0.
 * 
 * Registers used:
 *	r0 - arg 1 -- w1, used to pass in arguments for function calls, holds
 *	     return value at end of program
 *	r1 - arg 2 -- w2, used to pass in arguments for function calls
 *	r2 - loads address, hashValue, word of w2, address and value of
 *	     wordData_t values, used for comparisons
 *	r3 - loads address, hashValue, word of w1, address and value of
 * 	     wordData_t values, used for comparisons
 *
 * Stack variables:
 * 	result - [fp -8] -- stores return value of strncmp
 * 	w1 - [fp -16] -- wordData_t pointer param to be compared to w2
 * 	w2 - [fp -20] -- wordData_t pointer param to be compared to w1
 */
compareWordData:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Allocate space on stack for local variables
	sub	sp, sp, LOCAL_VAR_SPACE	@ allocate 1 local var

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE	@ allocate 2 formal params

	@ Store formal parameters
	str	r0, [fp, W1_OFFSET]	@ store w1
	str	r1, [fp, W2_OFFSET]	@ store w2

	@ Check if w1's hash is smaller than w2's hash
	ldr	r3, =G_HASHVALUE_OFFSET	@ load address of hashValue
	ldr	r3, [r3]		@ load value of hashValue
	ldr	r0, [fp, W1_OFFSET]	@ load address of w1
	ldr	r3, [r0, r3]		@ load w1->hashValue to r3

	ldr	r2, =G_HASHVALUE_OFFSET	@ load address of hashValue
	ldr	r2, [r2]		@ load value of hashValue
	ldr	r1, [fp, W2_OFFSET]	@ load address of w2
	ldr	r2, [r1, r2]		@ load w2->hashValue to r2

	cmp	r3, r2			@ compare r3 and r2
	bhs	outer_if		@ branch to outer_if if r3 higher or
					@   same as r2

	mov	r0, -1			@ set -1 to return value r0
	b	epilogue		@ branch to epilogue

outer_if:
	@ Check if w1's hash is less than w2's hash
	ldr	r3, =G_HASHVALUE_OFFSET	@ load address of hashValue
	ldr	r3, [r3]		@ load value of hashValue
	ldr	r0, [fp, W1_OFFSET]	@ load address of w1
	ldr	r3, [r0, r3]		@ load w1->hashValue to r3

	ldr	r2, =G_HASHVALUE_OFFSET	@ load address of hashValue
	ldr	r2, [r2]		@ load value of hashValue
	ldr	r1, [fp, W2_OFFSET]	@ load address of w2
	ldr	r2, [r1, r2]		@ load w2->hashValue to r2
	cmp	r3, r2			@ compare r3 and r2
	bls	else			@ branch to else if r3 higher or same as
					@   r2

	mov	r0, 1			@ set 1 to return value r0
	b	epilogue		@ branch to epilogue

else:
	@ If strncmp < 0, return -1
	ldr	r0, [fp, W1_OFFSET]	@ load address of w1
	
	ldr	r1, [fp, W2_OFFSET]	@ load address of w2

	mov	r2, MAX_WORD_SIZE	@ set r2 to 48
	bl	strncmp			@ call strncmp
	str	r0, [fp, RESULT_OFFSET]	@ store result of function call to
					@   result

	ldr	r3, [fp, RESULT_OFFSET]	@ load result
	mov	r2, 0			@ set r2 to 0
	cmp	r3, r2			@ compare r3 and r2
	bge	inner_if		@ branch to inner_if if r3 higher or
					@   same as r2
	mov	r0, -1			@ set -1 to return value r0
	b	epilogue		@ branch to epilogue

inner_if:
	@ If strncmp > 0, return 1
	ldr	r0, [fp, W1_OFFSET]	@ load address of w1

	ldr	r1, [fp, W2_OFFSET]	@ load address of w2

	mov	r2, MAX_WORD_SIZE	@ set r2 to 48
	bl	strncmp			@ call strncmp
	str	r0, [fp, RESULT_OFFSET]	@ store result of function call to
					@   result

	ldr	r3, [fp, RESULT_OFFSET]	@ load result to r3
	mov	r2, 0			@ set r2 to 0
	cmp	r3, r2			@ compare r3 and r2
	ble	else_1			@ branch to else_1 if r3 lower or same
					@   as r2

	mov	r0, 1			@ set 1 to return value r0
	b	epilogue		@ branch to epilogue

else_1:
	@ If strncmp = 0, return 0
	mov	r0, 0			@ set 0 to return value r0
	b	epilogue		@ branch to epilogue

epilogue:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
