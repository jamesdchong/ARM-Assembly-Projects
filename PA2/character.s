/*
 * Filename: character.s
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of Help: None
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Our Raspberry Pi
	.syntax	unified		@ Modern ARM syntax

	.equ	FP_OFFSET, 4	@ Offset from sp to set fp

@ Constants for local variables
	.equ	LOCAL_VAR_SPACE, 8
	.equ	NEW_CH_OFFSET, -8

@ Constants for formal parameters
	.equ	PARAM_SPACE, 16
	.equ	PATTERN_OFFSET, -16
	.equ	CH_OFFSET, -20
	.equ	ALPHABET_PATTERNS_OFFSET, -24
	.equ	DIGIT_PATTERNS_OFFSET, -28

@ Constants
	.equ	LETTER_INTERVAL_MIN, 65
	.equ	LETTER_INTERVAL_MAX, 90
	.equ	NUMBER_INTERVAL_MIN, 48
	.equ	NUMBER_INTERVAL_MAX, 57
	.equ	ARRAY_OFFSET, 4

	.global	character	@ Specify character as a global symbol

	.text			@ Switch to Text segment
	.align	2		@ Align to 4-byte boundary

/*
 * Function Name: character()
 * Function Prototype: int character( unsigned int pattern[], char ch,
 *				      const char * alphabetPatterns[],
 *				      const char * digitPatterns[] );
 * Description: Fills pattern with the bit pattern of ch. If ch is a letter,
 * 		look up its bit pattern in alphabetPatterns (uppercase letters
 * 		A-Z). Otherwise, if ch is a number, then look up its bit pattern
 * 		in digitPatterns (digits 0-9). If its bit pattern is found, use
 * 		it to set the bits in pattern.
 * Parameters: pattern[] - empty array to be filled with two unsigned hex values
 * 	       ch - pattern to be filled with this character's bit pattern
 * 	       alphabetPatterns[] - bit patterns of letters 'A'-'Z'
 *	       digitPatterns[] - bit patterns of digits 0-9
 * Side Effects - None
 * Error Conditions: If ch is not a letter or a number, return -1
 * Return Value: -1 if ch is not a letter or a number, else return 0
 * 
 * Registers used:
 *	r0 - arg 1 -- pattern[], used various times to store temporary values,
 *		      holds return value of -1 if error occurs, 0 otherwise
 *	r1 - arg 2 -- ch, used various times to store temporary values
 *	r2 - arg 3 -- alphabetPatterns[], used various times to store temporary
 *		      values
 *	r3 - arg 4 -- digitPatterns[], used various times to store temporary
 *		      values
 */
character:
	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved
						@   registers

	@ Allocate space on stack for local vars
	sub	sp, sp, LOCAL_VAR_SPACE		@ allocate 2 local vars

	@ Allocate space on stack for formal parameters
	sub	sp, sp, PARAM_SPACE		@ allocate space for params

	@ Store formal parameters
	str	r0, [fp, PATTERN_OFFSET]		@ store param1
	str	r1, [fp, CH_OFFSET]			@ store param2
	str	r2, [fp, ALPHABET_PATTERNS_OFFSET]	@ store param3
	str	r3, [fp, DIGIT_PATTERNS_OFFSET]		@ store param4

	@ Initialize local var new ch to ch
	ldr	r3, [fp, CH_OFFSET]		@ loads ch to r3
	str	r3, [fp, NEW_CH_OFFSET]		@ stores r3 to new ch

	@ Capitalize letter
	ldr	r0, [fp, NEW_CH_OFFSET]		@ loads ch into r0
	bl	toupper				@ capitalizes ch
	str	r0, [fp, NEW_CH_OFFSET]		@ stores uppercase ch to new ch	

	@ Check if new ch is a letter
	mov	r0, LETTER_INTERVAL_MIN		@ sets ascii char 65 to r0
	mov	r1, LETTER_INTERVAL_MAX		@ sets ascii char 90 to r1
	ldr	r2, [fp, NEW_CH_OFFSET]		@ loads new ch into r2
	bl	intervalContains		@ checks if new ch in interval
	cmp	r0, 1				@ if in interval, r0 contains 1
	bne	else_if				@ branch to else_if if new ch
						@   not in interval

	@ Convert character to integer
	ldr	r3, [fp, NEW_CH_OFFSET]		@ load new ch into r3
	mov	r2, LETTER_INTERVAL_MIN		@ sets interval min (65) to r2
	sub	r3, r3, r2			@ obtains int value of new ch
	str	r3, [fp, NEW_CH_OFFSET]		@ stores value to new ch
	b	alphabet_array			@ branch to alphabet_array

else_if:
	@ If not a letter, check if ch is a digit
	mov	r0, NUMBER_INTERVAL_MIN		@ sets ascii char 48 to r0
	mov	r1, NUMBER_INTERVAL_MAX		@ sets ascii char 57 to r1
	ldr	r2, [fp, NEW_CH_OFFSET]		@ loads new ch into r2
	bl	intervalContains		@ checks if new ch in interval
	cmp	r0, 1				@ if in interval, r0 contains 1
	bne	else				@ branch to "if" if new ch in
						@   interval

	@ Convert character to integer
	ldr	r3, [fp, NEW_CH_OFFSET]		@ load new ch into r3
	mov	r2, NUMBER_INTERVAL_MIN		@ sets interval min (48) to r2
	sub	r3, r3, r2			@ obtains int value of new ch
	str	r3, [fp, NEW_CH_OFFSET]		@ stores value to new ch
	b	digit_array			@ branch to digit_array

else:
	b	error_case			@ branch to end as error case

alphabet_array:
	@ Look up new ch or the index of alphabet array
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r3, [fp, ALPHABET_PATTERNS_OFFSET]	@ load alphabet patterns
							@   array to r3
	ldr	r2, [fp, NEW_CH_OFFSET]		@ load new ch to r2
	mov	r1, ARRAY_OFFSET		@ access array values in
						@   memory in multiples
						@   of four
	mul	r2, r2, r1			@ multiplies new ch value with
						@   array offset
	ldr	r1, [r3, r2]			@ load bit pattern letter in
						@   alphabet array to r1

	@ Load specific alphabet string to pattern array
	bl	loadPatternString		@ loads r1 to pattern
	b	end				@ branch to end

digit_array:
	@ Look up new ch or the index of digit array
	ldr	r0, [fp, PATTERN_OFFSET]	@ load pattern array to r0
	ldr	r3, [fp, DIGIT_PATTERNS_OFFSET]	@ load digit patterns array to
						@   r3
	ldr	r2, [fp, NEW_CH_OFFSET]		@ load new ch to r2
	mov	r1, ARRAY_OFFSET		@ access array values in
						@   memory in multiples
						@   of four
	mul	r2, r2, r1			@ multiplies new ch value with
						@   array offset
	ldr	r1, [r3, r2]			@ load bit pattern digit in
						@   digit array to r1
	
	@ Load specific digit string to pattern array
	bl	loadPatternString		@ loads r1 to pattern
	b	end				@ branch to end

end:
	mov	r0, 0				@ set successful return value of
						@   0 to r0
	b	return				@ branch to return

error_case:
	mov	r0, -1				@ set unsuccessful return value
						@   of -1 to r0
return:
@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved
						@   register
	pop	{fp, pc}			@ Restore fp; restore lr into
						@   pc for return
