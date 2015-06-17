#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void foto()
{
	//int i;
	char buffer[500];
	// int n = 0;
 //   	DIR *dir;
 //   	char path[] = "/home/pi/theProgram/photos/copycascade";
 //   	char *file[60];
 //   	int fileNumber[20];
 //   	struct dirent *dirent;
 //   	int maxNumber = 0;

	printf("Capture image\n");
	
	// for(i = 0; i < 10; i++)
	// {
	// 	sprintf(buffer, "sudo fswebcam -r 160x120 --no-banner /home/pi/theProgram/photos/pos/image%d.pgm", i);
 //        system(buffer);
 //        sleep(15);
	// }
	printf("Start making the vec file\n");
	// maakt vec file
	sprintf(buffer, "sudo opencv_createsamples -info /home/pi/theProgram/photos/pospic.info -num 10 -w 48 -h 24 -vec /home/pi/theProgram/photos/object.vec");
    system(buffer);
    sleep(3);
    printf("Create XML\n");
    
    // maakt de xml
    sprintf(buffer, "cd /home/pi/theProgram/photos\nsudo opencv_traincascade -data data -vec /home/pi/theProgram/photos/object.vec -bg /home/pi/theProgram/photos/bg.txt -numPos 9 -numNeg 9 -numStages 20 -w 48 -h 24 -featureType LBP");
    system(buffer);

    //copy maken naar copycascade en naam geven met nummer
    

	
   
}

void copydd(){

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
       // return main;
    }

    while ((dirent = readdir(dir)) != NULL) {
        printf ("[%s]-- n = %d\n", dirent->d_name, n);
        
        file[n] = dirent->d_name;
        n++;
    }
    closedir(dir);

    n = 0;

    while(file[n] != NULL)
    {
    	printf("1. %s\n", file[n]);
    	sscanf(file[n], "%d", &fileNumber[n]);
    	
    	 printf("test: %d\n", fileNumber[n]);
    	 if(fileNumber[n] > maxNumber && fileNumber[n] < 20000000)
    	{
    		maxNumber = fileNumber[n];
    	}
    	printf("max = %d\n", maxNumber);
    	n++;
    }

    maxNumber++;
    printf("2.max = %d\n", maxNumber);
    sprintf(buffer, "sudo cp /home/pi/theProgram/photos/data/cascade.xml /home/pi/theProgram/photos/copycascade/%d.xml", maxNumber);
    system(buffer);
    sleep(3);
    // //upload naar dropbox
    sprintf(buffer, "/home/pi/Dropbox-Uploader/dropbox_uploader.sh upload %c/home/pi/theProgram/photos/copycascade/%d.xml%c %ccascade%d.xml%c",34, maxNumber, 34, 34, maxNumber, 34);
    system(buffer);

}