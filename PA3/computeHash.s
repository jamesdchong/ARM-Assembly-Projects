/*
 * Filename: computeHash.s
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
	.equ	LOCAL_VAR_SPACE, 16
	.equ	HASH_OFFSET, -8
	.equ	I_OFFSET, -12

@ Constants for parameters
	.equ	PARAM_SPACE, 16
	.equ	STR_OFFSET, -16

@ Constants
	.equ	NULL_TERMINATOR, 0

	.global	computeHash		@ Specify computeHash as global symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: computeHash()
 * Function Prototype: int computeHash( const char * str );
 * Description: Used to create the hash value of a string. Creates an unsigned
 * 		integer hash value from str with a a hashing algorithm.
 * Parameters: str - string used to create a hash value
 * Side Effects - None
 * Error Conditions: None
 * Return Value: The hash value of str
 * 
 * Registers used:
 *	r0 - arg 1 -- str, used to store hash value before returning
 *	r1 - used to load and store str and str[i]
 *	r2 - used to load and store str and str[i], HASH_START_VAL, and i
 *	r3 - used to store formal params, initialize local vars, as well as
 *	     storing, using, and loading temporary values
 *
 * Stack variables:
 * 	hash - [fp -8] -- the hash value of str
 *	i - [fp -12] -- loop counter
 * 	str - [fp -16] -- string parameter whose hash value is being calculated
 */
computeHash:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE	@ Allocate 2 local variables

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE	@ Allocate 1 formal parameter

	@ Store formal params
	str	r0, [fp, STR_OFFSET]	@ store r0 to str

	@ Initialize local vars
	ldr	r3, =G_HASH_START_VAL	@ load address of HASH_START
	ldr	r3, [r3]		@ load value of HASH_START
	str	r3, [fp, HASH_OFFSET]	@ store r3 to hash

	mov	r3, 0			@ set r3 to 0
	str	r3, [fp, I_OFFSET]	@ store 0 to i

	@ Set up for loop
	mov	r3, NULL_TERMINATOR	@ set r3 to null terminator
	ldr	r2, [fp, I_OFFSET]	@ load i to r2
	ldr	r1, [fp, STR_OFFSET]	@ load address of str to r1
	ldrb	r1, [r1, r2]		@ load value of str[i] to r1
	cmp	r1, r3			@ compare str[i] with null terminator
	beq	end_loop		@ branch to end_loop if not equal

loop:
	@ hash = hash * HASH_PRIME + str[i];
	ldr	r3, [fp, HASH_OFFSET]	@ load hash to r3
	ldr	r2, =G_HASH_PRIME	@ load address of G_HASH_PRIME to r2
	ldr	r2, [r2]		@ load value of G_HASH_PRIME to r2
	mul	r2, r2, r3		@ multiply hash with HASH_PRIME
	str	r2, [fp, HASH_OFFSET]	@ store result to hash

	ldr	r3, [fp, I_OFFSET]	@ load i to r3
	ldr	r2, [fp, STR_OFFSET]	@ load str to r2
	ldrb	r2, [r2, r3]		@ load str[i] to r2
	ldr	r3, [fp, HASH_OFFSET]	@ load hash to r3
	add	r3, r2, r3		@ add hash and str[i]
	str	r3, [fp, HASH_OFFSET]	@ store r3 to hash

	@ Increment i
	ldr	r3, [fp, I_OFFSET]	@ load i to r3
	add	r3, r3, 1		@ increment i
	str	r3, [fp, I_OFFSET]	@ store r3 to i

	@ Check loop condition
	mov	r3, NULL_TERMINATOR	@ set r3 to null terminator
	ldr	r2, [fp, I_OFFSET]	@ load i to r2
	ldr	r1, [fp, STR_OFFSET]	@ load address of str to r1
	ldrb	r1, [r1, r2]		@ load value of str[i] to r1
	cmp	r1, r3			@ compare str[i] with null terminator
	bne	loop			@ branch to loop if not equal

end_loop:
	@ load value of hash to return in r0
	ldr	r0, [fp, HASH_OFFSET]	@ load hash to r0

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
