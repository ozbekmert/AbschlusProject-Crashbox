#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <stdint.h>

//void writeData();
void convertAcceleration();
void *readAcceleration(void * argument);
void stopRecord();
//void mainAccelerometerProcess();
void startRecord(char* fn);

#endif /* ACCELEROMETER_H_ */
