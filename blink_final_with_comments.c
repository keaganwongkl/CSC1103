//To compile: gcc -Wall -o blink blink.c -lwiringPi
#include <stdio.h>                //including standard input output library for C
#include <wiringPi.h>             //including the wiringPi library for C
#include <stdlib.h>               //including the standard lib header for C to use atoi(); function

int start(void);                  //function prototype
int stop(void);                   //function prototype
void pwmpulse(float brightnes);   //function prototype
void RedOffOn(int i);             //function prototype
void RedOnOff(int i);             //function prototype
void pulse(void);                 //function prototype

float max_bright = 1024;          //global float variable declaration
float ddc_val = 0;                //global float variable declaration

#define red 7                     //physical pin no.7
#define green 1                   //physical pin no.12

int main(int argc, char *argv[])  //accepts only 2 arguments (inclusive of program name)
{
if (argc != 2)                    //if statement to check if the amount of arguments is not equals to 2
{
  printf("Please enter the correct usage of program 'sudo ./blink 1' for example. \n"); //incorrect program usage catch
  return 0;                       //returns 0 to main to exit out of program safely
}
else if (atoi(argv[1])==0)        //if condition for number 0
{
	stop();                         //function call
  return 0;                       //returns 0 to main to exit out of program safely
}
else if (atoi(argv[1]) == 1)      //else if condition to check if the passed in argument is equals to 1
{
	start();                        //function call
  return 0;                       //returns 0 to main to exit out of program safely
}
else if (atoi(argv[1])==2)        //else if condition to check if the passed in argument is equals to 2
{
  printf("Running at 50 percent duty cycle on Red and Green LED at 2Hz.\n");   //documentation to user
	printf("Hold Ctrl + C to stop pulse and change LED functions.\n");           //instructions to user
	do                              //do while loop to run the body of the do while loop while a condition is met
	{
    	pulse();                    //function call
      return 0;                   //returns 0 to main to exit out of program safely
	}
		while(atoi(argv[1])==2);      //end of do while loop
}

else if (atoi(argv[1])==3)        //else if condition to check if the passed in argument is equals to 3
{
  do                              //do while loop to check if user input a correct value for ddc_val. Will repeat if ddc_val < 0
  {
    printf("How mnay times dimmer do you want the green LED to be (e.g: 1 being max brightness, 2 being half as bright): "); //prompt user for brightness level of green LED
    scanf("%f",&ddc_val);         //scanf to get the brightness level requested by user
    if (ddc_val <=0)              //if condition to check 
    {
      printf("Please use a number greater than 0.\n"); //print condition to tell user to input a right value
    }
  } while(ddc_val <= 0);          //end of do while loop
  printf("\nRunning at %.4f percent brightness on green LED on PWM at 2Hz, 100 percent brightness on Red LED at 8Hz.\n",100/ddc_val); //documentation to user
  printf ("\nHold Ctrl + C to stop pulse and change LED functions or brightness level.\n"); //instructions to user
  do                              //do while loop to run the body of the do while loop while a condition is met
	{
        ddc_val = (100/(ddc_val)/100);          //assigning ddc_val = 100/scanf'd ddc_value
        max_bright = max_bright*ddc_val;        //assigning max_bright = 1024/new ddc_value
        wiringPiSetup();                        //wiringPi library initialisation
        pinMode (green, PWM_OUTPUT);            //set up wiringPi GPIO pin 1 (physical pin )
        for (;;)                                //infinite for loop without any conditions
        {
            pwmpulse(max_bright);               //function call to pwmpulse with max_bright passed as an argument
        }
        return 0 ;                              //returns 0 to main to exit out of program safely
	} while(atoi(argv[1])==3);                    //end of do while loop
  return 0;                                     //returns 0 to main to exit out of program safely
}
else                                            //else condition to catch all other exceptions
{
  printf("Please use appropriate parameters of 0-3 when executing program.\n"); //incorrect argument passed into program catch
  return 0;                                     //returns 0 to main to exit out of program safely
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
