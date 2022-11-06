//To compile: gcc -Wall -o blink blink.c -lwiringPi
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

int start(void);                  //function prototype
int stop(void);                   //function prototype
void pwmpulse(float brightnes);   //function prototype
void RedOffOn(int i);             //function prototype
void RedOnOff(int i);             //function prototype
void pulse(void);                 //function prototype

#define red 7                     //physical pin no.7
#define green 1                   //physical pin no.12

int main(int argc, char *argv[])  //accepts only 2 arguments (inclusive of program name)
{
if (argc != 2)
{
  printf("Please enter the correct usage of program 'sudo ./blink 1' for example. \n"); //incorrect program usage catch
}
else if (atoi(argv[1])==0)        //if condition for number 0
{
	stop();                         //function call
}
else if (atoi(argv[1]) == 1)      //if condition for number 1
{
	start();                        //function call
}
else if (atoi(argv[1])==2)        //pulses twice every second until stopped
{
  printf("Running at 100 percent brightness on Red and Green LED at 2Hz.\n");  //documentation to user
	printf("Hold Ctrl + C to stop pulse and change LED functions.\n");           //instructions to user
	do                              //do while loop to run condition check to run function indefinitely
	{
    	pulse();                    //function call
	}
		while(atoi(argv[1])==2);      //end of do while loop
}

else if (atoi(argv[1])==3)
{
  printf("Running at 25 percent brightness on green LED on PWM at 2Hz, 100 percent brightness on Red LED at 8Hz.\n"); //documentation to user
  printf ("Hold Ctrl + C to stop pulse and change LED functions. You can change the brightness level of the green LED from 1-1024 as well.\n"); //instructions to user
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
else
{
  printf("Please use appropriate parameters of 0-3 when executing program.\n"); //incorrect program usage catch
}
}


int start(void)                     //start(); function to turn on both the LEDs
{
	  wiringPiSetup();                //initialises the usage of the wiringPi functions
	  pinMode(red, OUTPUT);           //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
	  pinMode(green, OUTPUT);         //Tells the compiler which pin the green LED is at specifically, and set it to have an output signal
	  digitalWrite(red, 1);           //turn on red LED
	  digitalWrite(green, 1);         //turn on green LED
	  return 0;                       //returns 0 to start(); function to let it know that the function has finished execution
}

int stop(void)                      //stop(); function to turn off both the LEDs
{
	  wiringPiSetup() ;               //initialises the usage of the wiringPi functions
	  pinMode(red, OUTPUT);           //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
	  pinMode(green, OUTPUT);         //Tells the compiler which pin the green LED is at specifically, and set it to have an output signal
	  digitalWrite(red, 0);           //turn off red LED 
	  digitalWrite(green, 0);         //turn off green LED
	  return 0;                       //returns 0 to stop(); function to let it know that the function has finished execution
}

void pwmpulse(float brightnes)      //2 red blinks : 1 green change
{
    digitalWrite(red,1);            //turns the red LED on
    pwmWrite(green, brightnes);     //turns on green LED in PWM mode at entered parameter brightness level
    delay(62.5);                    //delays the next line by 62.5 milliseconds.
    RedOffOn(2);                    //function call
    digitalWrite(red, 0);           //turns red LED off
    pwmWrite(green, 0);             //turns green LED off
    delay(62.5);                    //delays the next line by 62.5 milliseconds
    RedOnOff(2);                    //function call
}

void RedOffOn(int i)
{
  for (int n = 0; n<i; n++)         //creating a loop that uses argument i as a parameter
  {
    digitalWrite(red, 0);           //turns the red LED off
    delay(62.5);                    //delays next line by 62.5 milliseconds
    digitalWrite(red, 1);           //turns the red LED on
    delay(62.5);                    //delays the next line by 62.5 milliseconds
  }
}

void RedOnOff(int i)
{
  for (int n =0; n<i; n++)          //creating a loop that uses argument i as a parameter
  {
    digitalWrite(red, 1);           //turns red LED on
    delay(62.5);                    //delays the next line by 62.5 milliseconds
    digitalWrite(red, 0);           //turns red LED off
    delay(62.5);                    //delays the next line by 62.5 milliseconds
  }
}

void pulse(void)
{
      wiringPiSetup () ;            //initialises the wiringPi functions so that functions are usable
		  pinMode (red, OUTPUT) ;       //Tells the compiler which pin the red LED is at specifically, and set it to have an output signal
		  pinMode (green, OUTPUT) ;     //Tells the compiler which pin the green LED is at specifically and set it to have an output signal
		  for (;;)                      //creating a for loop without conditionals so that it runs infinitely
      {
        digitalWrite (red, 1) ;     //turns on the red LED
        digitalWrite (green, 1);    //turns on the green LED
        delay (250) ;               //adds a 250millisecond delay before executing next line
        digitalWrite (red, 0) ;     //turns off the red LED
        digitalWrite (green, 0) ;   //turns off the green LED
        delay (250) ;               //adds a 250millisecond delay before executing next line
      }
}
