#include <stdio.h>
#include <stdlib.h>
#include <uart.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "camera.h"

static int uart_fd1;
int rbcamera_init()
{
	if((uart_fd1=uart_open("ttymxc2"))<0){
		return -1;
	}
	uart_setopt(uart_fd1, 9600,8,'N',1);
	return 1;
}

int top103SetZoom(char *tmp)
{
	printf("top103SetZoom function was invoked.\n");
	char buff[255];
	strcpy(buff,":wF716");
	strcat(buff,tmp);
	buff[strlen(buff)]='\0';
	uart_Send(uart_fd1,buff,strlen(buff));
	printf("uart_Send %s!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",buff);
	return 1;
}

int top103SetFocus(char *tmp)
{
	printf("top103SetFocus function was invoked.\n");
	char buff[255];
	strcpy(buff,":wF712");
	strcat(buff,tmp);
	buff[strlen(buff)]='\0';
	uart_Send(uart_fd1, buff, strlen(buff));
	printf("uart_Send %s!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",buff);
	return 1;
}

int top103PhotoMode()
{
	printf("top103PhotoMode function was invoked.\n");
	char buff[255];
	buff[0] = 0XFF;buff[1] = 0X01;buff[2] = 0x00;buff[3] = 0x07;
	buff[4] = 0x00;buff[5] = 0X67;buff[6] = 0x6F;
	uart_Send(uart_fd1, buff, 7);
	return 1;
}

int top103ShotScreen()
{
	printf("toop103ShotScreen function was invoked.\n");
	char buff[255];
	buff[0] = 0XFF;buff[1] = 0X01;buff[2] = 0X00;buff[3] = 0x07;
	buff[4] = 0x00;buff[5] = 0x66;buff[6] = 0x6E;
	uart_Send(uart_fd1, buff, 7);
	return 1;
}

int top103CameraSwitch(int onoff)
{
	/*char buff[4];
	if(onoff)
		strcpy(buff,"ON");
	else
		strcpy(buff,"OFF");
	*/
	char buff[255];
	buff[0] = 0XFF;buff[1] = 0x01; buff[2] = 0x00; buff[3] = 0x07;
	buff[4] = 0x00; buff[5] = 0x67; buff[6] = 0x6F;
	uart_Send(uart_fd1, buff, 7);
	printf("top103CameraSwitch %s function was invoked.\n",buff);
	return 1;
}