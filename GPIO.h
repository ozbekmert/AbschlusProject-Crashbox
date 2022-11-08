#ifndef GPIO_H_
#define GPIO_H_

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int init_gpio(int pin);
int set_gpio(int pin, int value);
int init_resetPin();
void restart_GM862();
void setGPIOs();

#endif /* GPIO_H_ */
