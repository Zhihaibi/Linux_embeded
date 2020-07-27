#ifndef ADC_H
#define ADC_H
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



void init_ADC_LED_buzzer();
int read_ADC();
void LED_bling();
void buzz_change();
void set_led(int ch, int val);


#endif // ADC_H
