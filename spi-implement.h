/*
 * @file spi-implement.h
 *
 *  @date Nov 22, 2014
 *  @author ollo
 *
 *  File was downloaded from https://github.com/0110/WookieController in the branch lcd-SSD1803A
 */

#ifndef SPI_IMPLEMENT_H_
#define SPI_IMPLEMENT_H_

#include <stdint.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/** @addtogroup LCD */

typedef enum {
	SPI_IMPL_RET_OK = 0,
	SPI_IMPL_RET_ERROR,
	SPI_IMPL_RET_ERR_OPENDEV,
	SPI_IMPL_RET_ERR_BITSIZE,
	SPI_IMPL_RET_ERR_SPEED,
	SPI_IMPL_RET_ERR_SPEEDVALUE
} spi_implement_ret_t;


spi_implement_ret_t     spi_implement_init(void);
spi_implement_ret_t     spi_implement_close(void);

/**
 * @brief Send data 
 * 
 * @param length	length of data to sent
 * @param txbuf 	buffer with the data to send
 * @return spi_implement_ret_t 
 */
spi_implement_ret_t     spi_implement_send(int length, const void *txbuf);

spi_implement_ret_t     spi_delay(int milliseconds);

/*@}*/

#endif /* SPI_IMPLEMENT_H_ */
