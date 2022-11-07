@to compile: as -o blink.o blink.s
@to build with link: gcc -o blink_asm blink.o -lwiringPi
@to run: sudo ./blink_asm

.data											@data_segment
.balign 4										@assign 4 bytes of data to everything below
message1: .asciz "\nTurning on red LED.\n"  	@message when user turns on red LED
message2: .asciz "\nTurning on green LED.\n" 	@message when user turns on green LED
message3: .asciz "\nWhat mode do you want?: " 	@message to prompt user for userinput
message4: .asciz "\nTurning off both LEDs.\n" 	@message when user turns off both LEDs

inputformat: .asciz "%d"						@formatting the scanf value to be of integer

redpin:	 .int 7						   	   		@creating redpin label position on physical pin 7 (wiringPi 7)
greenpin: .int 1						   		@creating greenpin label position on physical pin 12 (wiringPi 1)

userinput:										@creating a variable called userinput
	.word 0								   		@defining userinput variable to be 0 first

OUTPUT	 =	1									@declaring OUTPUT variable and assigning it to be 1, which is used for GPIO setting to be high.
	
.text	
.global main									@main program declaration
.extern wiringPiSetup							@declaring usage of external function
.extern digitalWrite							@declaring usage of external function
.extern pinMode									@declaring usage of external function


red_on:											@function to turn on the red LED
	ldr	r0, =message1							@load the address of message1 into r0
    bl printf									@branch link to use printf function
	ldr	r0, =redpin								@load the address of the redpin variable into r0
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #OUTPUT								@move an immediate value of OUTPUT == 1 into r1
	bl	pinMode									@branch link to external function pinMode, this makes the GPIO pin to be a general purpose pin with an OUTPUT setting. Takes r0 and r1 as arguments
	ldr	r0, =redpin								@load the address of the redpin variable into r0 because it gets wiped
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #1									@move an immediate value of 1 into r1
	bl digitalWrite								@brach link to external function digitalWrite, this makes the pin that the red LED is on to be high(turns it on). Takes r0 and r1 as arguments
	mov r7,#1									@move immediate value of 1 into r7, used for sys call exits
	swi 0										@software interrupt to exit safely out of program


green_on:										@function to turn on the green LED
	ldr r0, =message2							@load r0 the adderss of message2
	bl printf									@branch link to use printf function
	ldr	r0, =greenpin							@load the address of the green variable into r0
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #OUTPUT								@move an immediate value of OUTPUT == 1 into r1
	bl	pinMode									@branch link to external function pinMode, this makes the GPIO pin to be a general purpose pin with an OUTPUT setting. Takes r0 and r1 as arguments
	ldr	r0, =greenpin							@load the address of the green variable into r0 because it gets wiped
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #1									@move an immediate value of 1 into r1
	bl digitalWrite								@brach link to external function digitalWrite, this makes the pin that the green LED is on to be high(turns it on). Takes r0 and r1 as arguments
	mov r7,#1									@move immediate value of 1 into r7, used for sys call exits
	swi 0										@software interrupt to exit safely out of program

off_both: 										@function to turn off both red and green LED
	ldr r0, =message4							@load the address of message4 into r0
	bl printf									@branch link to use printf function
	ldr	r0, =redpin								@load r0 the address of redpin variable
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #0									@move an immediate value of 0 into r1
	bl 	digitalWrite							@brach link to external function digitalWrite, this makes the pin that the red LED is on to be low(turns it off). Takes r0 and r1 as arguments
	ldr	r0, =greenpin							@load r0 the address of greenpin variable
	ldr	r0, [r0]								@load the value stored in the address stored in r0, into r0, r0 = *(r0) in C
	mov	r1, #0									@move an immedaite value 0 into r1
	bl 	digitalWrite							@brach link to external function digitalWrite, this makes the pin that the green LED is on to be low(turns it off). Takes r0 and r1 as argumen
	mov r7,#1									@move immediate value of 1 into r7, used for sys call exits
	swi 0										@software interrupt to exit safely out of program

main:   										@main program function here

	bl	wiringPiSetup							@branch link to the wiringPisetup so that wiringPi library functions can be used
	ldr r0, =message3                       	@load address of message1 from memory into register 0
    bl printf                               	@branch link to use C library function printf
    ldr r0, =inputformat                    	@load register 0 the address of inputformat
    ldr r1, =userinput                      	@load register 1 the address of var1
    bl scanf                                	@branch link to use C library function scanf

	ldr r0,=userinput							@load r0 the address of userinput
	ldr r0, [r0]								@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#1									@compare the value of r1 if it is equal to 1
	beq red_on									@branch to red_on if r0 == 1

	ldr r0,=userinput							@load r0 the address of userinput
	ldr r0, [r0]								@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#2									@compare the value of r1 if it is equal to 2
	beq green_on								@branch to green_on if r0 == 2

	ldr r0,=userinput							@load r0 the address of userinput
	ldr r0, [r0]								@load r0 the value stored in r0, which is the address of userinput
	cmp r0,#3									@compare the value of r1 if it is equal to 2
	beq off_both								@branch to green_on if r0 == 3

	mov r7,#1									@program exit catch incase
	swi 0										@system call
