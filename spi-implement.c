/**
 * @file spi-implement.c
 * @author Ollo
 * @brief 
 * @version 0.1
 * @date 2020-06-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "spi-implement.h"

#include <unistd.h>
#include <fcntl.h>                // Needed for SPI port
#include <sys/ioctl.h>            // Needed for SPI port
#include <linux/spi/spidev.h>     // Needed for SPI port

#define     SPIDEVICE   "/dev/spidev0.0"
#define     BITS        8
#define     SPEED       500000              /**< 500 kHz*/

/******************************************************************************
 * PROTOTYPE
 ******************************************************************************/

/******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************/
static int gSpiFd = 0;

/******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************/

spi_implement_ret_t     spi_implement_init(void)
{
    static const char *device = SPIDEVICE;
    static uint8_t mode;
    static uint8_t bits = BITS;
    static uint32_t speed = SPEED;
    static uint16_t delay;
    int ret;

    /* Open device */
    if ((gSpiFd = open(device, O_RDWR)) < 0)
    {
        return SPI_IMPL_RET_ERR_OPENDEV;
    }
    
    /* set length */
    ret = ioctl(gSpiFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret < 0)
    {
        return SPI_IMPL_RET_ERR_BITSIZE;
    }

    ret = ioctl(gSpiFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret < 0)
    {
        return SPI_IMPL_RET_ERR_SPEED;
    }
        
    /* check speed */
    ret = ioctl(gSpiFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if ((ret < 0) || (speed != SPEED))
    {
        return SPI_IMPL_RET_ERR_SPEEDVALUE;
    }

    return SPI_IMPL_RET_OK;
}

spi_implement_ret_t     spi_implement_send(int length, const void *txbuf)
{
    if (gSpiFd == 0)  {
        return SPI_IMPL_RET_ERR_OPENDEV;
    }

    if (length <= 0) {
        return SPI_IMPL_RET_ERROR;
    }
    write(gSpiFd, txbuf, length);

    return SPI_IMPL_RET_OK;
}

spi_implement_ret_t     spi_delay(int milliseconds)
{
    usleep(milliseconds * 1000);
}