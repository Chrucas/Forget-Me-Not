//compile sudo gcc -o program program.c -lwiringPi
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define STARTBUTTON 7
#define STOPBUTTON 0
#define RELAY 3

void foto();
void openCV();
void saveDropbox();

void startMotor()
{
	digitalWrite(RELAY, HIGH);
  foto();
}

void stopMotor()
{
	digitalWrite(RELAY, LOW);
  openCV();
}

int main(void)
{
  wiringPiSetup () ;
  pinMode(STARTBUTTON, INPUT);
  pinMode(STOPBUTTON, INPUT);
  pinMode(RELAY, OUTPUT);
  
  while(1)
  {    
    digitalWrite(RELAY, LOW);
    if(digitalRead(STARTBUTTON) == 1)
    {
      startMotor();
    }
    else if(digitalRead(STOPBUTTON) == 1)
    {
      stopMotor();
    }
  }
  exit(0);
}


void foto()
{
  
  char buffer[500];
 
  printf("Capture image\n");
  int x, u;
  x = digitalRead(STARTBUTTON);
  u = digitalRead(STOPBUTTON);
  // for(i = 0; i < 10; i++)
  // {
  //  sprintf(buffer, "sudo fswebcam -r 160x120 --no-banner /home/pi/theProgram/photos/pos/image%d.pgm", i);
    //  system(buffer);
    //  sleep(15);
  // }
  
  int i;
  for(i =0; i<5; i++)
  {
    printf("x = %d -- u = %d\n", x, u);
  }
  sleep(3);
  stopMotor();
 }

void openCV()
{
  char buffer[500];
  printf("Start making the vec file\n");
  // maakt vec file
  sprintf(buffer, "sudo opencv_createsamples -info /home/pi/theProgram/photos/pospic.info -num 10 -w 48 -h 24 -vec /home/pi/theProgram/photos/object.vec");
  system(buffer);
  
  printf("Create XML\n");
    
  // maakt de xml
  sprintf(buffer, "cd /home/pi/theProgram/photos\nsudo opencv_traincascade -data data -vec /home/pi/theProgram/photos/object.vec -bg /home/pi/theProgram/photos/bg.txt -numPos 9 -numNeg 9 -numStages 20 -w 48 -h 24 -featureType LBP");
  system(buffer);
  printf("opencv");
  saveDropbox();
  printf("opencv22");
}


void saveDropbox()
{
  printf("saveDropbox00");
  char buffer[500];
  int n = 0;
  DIR *dir;
  char path[] = "/home/pi/theProgram/photos/copycascade";
  char *file[60];
  int fileNumber[20];
  struct dirent *dirent;
  int maxNumber = 0;

  dir = opendir (path);
    if (dir == NULL) {
      printf ("Cannot open directory '%s'\n", path);
    }

    while ((dirent = readdir(dir)) != NULL) {
        file[n] = dirent->d_name;
        n++;
    }
    closedir(dir);

    n = 0;

    while(file[n] != NULL)
    {
      // read the numbers in all the file names and store it in filenumber
      sscanf(file[n], "%d", &fileNumber[n]);
      
      if(fileNumber[n] > maxNumber && fileNumber[n] < 200)
      {
        maxNumber = fileNumber[n];
      }
      n++;
    }
    //copy maken naar copycascade en naam geven met nummer
  maxNumber++;
  printf("2.max = %d\n", maxNumber);
  sprintf(buffer, "sudo cp /home/pi/theProgram/photos/data/cascade.xml /home/pi/theProgram/photos/copycascade/%d.xml", maxNumber);
  system(buffer);
    
  // //upload naar dropbox
  sprintf(buffer, "/home/pi/Dropbox-Uploader/dropbox_uploader.sh upload %c/home/pi/theProgram/photos/copycascade/%d.xml%c %ccascade%d.xml%c",34, maxNumber, 34, 34, maxNumber, 34);
  system(buffer);
}