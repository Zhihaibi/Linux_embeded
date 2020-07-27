#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>

int main(void){
	int len = 0;
	int value = 0;
	int flag = 0;
	int delay_times = 0;
	double fre = 2;

	int fd_adc;
	int fd_led;
	int fd_bz;
	char *adc = "/dev/adc";
	char *leds = "/dev/leds";
	char *buzzer = "/dev/buzzer_ctl";
	char buffer[512];
	memset(buffer,0,sizeof(buffer));  // Ìî³äÄÚ´æ
	
	if((fd_adc = open(adc, O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		printf("open ADC error\n");
		return;
	}
	if((fd_led = open(leds, O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		printf("open leds error\n");
		return;
	}
	if((fd_bz = open(buzzer, O_RDWR|O_NOCTTY|O_NDELAY))<0)
	{
		printf("open buzzer error\n");
		return;
	}
	

	while(1)
	{
		flag = 0;
		int len = read(fd_adc,buffer,10);	// ¶ÁÈ¡ADÖµ
		if(len == 0)
		{
			printf("ADC read error \n");
			return;
		}
		value = atoi(buffer);
		value = value*10000/4096;
		printf("--------------------R = %d-----------------\n",value);

		if(value > 9000 || value < 1000)
		{
			ioctl(fd_bz,1);		// ·äÃùÆ÷Ïì
			sleep(1);
			ioctl(fd_bz,0);
			sleep(1);	
		}
		else
		{
			flag  = 1;
		}
	
		if(flag == 1)
		{
			//led
			//delay_times = value*value;
			ioctl(fd_bz,0);

			delay_times = 1000000;
			ioctl(fd_led,0,0);
			ioctl(fd_led,0,1);
			usleep(delay_times);
			ioctl(fd_led,1,0);
			ioctl(fd_led,1,1);
			usleep(delay_times);	
		}
		else 
		{
			ioctl(fd_led,1,0);  // Í£Ö¹ÉÁË¸
			ioctl(fd_led,1,1);
		}

	}	
}

