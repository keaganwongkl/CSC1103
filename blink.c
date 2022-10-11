#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
//number 0 = turn off both red and green LED lights
//number 1 = turn on both red and green LED (No blinks, just turn on)
//number 2 = keep blinking 2 times every second, 50% duty cycle. Just blink both together
//number 3 = blink red LED 8 times per second.
	       //turn on and dim the green LED by 4x duty cycle from 50% into 12.5% (make the average voltage 12.5% instead of 50%)
		//for green LED, exclusively use GPIO 12/13/18 or 19
//Duty Cycle = (pulse width/time period)*100%
int start(void);
int stop(void);

#define red 4
#define green 18
int main(int argc, char *argv[])//accepts only 2 arguments (inclusive of program name)
{
if (atoi(argv[1])==0) //if condition for number 0
{
	stop();
}
else if (atoi(argv[1]) == 1)   //if condition for number 1
{
	start();
}
if (atoi(argv[1])==2) //pulses twice every second until stopped
{
	printf("Hold Ctrl + C to stop pulse.\n");
	do
	{
    	if (gpioInitialise() < 0)
    	{
        	return 1; //Failed to initialize.
    	}
		gpioSetMode(red, PI_OUTPUT);
		gpioSetMode(green, PI_OUTPUT);
		gpioWrite(red, 1);
		gpioWrite(green, 1);
		time_sleep(0.25);  //on for 0.25s 50% uptime
		gpioWrite(red, 0);
		gpioWrite(green, 0);
		//time_sleep(0.25); //sleep for 0.25s  50% downtime, period = 0.5s
		gpioTerminate(); //kills all currently running threads to release memory, otherwise overtime will implode
	}
		while(atoi(argv[1])==2);
}
if (atoi(argv[1])==3) //pulses twice every second until stopped
{
	do
	{
    	if (gpioInitialise() < 0)
    	{
        	return 1; //Failed to initialize.
    	}
		gpioSetMode(red, PI_OUTPUT);
		gpioSetMode(green, PI_OUTPUT);
		gpioWrite(green,1);
		gpioWrite(red, 1);
		time_sleep(0.00125);
		gpioWrite(green,0);
		gpioWrite(red, 0);
		gpioTerminate();
	}
		while(atoi(argv[1])==3);
}
	printf("Blink count is %s, program exiting...\n",argv[1]);
	return 0;
	gpioTerminate();
}


int start(void)
{
	if (gpioInitialise() < 0)
	{
		return 1; //failed to initialise
	}
	gpioSetMode(red, PI_OUTPUT);
	gpioSetMode(green, PI_OUTPUT);
	gpioWrite(red, 1);  //turn on red LED
	gpioWrite(green, 1); //turn off green LED
	gpioTerminate(); //clear memory
	return 0;
}

int stop(void)
{
	if (gpioInitialise() < 0)
	{
		return 1; //failed to initialise
	}
	gpioSetMode(red, PI_OUTPUT);
	gpioSetMode(green, PI_OUTPUT);
	gpioWrite(red, 0);   //turn off red LED
	gpioWrite(green, 0);  //turn off green LED
	gpioTerminate();  //clear memory
	return 0;
}
