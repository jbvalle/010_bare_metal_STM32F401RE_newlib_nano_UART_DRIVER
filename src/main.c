#include <stdint.h>
#include "peripherals.h"

RCC_t * const RCC = (RCC_t *) 0x40023800;
GPIOx_t * const GPIOA = (GPIOx_t *) 0x40020000;
USART_t * const USART2 = (USART_t *) 0x40004400;

void wait_ms(int time){
    for(int i = 0; i < time; i++){
        for(int j = 0; j < 1600; j++);
    }
}
int main(void){

    RCC->RCC_AHB1ENR |= 1;

    GPIOA->GPIOx_MODER &= ~(3 << (5 * 2));
    GPIOA->GPIOx_MODER |=  (1 << (5 * 2));
    /** Enable CLOCK for GPIOA **/
    /** Enable CLOCK for USART2 **/

    /** SET AF07 for PA2 and PA3 **/
    /** SET AF MODE for PA2 and PA3 **/

    /** Set Baud Rate Register **/
    /** SET CR1 -> CR1[3, 2] Enable TXE RXE **/

    /** SET CR2 -> CR[13:12] Set 00 for 1 STOP BIT **/

    /** RESET CR3 -> Disable flow control RTS CTS **/

    /** Enable UART CR1 **/

    for(;;){
        GPIOA->GPIOx_ODR ^= (1 << 5);
        wait_ms(100);
        /** Wait until TXE Empty SR **/

        /** Write to DR **/
    }
}
