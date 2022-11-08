#include "GPIO.h"

#define MAX 64
#define HIGH "1"
#define LOW "0"
#define resetPIN 39
#define ON_OFF 38 //on off export et
#define PIN6 35
#define PIN22 37
#define PIN24 33
#define PIN26 61 //acc trigger message pin


int init_gpio(int pin)
{
	FILE *LEDHandle = NULL;
	char setValue[4], GPIOString[4], GPIOValue[MAX], GPIODirection[MAX];

	sprintf(GPIOString, "%d", pin);
	sprintf(GPIOValue, "/sys/class/gpio/gpio%d/value", pin);
	sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", pin);

	//Export Pin
	if((LEDHandle = fopen("/sys/class/gpio/export", "ab")) == NULL){
		printf("Cannot export the GPIO pin.\n");
		return 1;
	}
	strcpy(setValue, GPIOString);
	fwrite(&setValue, sizeof(char), 2, LEDHandle);
	fclose(LEDHandle);

	//Set the direction of pin
	if((LEDHandle = fopen(GPIODirection, "rb+")) == NULL){
		printf("Cannot open direction handle.\n");
		return 1;
	}
	strcpy(setValue, "out");
	fwrite(&setValue, sizeof(char), 3, LEDHandle);
	fclose(LEDHandle);

	//Initialize pin to low
	if((LEDHandle = fopen(GPIOValue, "rb+")) == NULL){
		printf("Cannot open value handle.\n");
		return 1;
	}
	strcpy(setValue, LOW);
	fwrite(&setValue, sizeof(char), 1, LEDHandle);
	fclose(LEDHandle);
}

int set_gpio(int pin, int value)
{
	FILE *LEDHandle = NULL;
	char setValue[4], GPIOString[4], GPIOValue[MAX];

	sprintf(GPIOString, "%d", pin);
	sprintf(GPIOValue, "/sys/class/gpio/gpio%d/value", pin);

	if(value == 1){
		//set pin to high
		if((LEDHandle = fopen(GPIOValue, "rb+")) == NULL){
			printf("Cannot open value handle.\n");
			return 1;
		}
		strcpy(setValue, HIGH);
		fwrite(&setValue, sizeof(char), 1, LEDHandle);
		fclose(LEDHandle);
	}
	else if(value == 0){
		//set pin to low
		if((LEDHandle = fopen(GPIOValue, "rb+")) == NULL){
			printf("Cannot open value handle.\n");
			return 1;
		}
		strcpy(setValue, LOW);
		fwrite(&setValue, sizeof(char), 1, LEDHandle);
		fclose(LEDHandle);
	}
}

int init_resetPin()
{
	FILE *PINHandle = NULL;
	char resetPin[35], setValue[4];
	sprintf(resetPin, "/sys/kernel/debug/omap_mux/gpmc_ad7");

	if((PINHandle = fopen(resetPin, "rb+")) == NULL){
		printf("Cannot open resetPin handle.\n");
		return 1;
	}
	strcpy(setValue, "7");
	fwrite(&setValue, sizeof(char), 1, PINHandle);
	fclose(PINHandle);

	init_gpio(resetPIN);
	set_gpio(resetPIN,1);
}

void restart_GM862(){
	set_gpio(resetPIN,0);
	sleep(2);
	set_gpio(resetPIN,1);
}

void setGPIOs()
{
	init_resetPin();
	init_gpio(PIN6);
	init_gpio(PIN22);
	init_gpio(PIN24);
	init_gpio(PIN26);
	set_gpio(PIN26,1);
}

