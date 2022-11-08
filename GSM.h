#ifndef GSM_H_
#define GSM_H_

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
#include <time.h>
#include <termios.h>
#include <stdlib.h>

int Serial_Open(int* fd, char *serial_Name, speed_t baudrate);
int Serial_Close(int *fd);
void print(char *data);
int Send(int *fd, char *transmit_data);
int Read(int *fd, char *recieve_data, int len);
void startGSM(char*);
void *gsmThread();
void stopGSM();
int init_UART2_TX();
int init_UART2_RX();
void initUART2();

#endif /* GSM_H_ */
