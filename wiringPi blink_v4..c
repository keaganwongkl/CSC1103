//https://stackoverflow.com/questions/58360015/how-to-clone-wiringpi-after-git-drogon-net-got-inaccesible
//install everything in root or it just won't work idk why. Aka "enter cd into terminal and then use the git clone in cli, then cd into wiringPi and ./build"
//To compile: gcc -Wall -o blink blink.c -lwiringPi
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <math.h>

int start(void);
int stop(void);
void pwmpulse(float brightnes);
void RedOffOn(int i);
void RedOnOff(int i);
void pulse(void);

#define red 7 //physical pin no.7
#define green 1 //physical pin no.12

int main(int argc, char *argv[]) //accepts only 2 arguments (inclusive of program name)
{

if (atoi(argv[1])==0) //if condition for number 0
{
	stop();
}
else if (atoi(argv[1]) == 1)   //if condition for number 1
{
	start();
}
else if (atoi(argv[1])==2) //pulses twice every second until stopped
{
	printf("Hold Ctrl + C to stop pulse.\n");
	do
	{
    	pulse();
	}
		while(atoi(argv[1])==2);
}

else if (atoi(argv[1])==3)
{
  printf ("Hold Ctrl + C to stop pulse. You can change the brightness level of the green LED from 1-1024 as well.\n");
  do
	{
        wiringPiSetup();
        pinMode (1, PWM_OUTPUT) ;
        for (;;)   
        {
            pwmpulse(256);  //can input whatever brightness level we want, 1024 for max brightness. AKA matching 1 in pinMode set
        }
        return 0 ;
	} while(atoi(argv[1])==3);
  return 0;
}
}


int start(void) //start(); function to turn on both the LEDs
{
	  wiringPiSetup(); //initialises the usage of the wiringPi functions
	  pinMode(red, OUTPUT); //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
	  pinMode(green, OUTPUT);//Tells the compiler which pin the green LED is at specifically, and set it to have an output signal
	  digitalWrite(red, 1);  //turn on red LED
	  digitalWrite(green, 1); //turn off green LED
	  return 0; //returns 0 to start(); function to let it know that the function has finished execution
}

int stop(void) //stop(); function to turn off both the LEDs
{
	  wiringPiSetup() ; //initialises the usage of the wiringPi functions
	  pinMode(red, OUTPUT); //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
	  pinMode(green, OUTPUT);//Tells the compiler which pin the green LED is at specifically, and set it to have an output signal
	  digitalWrite(red, 0);  //turn on red LED 
	  digitalWrite(green, 0); //turn off green LED
	  return 0; //returns 0 to stop(); function to let it know that the function has finished execution
}

void pwmpulse(float brightnes) //2 red blinks : 1 green change
{
    digitalWrite(red,1);  //turns the red LED on
    pwmWrite(green, brightnes); //turns on green LED in PWM mode at entered parameter brightness level
    delay(62.5); //delays the next line by 62.5 milliseconds.
    RedOffOn(2); //turns red LED off and then waits 62.5milliseconds, turns it back on. Then waits 62.5 milliseconds again
    digitalWrite(red, 0);
    pwmWrite(green, 0);
    delay(62.5);
    RedOnOff(2);
}

void RedOffOn(int i)
{
  for (int n = 0; n<i; n++)
  {
    digitalWrite(red, 0); //turns the red LED off
    delay(62.5);
    digitalWrite(red, 1);
    delay(62.5);
  }
}

void RedOnOff(int i)
{
  for (int n =0; n<i; n++)
  {
    digitalWrite(red, 1);
    delay(62.5);
    digitalWrite(red, 0);
    delay(62.5);
  }
}

void pulse(void)
{
      wiringPiSetup () ;              //initialises the wiringPi functions so that functions are usable
		  pinMode (red, OUTPUT) ;         //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
		  pinMode (green, OUTPUT) ;       //Tells the compiler which pin the green LED is at specifically and set it to have an output signal
		  for (;;)  //creating a for loop without conditionals so that it runs infinitely
      {
        digitalWrite (red, 1) ;       //turns on the red LED
        digitalWrite (green, 1);      //turns on the green LED
        delay (250) ;                 //adds a delay to program, calculated in milliseconds
        digitalWrite (red, 0) ;       //turns off the red LED
        digitalWrite (green, 0) ;     //turns off the green LED
        delay (250) ;                 //adds a delay to program, calculated in milliseconds
      }
}
