/*
 * ledcontrol.c
 *
 *  Created on: Feb 20, 2025
 *      Author: johnchang
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "ledcontrol.h"


int main(int argc, char *argv[])
{
	led_on();
	sleep(1);
	led_off();

	return 0;
}

void led_on(){
	int fd;
	ssize_t ret;
	printf("led on is working...\n");
	fd = open("/sys/class/leds/user-led1/brightness", O_RDWR);
	if(-1 == fd)
		perror("led file open failed");

	/*led on*/
	ret = write(fd, "1", 1);
	if(-1 == ret){
		perror("led write failed");
		close(fd);
	}
	close(fd);
}

void led_off(){
	int fd;
	ssize_t ret;
	printf("led off is working...\n");
	fd = open("/sys/class/leds/user-led1/brightness", O_RDWR);
	if(-1 == fd)
		perror("led file open failed");

	/*led on*/
	ret = write(fd, "0", 1);
	if(-1 == ret){
		perror("led wtite failed");
		close(fd);
	}
	close(fd);
}

