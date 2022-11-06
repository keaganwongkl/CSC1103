@to compile: as -o blink.o blink.s
@to build with link: gcc -o blink_asm blink.o -lwiringPi
@to run: sudo ./blink_asm

.data
.balign 4									@assign 4 bytes of data to everything below
message1: .asciz "\nTurning on red LED.\n"   @message when user turns on red LED
message2: .asciz "\nTurning on green LED.\n" @message when user turns on green LED
message3: .asciz "\nWhat mode do you want?: " 
message4: .asciz "\nTurning off both LEDs.\n" @message when user turns off both LEDs

inputformat: .asciz "%d"

redpin:	 .int 7						   	   @creating redpin label position on physical pin 7 (wiringPi 7)
greenpin: .int 1						   @creating greenpin label position on physical pin 12 (wiringPi 1)

userinput:
	.word 0								   @defining userinput variable to be 0 first

OUTPUT	 =	1
	
.text
.global main			@main program declaration
.extern wiringPiSetup	@declaring usage of external function
.extern digitalWrite	@declaring usage of external function
.extern pinMode			@declaring usage of external function


red_on:
	ldr	r0, =message1	@load the address of message1 into r0
    bl printf			@branch link to use printf function
	ldr	r0, =redpin
	ldr	r0, [r0]
	mov	r1, #OUTPUT
	bl	pinMode
	ldr	r0, =redpin
	ldr	r0, [r0]
	mov	r1, #1
	bl digitalWrite
	mov r7,#1
	swi 0


green_on:
	ldr r0, =message2
	bl printf			@branch link to use printf function
	ldr	r0, =greenpin
	ldr	r0, [r0]
	mov	r1, #OUTPUT
	bl	pinMode
	ldr	r0, =greenpin
	ldr	r0, [r0]
	mov	r1, #1
	bl digitalWrite
	mov r7,#1
	swi 0

off_both: @to turn off both red and green LED
	ldr r0, =message4
	bl printf			@branch link to use printf function
	ldr	r0, =redpin
	ldr	r0, [r0]
	mov	r1, #0
	bl 	digitalWrite
	ldr	r0, =greenpin
	ldr	r0, [r0]
	mov	r1, #0
	bl 	digitalWrite
	mov r7,#1
	swi 0

main:   

	bl	wiringPiSetup
	ldr r0, =message3                       @load address of message1 from memory into register 0
    bl printf                               @branch link to use C library function printf
    ldr r0, =inputformat                    @load register 0 the address of inputformat
    ldr r1, =userinput                      @load register 1 the address of var1
    bl scanf                                @branch link to use C library function scanf

	ldr r0,=userinput						@load r0 the address of userinput
	ldr r0, [r0]							@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#1								@compare the value of r1 if it is equal to 1
	beq red_on								@branch to red_on if r0 == 1

	ldr r0,=userinput						@load r0 the address of userinput
	ldr r0, [r0]							@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#2								@compare the value of r1 if it is equal to 2
	beq green_on							@branch to green_on if r0 == 2

	ldr r0,=userinput						@load r0 the address of userinput
	ldr r0, [r0]							@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#3								@compare the value of r1 if it is equal to 2
	beq off_both							@branch to green_on if r0 == 3

	mov r7,#1			@program exit catch incase
	swi 0				@system call
