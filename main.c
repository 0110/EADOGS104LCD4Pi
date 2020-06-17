/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ssd1803a-spi.h"

#define MAX_CHARACTERS	(20*4)

int main(int argc, char ** argv) {
 
 SSD1803A_RET ret;

 ssd1803a_spi_init();
 
 if (argc >= 2) {
	if (strcmp(argv[1], "-s") == 0) {
		char buffer[MAX_CHARACTERS];
		int readbytes=read(STDIN_FILENO, buffer, MAX_CHARACTERS);
		ret = ssd1803a_spi_sendText(buffer, readbytes);
		if (readbytes < MAX_CHARACTERS) {
			buffer[readbytes] = '\0';
		}
		if (ret == SSD1803A_RET_OK) {
		     printf("Display should show '%s' (%d characters)\n", buffer, readbytes);
		} else {
		     printf("Display returned code %d\n", ret);
		}
	} else {
		printf("Unkown command %s\n", argv[1]);
	}
 } else {
	 ret = ssd1803a_spi_sendText("Hello World\0", sizeof("Hello World") - 1);
	 if (ret == SSD1803A_RET_OK) {
	     printf("Display should show 'Hello World'\n");
	 } else {
	     printf("Display returned code %d\n", ret);
	 }
 }
 ssd1803a_spi_close();

 return 0;
}
