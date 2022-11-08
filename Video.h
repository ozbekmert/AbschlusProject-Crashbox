#ifndef VIDEO_H_
#define VIDEO_H_

#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
// sudo apt-get install ffmpeg
// ffmpeg -f video4linux2 -r 25 -s 640x480 -i /dev/video0 a.mp4
//extern int alphasort();

char* pathVideo;

int file_select(struct direct *entry);
void copy_file(char* source, char* target);
void *copy_recent_videos();
void *remove_old_videos();
void *record_videos();
void mainCamProcess();
void copy_videos();
void *recordVideo();
void rcv(char* path);

#endif /* VIDEO_H_ */
