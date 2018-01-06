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


#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/** @addtogroup LCD */

typedef enum {
	SPI_IMPL_RET_OK,
	SPI_IMPL_RET_ERROR
} spi_implement_ret_t;


spi_implement_ret_t     spi_implement_init(void);

spi_implement_ret_t     spi_implement_send(int n, const void *txbuf);

/*@}*/

#endif /* SPI_IMPLEMENT_H_ */
