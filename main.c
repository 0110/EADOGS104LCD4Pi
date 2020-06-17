/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

#include <stdio.h>
#include "ssd1803a-spi.h"

int main(int argc, char ** argv) {
 
 SSD1803A_RET ret;

 ssd1803a_spi_init();
 
 ret = ssd1803a_spi_sendText("Hello World", sizeof("Hello World"));
 if (ret == SSD1803A_RET_OK) {
     printf("Display should show 'Hello World'\n");
 } else {
     printf("Display returned code %d\n", ret);
 }

 ssd1803a_spi_close();

 return 0;
}
