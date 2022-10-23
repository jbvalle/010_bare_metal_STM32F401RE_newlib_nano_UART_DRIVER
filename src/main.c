#include <stdint.h>
#include "peripherals.h"

RCC_t * const RCC = (RCC_t *) 0x40023800;
GPIOx_t * const GPIOA = (GPIOx_t *) 0x40020000;
USART_t * const USART2 = (USART_t *) 0x40004400;

int main(void){

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
        /** Wait until TXE Empty SR **/

        /** Write to DR **/
    }
}
