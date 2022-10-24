#include <stdint.h>
#include "peripherals.h"

#define USART2_IRQn 38

RCC_t * const RCC = (RCC_t *) 0x40023800;
GPIOx_t * const GPIOA = (GPIOx_t *) 0x40020000;
USART_t * const USART2 = (USART_t *) 0x40004400;
NVIC_t * const NVIC = (NVIC_t *) 0xE000E100;

void wait_ms(int time){
    for(int i = 0; i < time; i++){
        for(int j = 0; j < 1600; j++);
    }
}

void UART2_handler(void){
}

void global_enable_NVIC(void){
    uint32_t priMASK = 0;
    __asm volatile("MSR primask, %0"::"r"(priMASK):"memory");
}

void global_disable_NVIC(void){
    uint32_t priMASK = 1;
    __asm volatile("MSR primask, %0"::"r"(priMASK):"memory");
}

void UART_write(int c){
    while(!(USART2->USART_SR & (1 << 7)));
    USART2->USART_DR |= (c & 0xFF);
}
int main(void){

    global_disable_NVIC();
    /** Enable CLOCK for GPIOA **/
    RCC->RCC_AHB1ENR |= 1;
    /** Enable CLOCK for USART2 **/
    RCC->RCC_APB1ENR |= (1 << 17);

    /** SET AF07 for PA2 **/
    GPIOA->GPIOx_AFRL &= ~(0xF << (2 * 4));
    GPIOA->GPIOx_AFRL |=  (7   << (2 * 4));

    GPIOA->GPIOx_MODER &= ~(3 << (2 * 2));
    GPIOA->GPIOx_MODER |=  (2 << (2 * 2));

    /** SET AF07 for PA3 **/
    GPIOA->GPIOx_AFRL &= ~(0xF << (3 * 4));
    GPIOA->GPIOx_AFRL |=  (7   << (3 * 4));

    GPIOA->GPIOx_MODER &= ~(3 << (3 * 2));
    GPIOA->GPIOx_MODER |=  (2 << (3 * 2));

    /*******************/
    /** Configure CR1 **/
    /*******************/

    // SET OVER8=0
    USART2->USART_CR1 &= ~(1 << 15);
    // Set M to 8len
    USART2->USART_CR1 &= ~(1 << 12);
    // enable TXE Interrupt
    //USART2->USART_CR1 |=  (1 << 7);
    // enable Transmitter
    USART2->USART_CR1 |=  (1 << 3);

    /** SET CR2 -> CR[13:12] Set 00 for 1 STOP BIT **/
    USART2->USART_CR2 &= ~(3 << 12);

    /** RESET CR3 -> Disable flow control RTS CTS **/
    USART2->USART_CR3 = 0;

    /** Set Baud Rate Register **/
    USART2->USART_BRR &= ~0xFFFF;
    USART2->USART_BRR |= ((8 << 4) | (0xB << 0));

    /** Enable UART CR1 **/
    USART2->USART_CR1 |=  (1 << 12);

    /** Enable NVIC IRQn **/
    //NVIC->ISER[USART2_IRQn / 32] |= (1 << (USART2_IRQn % 32));

    //global_enable_NVIC();
    char word[] = "Hello There\n\0";

    for(;;){
        for(int i = 0; i < 13; i++){
            UART_write(word[i]);
        }
        wait_ms(500);
    }
}
