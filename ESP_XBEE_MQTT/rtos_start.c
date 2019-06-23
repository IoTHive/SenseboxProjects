/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#include "atmel_start.h"
#include "rtos_start.h"
#include "ESP8266Client.h"
#define TASK_EXAMPLE_STACK_SIZE (1024 / sizeof(portSTACK_TYPE))
#define TASK_EXAMPLE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedExampleTask;
static SemaphoreHandle_t disp_mutex;
extern long unsigned int network_gettime_ms(void);
/**
 * OS example task
 *
 * \param[in] p The void pointer for OS task Standard model.
 *
 */
static void example_task(void *p)
{
	(void)p;
        uint8_t x;
        uint32_t num = 0;
        ESP82_Result_t espResult = ESP82_SUCCESS;
         uint8_t dataBuf[] = "AT\r\n";
	while (1) 
        {

          if(ringbuffer_num((struct ringbuffer *const)&USART_0.rx) != 0)
          {
            while(ERR_NONE == ringbuffer_get((struct ringbuffer *const)&USART_0.rx,&x))
            {
                printf("%c",x);
            }
            printf("scan cycle - %d\n\r",num++);
             

          }
          //io_write(io, dataBuf, sizeof(dataBuf)-1);
          ESP82_sendCmd(dataBuf, sizeof(dataBuf)-1);
          if(num > 5)
          {
              ESP82_Init(115200, false, (uint32_t(*const)(void))network_gettime_ms);
              espResult = ESP82_ConnectWifi(true, "SmartDev", "aaaaaaaa");
          }
		os_sleep(2000);
	}
}

/*
 * Example
 */
void FREERTOS_V823_0_example(void)
{
	disp_mutex = xSemaphoreCreateMutex();

	if (disp_mutex == NULL) {
		while (1) {
			;
		}
	}

	if (xTaskCreate(
	        example_task, "Example", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedExampleTask)
	    != pdPASS) {
		while (1) {
			;
		}
	}

	vTaskStartScheduler();

	return;
}
