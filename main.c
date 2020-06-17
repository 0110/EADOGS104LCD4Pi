/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

#include <stdio.h>
#include "spi-implement.h"

int main(int argc, char ** argv) {
 
 spi_implement_ret_t ret = spi_implement_init();

 if (ret == SPI_IMPL_RET_OK) {
    /* Kontrollausgabe */
    printf("SPI-Device.....: Opend\n");
 } else {
      printf("SPI-Device.....: %d error code\n", ret);
 }

 return 0;
}
