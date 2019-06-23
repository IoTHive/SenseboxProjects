#include <atmel_start.h>
void Switchcallback()
{
  gpio_toggle_pin_level(STATUS_RED);
  
}

void Switchcallback2()
{
  gpio_toggle_pin_level(STATUS_RED);
  
}

int main(void)
{
    uint32_t status;
    
/* Initializes MCU, drivers and middleware */
	atmel_start_init();
        status  = ext_irq_register(20,Switchcallback);
        status  = ext_irq_register(21,Switchcallback2);
	/* Replace with your application code */
	while (1) {
	}
}
