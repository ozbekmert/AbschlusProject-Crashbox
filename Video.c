#include "Video.h"

#include <string.h>

//extern int alphasort();


int file_select(struct direct *entry)
{
	if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0 )
		return 0;
	return 1;
}

void copy_file(char* source, char* target)
{
	int inhandle,outhandle,bytes;
	char buffer[512];

	inhandle=open(source,O_RDONLY);
	if(inhandle==-1)
	{
	    printf("cannot open source file\n");
	    exit(0);
	}
	outhandle=open(target,O_CREAT|O_WRONLY|S_IWRITE,777);
	if(outhandle==-1)
	{

	    printf("cannot open target file\n");
	    close(outhandle);
	    exit(0);
	}
	while(1)
	{
	    bytes=read(inhandle,buffer,512);
	    if(bytes>0)
	    {
	    	write(outhandle,buffer,bytes);
	    }
	    else
	    	break;
	}
	close(inhandle);
	close(outhandle);
}

void *copy_recent_videos()
{
	int numOfFiles,i;
	struct direct **files;
	int file_select();
	numOfFiles = scandir("videos/",&files,(int*)file_select,alphasort);

	for(i=numOfFiles-1; i>=numOfFiles-5 && i>=0;i--)
	{
		// son 5 video'yu kopyalar
		char videoPath[31];
		sprintf (videoPath, "videos/%s",files[i]->d_name);
		printf("videoPath %s\n",videoPath);
		
		char destPath[36];
		sprintf (destPath, "copy_videos/%s",files[i]->d_name);
		printf("copy videoPath %s\n",destPath);
		copy_file(videoPath,destPath);

	}
}

void copy_videos()
{
	pthread_t copy_tid;
	int ret = pthread_create(&(copy_tid),NULL,&copy_recent_videos,NULL);
}

void *remove_old_videos()
{
	while(1)
	{
		int numOfFiles,i;
		struct direct **files;
		int file_select();
		numOfFiles = scandir("videos/",&files,(int*)file_select,alphasort);
		for(i=numOfFiles-11;i>=0;i--)
		{
			// son 10 tanesi hariç gerisini siler bro
			char videoPath[31];
			sprintf (videoPath, "videos/%s",files[i]->d_name);
			printf("videoPath %s\n",videoPath);
			
			if(remove(videoPath) != 0 )
			    puts("Error deleting file\n");
		    	else
			    puts("File successfully deleted\n");
		}
		sleep(60);
	}
}

void *record_videos()
{
	while(1){
		char videoPath[31];
		time_t timer=time(NULL);
		strftime (videoPath, 31, "videos/%Y-%m-%d %I-%M-%S.mp4", localtime(&timer));
		pid_t processVideo;
		processVideo = fork();

		if(processVideo == 0)
		{
			int p = execl("/usr/bin/ffmpeg","ffmpeg","-r","14/1","-s","320x240","-f","video4linux2","-i","/dev/video0","-f","mp4",videoPath,NULL);
			return 0;
		}

		sleep(34); // video'lar 10 max 10sn'lik



		pid_t processKill = fork();
		if(processKill == 0)
		{
			char buffer [50];
			sprintf (buffer, "%d", (int)processVideo);
			execl("/bin/kill","kill",buffer,NULL);
			return 0;
		}
		pid_t res = waitpid(processVideo,NULL,0);
	}
}

//char* videoPath;
//char videoPath[31];

void *recordVideo(){
//	char videoPath[31];
//	time_t timer=time(NULL);
//	strftime (videoPath, 31, "videos/%Y-%m-%d %I-%M-%S.mp4", localtime(&timer));
	pid_t processVideo;
	processVideo = fork();

	if(processVideo == 0)
	{
		printf("%s\n",pathVideo);
//										ffmpeg -f video4linux2 -i /dev/video1 -r 40  -vcodec mpeg4 -qscale 0.1 -s 800x600 out3.mp4
//		int p = execl("/usr/bin/ffmpeg","ffmpeg","-f","video4linux2","-i","/dev/video0","-r","40","-vcodec", "mpeg4","-qscale","0.1","-s","800x600",pathVideo,NULL);
		int p = execl("/usr/bin/ffmpeg","ffmpeg","-r","14/1","-s","320x240","-f","video4linux2","-i","/dev/video0","-f","mp4",pathVideo,NULL);
		return 0;
	}

	char buffer [50];
	sprintf (buffer, "%d", (int)processVideo);
//	printf("%s\n",buffer);
//	int camTime = 5; // cam record time
//	while(camTime>0)
//	{
//		usleep(1000000);
//		camTime--;
//	}
	sleep(5);


	pid_t processKill = fork();
	if(processKill == 0)
	{
		execl("/bin/kill","kill",buffer,NULL);
		return 0;
	}
	printf("%s killing\n",buffer);
	pid_t res = waitpid(processVideo,NULL,0);
	printf("%s killed\n",buffer);
}

void rcv(char* path){
	pthread_t rc_id;
	pathVideo = path;
	int ret_rc = pthread_create(&rc_id,NULL,&recordVideo,NULL);
	pthread_join(rc_id, NULL);
}

void mainCamProcess()
{
	pthread_t rm_id,rc_id;

	int ret_rm = pthread_create(&rm_id,NULL,&remove_old_videos,NULL);
	//int ret_rc = pthread_create(&rc_id,NULL,&remove_old_videos,NULL);
}


