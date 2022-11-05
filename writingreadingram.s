.data                                       @data segment to store strings and other variables
message1: .asciz "What is your value?: "    @message1 that wants to be printed out for user
message2: .asciz "\nThe input value is: "   @message2 that wants to be printed out for user
message3: .asciz "\nThe output value is: "  @message3 that wants to be printed out for user
printline: .asciz "\n"                      @linefeed message that prints out
inputformat: .asciz "%d"                    @used for a formatted input for scanf to intake an integer value from user

.balign 4                                   @requesting 4 bytes from memory
var1:                                       @defining a variable of size 32 bits, since ARM is a 32bit system, var1 is stored at a specific memory location in RAM upon every code execution.
    .word 0                                 @defining var1 to be value of 0 first

.text                                       @text segment to write code into

.global main                                @main program starts here

loadmem:                                    @creating function to load r0 and r1
    push {lr}                               @push return address into stack
    ldr r0, =inputformat                    @load register 0 the address of inputformat
    ldr r1, =var1                           @load register 1 the address of var1
    pop {pc}                                @pop the program counter off the stack and return

println:                                    @creating linefeed function
    push {lr}                               @push return address into stack 
    ldr r0, =printline                      @load register 0 the address of printline
    bl printf                               @branch link to use C library function printf
    pop {pc}                                @pop the program counter off the stack and return

read_out:                                   @creating function to read out data from register 1
    push {lr}                               @push return address into stack
    ldr r1, [r1]                            @load register 1 the value of the address stored in register 1
    bl printf                               @branch link to use C library function printf
    pop {pc}                                @pop the program counter off the stack and return

main:                                       @function for main

    push {lr}                               @push return address (link register) into stack

    ldr r0, =message1                       @load address of message1 from memory into register 0
    bl printf                               @branch link to use C library function printf
    bl loadmem                              @function call
    bl scanf                                @branch link to use C library function scanf

    ldr r0, =message2                       @load address of message2 into register 0
    bl printf                               @branch link to use C library function printf
    bl loadmem                              @function call
    bl read_out                             @function call

    bl println                              @function call

    ldr r0, =message3                       @load address of message3 into register 0
    bl printf                               @branch link to use C library function printf
    bl loadmem                              @function call
    bl read_out                             @function call

    bl println                              @function call

    pop {pc}                                @pop the program counter off the stack and returns out of main and exits program
