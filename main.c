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
#include <stdbool.h>
#include <argp.h>
#include "ssd1803a-spi.h"

#define MAX_CHARACTERS	(20*4)

#define GPIO_LCDBACKLIGHT	18
#define GPIO_LCDBACKLIGHT_STR	"18"

const char *argp_program_version = "0.1";
const char *argp_program_bug_address = "Ollo@raspberry.local";
static char doc[] = "Control your EADOGS104 LCD from a raspberry pi";
static char args_doc[] = "EADIGS104...";
static struct argp_option options[] = { 
	{ "stdin", 's', 0, 0, "Read input to display from stdin"},
	{ "big", 'b', 0, 0, "Show 2 lines with 10 characters each."},
	{ 0 } 
};

struct arguments {
 bool useStdin;
 bool useBigChar;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
	case 's': arguments->useStdin = true; break;
	case 'b': arguments->useBigChar = true; break;
	case ARGP_KEY_ARG: return 0;
	default: return ARGP_ERR_UNKNOWN;
    }   
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char ** argv) {
 
 SSD1803A_RET ret;
 struct arguments arguments;
 arguments.useStdin = false;
 arguments.useBigChar = false;
 /* parese arguments */
 argp_parse(&argp, argc, argv, 0, 0, &arguments);

 /* main programm */
 ret = ssd1803a_spi_init();
 if (ret != SSD1803A_RET_OK) {
     printf("Initialization returned code %d\n", ret);
     printf("Was the kernel module loaded?\n");
     printf("  use >sudo modprobe spi_bcm2835< to do so\n");
     return 1;
 }

 /* activate backlight */
 FILE *sysfs_handle = NULL;
 if ((sysfs_handle = fopen("/sys/class/gpio/export", "w")) != NULL)
 {
    fwrite(GPIO_LCDBACKLIGHT_STR "\0", sizeof(char), 2, sysfs_handle);
    fclose(sysfs_handle);
 }
 if ((sysfs_handle = fopen("/sys/class/gpio/gpio"GPIO_LCDBACKLIGHT_STR "/direction", "w")) != NULL)
 {
    fwrite("out\0", sizeof(char), 4, sysfs_handle);
    fclose(sysfs_handle);
 }
 if ((sysfs_handle = fopen("/sys/class/gpio/gpio" GPIO_LCDBACKLIGHT_STR "/value", "w")) != NULL)
 {
    fwrite("1\0", sizeof(char), 2, sysfs_handle);
    fclose(sysfs_handle);
 }

 if (arguments.useBigChar) {
	ssd1803a_spi_setLines(2); /* use only 2 of 4 lines */
 }
 
 if (arguments.useStdin) {
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
