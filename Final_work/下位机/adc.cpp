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
#include "adc.h"
#include <sys/ioctl.h>
int fd_adc;
int fd_led;
int fd_bz;
int led_state = 0;
int buzzer_state = 0;
char buffer[128];

void init_ADC_LED_buzzer()
{

    const char *adc = "/dev/adc";
    const char *leds = "/dev/leds";
    const char *buzzer = "/dev/buzzer_ctl";
    char buffer[512];
    memset(buffer,0,sizeof(buffer));


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
}


int read_ADC()
{

    memset(buffer,0,sizeof(buffer));
    int len = 0;
    int value = 0;
    len=read(fd_adc,buffer,12);
    if(len == 0)
    {
        return -1;
    }
    value = atoi(buffer);
    value = value*10000/4096;
    return value;

}

void LED_bling()
{
    led_state = (led_state+1)%2;
    ioctl(fd_led,led_state,0);
    ioctl(fd_led,led_state,1);
}
void set_led(int ch, int val){
    ioctl(fd_led,val,ch);
}

void buzz_change()
{
    buzzer_state = (buzzer_state+1)%2;
    ioctl(fd_bz,1);
}
