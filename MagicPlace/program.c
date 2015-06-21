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
  
    printf("Capture image\n");
  
    // for(i = 0; i < 10; i++)
    //  {
    //   sprintf(buffer, "sudo raspistill -o /home/pi/theProgram/photos/pos/image%d.jpg -w 275 -h 206 -t 1000", i); // volgens mij kon het zo ook sander
    //     system(buffer);
    //     //sleep(1500);
    //   sprintf(buffer, "sudo mv image%d.jpg /home/pi/theProgram/photos/pos", i);  //pad waar je de image heen wilt hebben
    //  }
  
    sleep(3);
    stopMotor();
 }

void openCV()
{
  int n = 0;
    DIR *dir;
    char path[] = "/home/pi/theProgram/photos/copycascade";
    char *file[60];
    int fileNumber[20];
    struct dirent *dirent;
    int maxNumber = 0;
    char buffer[250];

    // remove the old vec file
    sprintf(buffer, "sudo rm /home/pi/theProgram/photos/object.vec");
    system(buffer);
    // remove the old params.xml file
    sprintf(buffer, "sudo rm /home/pi/theProgram/photos/data/params.xml");
    system(buffer);
    // remove all the stage files what is needed to create the cascade
    for(n = 0; n <= 8; n ++)
    {
      sprintf(buffer, "sudo rm /home/pi/theProgram/photos/data/stage%d.xml", n);
      system(buffer);
    }

    n = 0;
  
  printf("Start making the vec file\n");
    // maakt vec file
    sprintf(buffer, "sudo opencv_createsamples -info /home/pi/theProgram/photos/pospic.info -num 6 -w 48 -h 30 -vec /home/pi/theProgram/photos/object.vec");
    system(buffer);
    
    printf("Create XML\n");
    
    // maakt de xml
    sprintf(buffer, "cd /home/pi/theProgram/photos\nsudo opencv_traincascade -data data -vec /home/pi/theProgram/photos/object.vec -bg /home/pi/theProgram/photos/file.txt -numPos 6 -numNeg 40 -numStages 9 -w 48 -h 30 -featureType LBP");
    system(buffer);
    printf("XML done\n");
  
    // open directory to get all the object cascade files.
    dir = opendir (path);
  
    if(dir == NULL) 
    {
      printf ("Cannot open directory '%s'\n", path);
    }
  
    while((dirent = readdir(dir)) != NULL) 
    {
      if(dirent->d_name[0] != '.')
      {
        // store the cascade files in file
        file[n] = dirent->d_name;
        // read the numbers in all the file names and store it in filenumber
        sscanf(file[n], "%d", &fileNumber[n]);
        n++;
      } 
    }
  
    closedir(dir);
  
    // search for the highest number to name the new cascade file
    int d = 0;
    while(d < n)
    {
      if(fileNumber[d] > maxNumber)
      {
          maxNumber = fileNumber[d];
      }
      d++;
    }
  
    //create copy and send it to the map copycascade
    printf("Create copy\n");
    maxNumber++;
    printf("maxnumber = %d\n", maxNumber);
    sprintf(buffer, "sudo cp /home/pi/theProgram/photos/data/cascade.xml /home/pi/theProgram/photos/copycascade/%d.xml", maxNumber);
    system(buffer);
    printf("upload to dropbox\n");
    //upload the new cascade to dropbox  
    sprintf(buffer, "/home/pi/Dropbox-Uploader/dropbox_uploader.sh upload %c/home/pi/theProgram/photos/copycascade/%d.xml%c %ccascade%d.xml%c",34, maxNumber, 34, 34, maxNumber, 34);
    system(buffer);
 
}