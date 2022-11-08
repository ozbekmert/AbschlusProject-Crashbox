#include "Accelerometer.h"
#define SCALE48g  0.0007324;   // approximate scale factor for full range (+/-24g)
#define SCALE24g  0.0003662; // approximate scale factor for full range (+/-12g)
#define SCALE12g  0.0001831; // approximate scale factor for full range (+/-6g)
using namespace std;
unsigned char buf_X_MSB[1];
unsigned char buf_X_LSB[1];
unsigned char buf_Y_MSB[1];
unsigned char buf_Y_LSB[1];
unsigned char buf_Z_MSB[1];
unsigned char buf_Z_LSB[1];
volatile double xAcc,yAcc,zAcc;
int run = 0;
char* filename;

void startRecord(char* fn){
	filename = fn;
	pthread_t t1;
	pthread_create( &t1, NULL, readAcceleration,NULL);
}

void stopRecord()
{
	run=0;
}

void convertAcceleration()
{

		short temp = buf_X_MSB[0];
	    temp = (temp<<8) | buf_X_LSB[0];
        xAcc = temp*(12/pow(2,16));

        temp = buf_Y_MSB[0];
	    temp = (temp<<8) | buf_Y_LSB[0];
	    yAcc =  temp*(12/pow(2,16));

		temp = buf_Z_MSB[0];
	    temp = (temp<<8) | buf_Z_LSB[0];
	    zAcc = temp*(12/pow(2,16));

//	    cout << xAcc << " " << yAcc << " " <<  zAcc << " "  <<"END" <<endl;
//		cout << "The X acceleration is " << xAcc << endl;
//		cout << "The Y acceleration is " << yAcc << endl;
//		cout << "The z acceleration is " << zAcc << endl;
}

void *readAcceleration(void * argument)
{
	ofstream log(filename, std::ios_base::app | std::ios_base::out);
	int fd;														// File descrition                                                               // Name of the port we will be using
    int  address = 0x19;										// Address of LIS331
    unsigned char buf[10];										// Buffer for data being read/ written on the i2c bus

	if ((fd = open("/dev/i2c-3", O_RDWR)) < 0) {				// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}

	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	buf[0] = 0x20;                                              // Address of in which the data to be changed
	buf[1] = 0x27;                                              // The new value equals 39 in decimal

	if ((write(fd, buf, 2)) != 2) {								// Send register to read software from
		printf("Error writing to i2c slave\n");
		exit(1);
	}

	if (read(fd, buf, 2) != 2) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}
	else {

		printf("Software version: %u\n", buf[0]);               // We can see the new value
	}

                                                    // Process begins
	run = 1;
	
	log <<  " data ='[" ;
	while(run == 1){
	
//##########################################################################################################################################
//##########################################################################################################################################
        //Get X LSB

        buf_X_LSB[0] = 0x28;

        if ((write(fd, buf_X_LSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_X_LSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }


        //Get X MSB

        buf_X_MSB[0] = 0x29;

        if ((write(fd, buf_X_MSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_X_MSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }

//##########################################################################################################################################
//##########################################################################################################################################

        //Get Y LSB

        buf_Y_LSB[0] = 0x2A;

        if ((write(fd, buf_Y_LSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_Y_LSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }


        //Get Y MSB

        buf_Y_MSB[0] = 0x2B;

        if ((write(fd, buf_Y_MSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_Y_MSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }

//##########################################################################################################################################
//##########################################################################################################################################
        //Get Z LSB

        buf_Z_LSB[0] = 0x2C;

        if ((write(fd, buf_Z_LSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_Z_LSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }


        //Get Z MSB

        buf_Z_MSB[0] = 0x2D;

        if ((write(fd, buf_Z_MSB, 1)) != 1) {								// Send register to read software from
            printf("Error writing to i2c slave\n");
            exit(1);
        }

        if (read(fd, buf_Z_MSB, 1) != 1) {								// Read back data into buf[]
            printf("Unable to read from slave\n");
            exit(1);
        }

        // Printing the values of X, Y, Z

        convertAcceleration();
        log << "{" << "\"xAcc\":\"" <<xAcc << "\"," << "\"yAcc\":\""<<yAcc << "\"," << "\"zAcc\":\""<<zAcc << "\""  << "},";
//        sleep(1);
	}c
	log <<  "null]';" ;  
	log.close();
	close(fd);

}
