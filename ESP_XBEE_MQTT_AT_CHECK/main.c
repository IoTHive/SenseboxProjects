#include <atmel_start.h>


int main(void)
{
    uint8_t dataBuf[] = "AT\r\n";
    struct io_descriptor *io;
    struct io_descriptor *stdio;
    uint8_t x;
    uint32_t num = 0;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	USART_0_example();
	usart_async_enable(&USART_0);
	usart_sync_get_io_descriptor(&TARGET_IO, &stdio);
	usart_async_get_io_descriptor(&USART_0, &io);
	//io_write(io, dataBuf, sizeof(dataBuf));
	/* Replace with your application code */

	while (1) 
        {
         
          delay_ms(1000);
          if(ringbuffer_num((struct ringbuffer *const)&USART_0.rx) != 0)
          {
            while(ERR_NONE == ringbuffer_get((struct ringbuffer *const)&USART_0.rx,&x))
            {
                printf("%c",x);
            }
            printf("scan cycle - %d\n\r",num++);
             

          }
          io_write(io, dataBuf, sizeof(dataBuf)-1);
          
	}
}
