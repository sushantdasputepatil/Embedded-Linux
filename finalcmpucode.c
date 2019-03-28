/*
	MPU6050 Interfacing with Raspberry Pi
	http://www.electronicwings.com
*/

#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define address 0x68	/*Device Address/Identifier for MPU6050*/
#define MPU_TEMP1 0x41
#define MPU_TEMP2 0x42
#define MPU_POWER2 0x6c
#define PWR_MGMT_1   0x6B
#define CONFIG       0x1A
#define INT_ENABLE   0x38

int fd;

void MPU6050_Init(){
	if ((fd = open(fileName, O_RDWR)) < 0) {
        printf("Failed to open i2c port\n");
        exit(1);
    }
	
    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        printf("Unable to get bus access to talk to slave\n");
        exit(1);
    }
	int8_t i2c_smbus_write_byte_data(fd, PWR_MGMT_1, 0x20);	/* Write to power management register */
	int8_t i2c_smbus_write_byte_data(fd, CONFIG, 0);		/* Write to Configuration register */
	int8_t i2c_smbus_write_byte_data(fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

	} 

void ms_delay(int val){
	int i,j;
	for(i=0;i<=val;i++)
		for(j=0;j<1200;j++);
}

int main(int argc, char **argv)
{
    int fd;
    char *fileName = "/dev/i2c-1";
    int  address = 0x68;
    MPU6050_Init();		                 /* Initializes MPU6050 */
    
    int8_t power = i2c_smbus_read_byte_data(fd, MPU_POWER1);
    i2c_smbus_write_byte_data(fd, MPU_POWER1, ~(1 << 6) & power);

    while (1) {
        int16_t temp = i2c_smbus_read_byte_data(fd, MPU_TEMP1) << 8 |
                        i2c_smbus_read_byte_data(fd, MPU_TEMP2);
        printf("temp: %f\n", (float)temp / 340.0f + 36.53);
        delay(500);
    }
		
    return 0;
}
