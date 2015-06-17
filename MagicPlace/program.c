//compile sudo gcc -o program program.c -lwiringPi
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include </home/pi/theProgram/foto.h>
#include <string.h>

#define STARTBUTTON 7
#define STOPBUTTON 0
#define RELAY 3

void startMotor()
{
	digitalWrite(RELAY, HIGH);
}

void stopMotor()
{
	digitalWrite(RELAY, LOW);
}

int main(void)
{
  wiringPiSetup () ;
  pinMode(STARTBUTTON, INPUT);
  pinMode(STOPBUTTON, INPUT);
  pinMode(RELAY, OUTPUT);

  while(1)
  {
    char start[4];
    printf("start program with a ");
    scanf("%s", &start);
  	if(STARTBUTTON == HIGH || strcmp(start, "a") == 0)
  	{
  		startMotor();
      foto();
      copydd();
  		sleep(5);
  	}
  	else if(STOPBUTTON == HIGH)
  	{
  		stopMotor();
  	}
  }
}