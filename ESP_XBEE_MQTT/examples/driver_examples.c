/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

#include "circularuart.h"
#include "circularbuffer.h"

struct io_descriptor *io;
struct io_descriptor *stdio;
/**
 * Example of using TARGET_IO to write "Hello World" using the IO abstraction.
 */
void TARGET_IO_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&TARGET_IO, &io);
	usart_sync_enable(&TARGET_IO);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_0[12] = "Hello World!";
extern uint8_t sendData;
static void tx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
   // usart_async_get_io_descriptor(&USART_0, &io);

    if (CircularBuffer_popFrontByte(&txBufferObject, &sendData)) 
    {
            io_write(io, &sendData, 1);
    } 
    
}

static void rx_cb(const struct usart_async_descriptor *const io_descr)
{
    uint8_t  recvdData;
    io_read(io, &recvdData, 1);
    CircularBuffer_pushBackByte(&rxBufferObject, recvdData);

}
static void err_cb(const struct usart_async_descriptor *const io_descr)
{
  uint8_t  x;
  
	/* Transfer completed */
  printf("UART ERROR\r\n");

}

void USART_0_example(void)
{
	

	usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_0, USART_ASYNC_ERROR_CB, err_cb);
	usart_async_get_io_descriptor(&USART_0, &io);
        usart_sync_get_io_descriptor(&TARGET_IO, &stdio);
	usart_async_enable(&USART_0);

	//io_write(io, example_USART_0, 12);
}