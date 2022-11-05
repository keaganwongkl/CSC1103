//https://stackoverflow.com/questions/58360015/how-to-clone-wiringpi-after-git-drogon-net-got-inaccesible
//install everything in root or it just won't work idk why. Aka "enter cd into terminal and then use the git clone in cli, then cd into wiringPi and ./build"
//To compile: gcc -Wall -o blink blink.c -lwiringPi
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <math.h>
//#include<pthread.h>

int start(void);
int stop(void);
//void *blink8red(void* tid);
//PI_THREAD (myThread);

#define red 7 //physical pin no.7
#define green 1 //physical pin no.12

int main(int argc, char *argv[]) //accepts only 2 arguments (inclusive of program name)
{

//pthread_t tid0;
//pthread_create(&tid0, NULL, blink8red,(void *)&tid0 );
//pthread_exit(NULL);
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
    	wiringPiSetup () ;
		  pinMode (red, OUTPUT) ;
		  pinMode (green, OUTPUT) ;
		  for (;;)
      {
        digitalWrite (red, 1) ;     // On
        digitalWrite (green, 1);
        delay (250) ;               // mS
        digitalWrite (red, 0) ;  
        digitalWrite (green, 0) ;     // Off
        delay (250) ;
      }
      return 0 ;
	}
		while(atoi(argv[1])==2);
}

else if (atoi(argv[1])==3)
{
  printf ("Raspberry Pi wiringPi PWM test program\n");
  do
	{
    	int brightness;
      wiringPiSetup();
      pinMode (1, PWM_OUTPUT) ;
      for (;;)   
      {
        digitalWrite(red,1);
        for (brightness = 0 ; brightness < 64 ; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 64; brightness < 128; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 128; brightness < 192; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 192; brightness < 256; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);


        digitalWrite(red,1);
        for (brightness = 255 ; brightness > 192 ; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 192; brightness > 128; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 128; brightness > 64; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 64; brightness >= 0; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
      }
  return 0 ;
	} while(atoi(argv[1])==3);
  //pthread_exit(NULL);
  return 0;
}
}


int start(void)
{
	  wiringPiSetup ();
	  pinMode(red, OUTPUT);
	  pinMode(green, OUTPUT);
	  digitalWrite(red, 1);  //turn on red LED
	  digitalWrite(green, 1); //turn off green LED
	  return 0;
}

int stop(void)
{
	  wiringPiSetup () ;
	  pinMode(red, OUTPUT);
	  pinMode(green, OUTPUT);
	  digitalWrite(red, 0);  //turn on red LED
	  digitalWrite(green, 0); //turn off green LED
	  return 0;
}

/*void *blink8red(void* tid)
{
  long *  myID =(long *)tid; //type casting thread ID into a long
  wiringPiSetup();
  pinMode (red, OUTPUT) ;
  for (;;)
  {
    digitalWrite (red, 1);     // On
    delay (62);               // mS
    digitalWrite (red, 0);     // Off
    delay (62);
  }
  return 0;
}*/

/*int main (void)
{
  printf ("Raspberry Pi - Gertboard Blink\n") ;

  wiringPiSetup () ;

  pinMode (red, OUTPUT) ;

  for (;;)
  {
    digitalWrite (red, 1) ;     // On
    delay (500) ;               // mS
    digitalWrite (red, 0) ;     // Off
    delay (500) ;
  }
  return 0 ;
}*/

/*do
	{
    	int brightness;
      wiringPiSetup();
      pinMode (1, PWM_OUTPUT) ;
      for (;;)   
      {
        for (brightness = 0 ; brightness < 256 ; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        delay(250);
        for (brightness = 255; brightness >= 0; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        delay(250);
      }
  return 0 ;
	}
    while(atoi(argv[1])==3);*/


/*
do      THIS IS THE CLOSEST I'VE GOTTEN to 8Hz and simultaneous dimming
	{
    	int brightness;
      wiringPiSetup();
      pinMode (1, PWM_OUTPUT) ;
      for (;;)   
      {
        digitalWrite(red,1);
        for (brightness = 0 ; brightness < 64 ; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 64; brightness < 128; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 128; brightness < 192; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 192; brightness < 256; ++brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);


        digitalWrite(red,1);
        for (brightness = 255 ; brightness > 192 ; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 192; brightness > 128; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 128; brightness > 64; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
        digitalWrite(red,1);
        for (brightness = 64; brightness >= 0; --brightness)
        {
        pwmWrite (green, brightness) ;
        delay (1) ;
        }
        digitalWrite(red,0);
        delay(62.5);
      }
  return 0 ;
	} while(atoi(argv[1])==3);*/
