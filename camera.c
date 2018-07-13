#include <stdio.h>
#include <stdlib.h>
#include <uart.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "camera.h"
#include "common.h"

char char2hex(char c)
{
	switch(c){
		case '0':
			return 0x00;
		case '1':
			return 0x01;
		case '2':
			return 0x02;
		case '3':
			return 0x03;
		case '4':
			return 0x04;
		case '5':
			return 0x05;
		case '6':
			return 0x06;
		case '7':
			return 0x07;
		case '8':
			return 0x08;
		case '9':
			return 0x09;
		case 'a':
		case 'A':
			return 0x0A;
		case 'b':
		case 'B':
			return 0x0B;
		case 'c':
		case 'C':
			return 0x0C;
		case 'd':
		case 'D':
			return 0x0D;
		case 'e':
		case 'E':
			return 0x0E;
		case 'f':
		case 'F':
			return 0x0F;
	}
	return 0x00;
}
static int uart_fd1;
int rbcamera_init()
{
	system("echo wr-rs485 > /sys/devices/soc0/soc.1/2100000.aips-bus/21b8000.weim/8000000.fpga/uartmode");
	if((uart_fd1=uart_open("ttymxc2"))<0){
		return -1;
	}
	uart_setopt(uart_fd1, 9600,8,'N',1);
	return 1;
}

int top103SetZoom(char *tmp)
{
	char buff[13];
	buff[0] = 0x81; buff[1] = 0x01; buff[2] = 0x04;	buff[3] = 0x47; 
	buff[4] = char2hex(tmp[0]); buff[5] = char2hex(tmp[1]);	buff[6] = char2hex(tmp[2]); buff[7] = char2hex(tmp[3]);
	buff[8] = char2hex(tmp[4]); buff[9] = char2hex(tmp[5]); buff[10] = char2hex(tmp[6]); buff[11] = char2hex(tmp[7]);
	buff[12] = 0xFF;
	uart_Send(uart_fd1, buff, 13);
	return 1;
}

int top103PhotoMode()
{
	char buff[7];
	buff[0] = 0XFF;buff[1] = 0X01;buff[2] = 0x00;buff[3] = 0x07;
	buff[4] = 0x00;buff[5] = 0X67;buff[6] = 0x6F;
	uart_Send(uart_fd1, buff, 7);
	return 1;
}

int top103ShotScreen()
{
	char buff[7];
	buff[0] = 0XFF;buff[1] = 0X01;buff[2] = 0X00;buff[3] = 0x07;
	buff[4] = 0x00;buff[5] = 0x66;buff[6] = 0x6E;
	uart_Send(uart_fd1, buff, 7);
	return 1;
}

int top103CameraSwitch(int onoff)
{
	char buff[6];	
	if(onoff){
		buff[0] = 0x81; buff[1] = 0x01; buff[2] = 0x04; buff[3] = 0x00;
		buff[4] = 0x02; buff[5] = 0xFF;
	}else{
		buff[0] = 0x81; buff[1] = 0x01; buff[2] = 0x04; buff[3] = 0x00;
		buff[4] = 0x03; buff[5] = 0xFF;
	}
	uart_Send(uart_fd1, buff, 6);
	return 1;
}
