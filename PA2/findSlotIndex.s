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

	.global	findSlotIndex		@ Specify findSlotIndex as global symbol

	.text				@ Switch to Text segment
	.align	2			@ Align to 4-byte boundary

/*
 * Function Name: findSlotIndex()
 * Function Prototype: int findSlotIndex( const char * wordStr,
 * 					  size_t numSlots );
 * Description: Calculates the index into the slot array for the string wordStr
 * 		in a slot array of size numSlots.
 * Parameters: wordStr - 
 * 	       numSlots - 
 * Side Effects - None
 * Error Conditions: None
 * Return Value: The index of wordStr in the slot array
 * 
 * Registers used:
 *	r0 - arg 1 -- str,
 *	r1 - 
 *	r2 - 
 *	r3 - 
 */
findSlotIndex:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers





@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved register
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@   return
