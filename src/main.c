#include <stdint.h>
#include <stdio.h>

#include "peripherals.h"

#define USART2_IRQn 38

RCC_t   * const RCC     = (RCC_t    *)  0x40023800;
GPIOx_t * const GPIOA   = (GPIOx_t  *)  0x40020000;
USART_t * const USART2  = (USART_t  *)  0x40004400;
NVIC_t  * const NVIC    = (NVIC_t   *)  0xE000E100;

void initialise_monitor_handles(void);


int main(void){

    initialise_monitor_handles();

    for(;;){
        printf("Hello World\r\n");
    }
}
