extern "C"
{
	#include "Video.h"
	#include <pthread.h>
    #include <unistd.h>
}

#include "Accelerometer.h"
#include "GSM.h"
#include "GPIO.h"
using namespace std;

char videoPath[31];
char accPath[31];
char gsmPath[35];

char lclTime[255];
char newLocalTime[20];

/*
void set_localTime(){

	char *time1;
	char *time2;
	char *MM, *DD, *hh, *mm, *YY, *ss;

	int fd;
	initUART2();
	Serial_Open(&fd, "/dev/ttyO2", B38400);

	if(tcflush(fd, TCIOFLUSH) == 0){

		Read(&fd,lclTime,255);
		print(lclTime);
		cout << endl;
	}

	int count=0;
	char* pch;
	pch = strtok(lclTime, ", ");
	while (pch != NULL) {
		if(count == 0)
		{
			time1 = pch;
			count++;
		}
		else
			time2 = pch;
		pch = strtok(NULL, ", ");
	}

	count = 0;
	pch = strtok(time1, "/ ");
	while (pch != NULL) {
		if(count == 0)
		{
			YY = pch;
			count++;
		}
		else if(count == 1)
		{
			MM = pch;
			count++;
		}
		else
			DD = pch;
		pch = strtok(NULL, "/ ");
	}

	count = 0;
		pch = strtok(time2, ": ");
			while (pch != NULL) {
				if(count == 0)
				{
					hh = pch;
					count++;
				}
				else if(count == 1)
				{
					mm = pch;
					count++;
				}
				else
					ss = pch;
				pch = strtok(NULL, ": ");
			}

	strcpy(newLocalTime, "date ");
	strcat(newLocalTime, MM);
	strcat(newLocalTime, DD);
	strcat(newLocalTime, hh);
	strcat(newLocalTime, mm);
	strcat(newLocalTime, YY);
	strcat(newLocalTime, ".");
	strcat(newLocalTime, ss);
	strcat(newLocalTime, "0");

	cout << "New Local: " << newLocalTime << endl;
}
*/

int main (){
//	setGPIOs();
	restart_GM862();
	mainCamProcess();
//	mainAccelerometerProcess();

//	set_localTime();


//	system(newLocalTime);
	//printf("Date changed!\n");

	while(1){
		time_t timer=time(NULL);
		strftime (videoPath, 31, "videos/%Y-%m-%d %I-%M-%S.mp4", localtime(&timer));
		strftime (accPath, 31, "videos/%Y-%m-%d %I-%M-%S.txt", localtime(&timer));
		strftime (gsmPath, 35, "videos/gsm_%Y-%m-%d %I-%M-%S.txt", localtime(&timer));
		printf("%s\n",videoPath);
		startRecord((char*)accPath); //acc thread
		//startGSM((char*)gsmPath);	//gsm thread
		rcv((char*)videoPath);	//cam thread
//		sleep(5);
		stopRecord();
		//stopGSM();
	}
	return 0;
}

//ON OFF pini ac accelerometreye bak

