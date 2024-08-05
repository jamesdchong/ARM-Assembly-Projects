/*
 * Filename: findSlotIndex.s
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
	.equ	HASH_OFFSET, -8
	.equ	INDEX_OFFSET, -12

@ Constants for parameters
	.equ	PARAM_SPACE, 8
	.equ	WORD_STR_OFFSET, -16
	.equ	NUM_SLOTS_OFFSET, -20

	.global	findSlotIndex		@ Specify findSlotIndex as global symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: findSlotIndex()
 * Function Prototype: int findSlotIndex( const char * wordStr,
 * 					  size_t numSlots );
 * Description: Calculates the index into the slot array for using the string
 * 		wordStr in a slot array of size numSlots
 * Parameters: wordStr - string being placed into slot array
 * 	       numSlots - size of slot array
 * Side Effects - None
 * Error Conditions: None
 * Return Value: The index of wordStr in the slot array
 * 
 * Registers used:
 *	r0 - arg 1 -- wordStr, holds wordStr when calling computeHash, holds
 *	hash when calling myURem, holds index to be returned
 *	r1 - arg 2 -- numSlots, holds numSlots when calling myURem
 *
 * Stack variables:
 * 	hash - [fp -8] -- holds hash value of wordStr
 *	index - [fp -12] -- index of wordStr in slot array
 *	wordStr - [fp -16] -- string being placed into slot array
 *	numSlot - [fp -20] -- size of slot array
 */
findSlotIndex:
@ Standard prologue
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ Allocate 2 local variables

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ Allocate 2 formal parameters

	@ Store formal parameters
	str	r0, [fp, WORD_STR_OFFSET]	@ store r0 to wordStr
	str	r1, [fp, NUM_SLOTS_OFFSET]	@ store r1 to numSlots

	@ Calculate hash value of the wordStr string
	ldr	r0, [fp, WORD_STR_OFFSET]	@ load wordStr to r0
	bl	computeHash			@ call computeHash
	str	r0, [fp, HASH_OFFSET]		@ store hash value to hash

	@ Find index by modding the hash value by numSlots
	ldr	r0, [fp, HASH_OFFSET]		@ load hash to r0
	ldr	r1, [fp, NUM_SLOTS_OFFSET]	@ load numSlots to r1
	bl	myURem				@ call myURem
	str	r0, [fp, INDEX_OFFSET]		@ stores result to index

	@ Loads index to r0 to return
	ldr	r0, [fp, INDEX_OFFSET]		@ loads index into r0 to return

@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
