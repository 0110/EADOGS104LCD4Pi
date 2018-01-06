#include <fcntl.h>                // Needed for SPI port
#include <sys/ioctl.h>            // Needed for SPI port
#include <linux/spi/spidev.h>     // Needed for SPI port
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
 static const char *device = "/dev/spidev0.0";
 static uint8_t mode;
 static uint8_t bits = 8;
 static uint32_t speed = 500000;
 static uint16_t delay;
 int ret, fd;

 /* Device oeffen */
 if ((fd = open(device, O_RDWR)) < 0)
 {
  perror("Fehler Open Device");
  exit(1);
 }
 /* Mode setzen */
 ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
 if (ret < 0)
 {
  perror("Fehler Set SPI-Modus");
  exit(1);
 }

 /* Mode abfragen */
 ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
 if (ret < 0)
 {
  perror("Fehler Get SPI-Modus");
  exit(1);
 }

 /* Wortlaenge setzen */
 ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
 if (ret < 0)
 {
  perror("Fehler Set Wortlaenge");
  exit(1);
 }

 /* Wortlaenge abfragen */
 ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
 if (ret < 0)
 {
  perror("Fehler Get Wortlaenge");
  exit(1);
 }

 /* Datenrate setzen */
 ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
 if (ret < 0)
 {
  perror("Fehler Set Speed");
  exit(1);
 }
    
 /* Datenrate abfragen */
 ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
 if (ret < 0)
 {
  perror("Fehler Get Speed");
  exit(1);
 }

 /* Kontrollausgabe */
 printf("SPI-Device.....: %s\n", device);
 printf("SPI-Mode.......: %d\n", mode);
 printf("Wortlaenge.....: %d\n", bits);
 printf("Geschwindigkeit: %d Hz (%d kHz)\n", speed, speed/1000);

 return 0;
}
