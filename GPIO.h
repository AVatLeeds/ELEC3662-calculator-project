#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

struct GPIO_registers
{
    volatile uint32_t GPIODATA;
    volatile const uint32_t PADDING0[0xFF];
    volatile uint32_t GPIODIR;
    volatile uint32_t GPIOIS;
    volatile uint32_t GPIOIBE;
    volatile uint32_t GPIOIEV;
    volatile uint32_t GPIOIM;
    volatile uint32_t GPIORIS;
    volatile uint32_t GPIOMIS;
    volatile uint32_t GPIOICR;
    volatile uint32_t GPIOAFSEL;
    volatile const uint32_t PADDING1[0x37];
    volatile uint32_t GPIODR2R;
    volatile uint32_t GPIODR4R;
    volatile uint32_t GPIODR8R;
    volatile uint32_t GPIOODR;
    volatile uint32_t GPIOPUR;
    volatile uint32_t GPIOPDR;
    volatile uint32_t GPIOSLR;
    volatile uint32_t GPIODEN;
    volatile uint32_t GPIOLOCK;
    volatile uint32_t GPIOCR;
    volatile uint32_t GPIOAMSEL;
    volatile uint32_t GPIOPCTL;
    volatile uint32_t GPIOADCCTL;
    volatile uint32_t GPIODMACTL;
    volatile const uint32_t PADDING2[0x2A6];
    volatile uint32_t GPIOPID4;
    volatile uint32_t GPIOPID5;
    volatile uint32_t GPIOPID6;
    volatile uint32_t GPIOPID7;
    volatile uint32_t GPIOPID0;
    volatile uint32_t GPIOPID1;
    volatile uint32_t GPIOPID2;
    volatile uint32_t GPIOPID3;
    volatile uint32_t GPIOPCID0;
    volatile uint32_t GPIOPCID1;
    volatile uint32_t GPIOPCID2;
    volatile uint32_t GPIOPCID3;
};

#define PORTA_BASE_APB  0x40004000
#define PORTA_BASE_AHB  0x40058000
#define PORTB_BASE_APB  0x40005000
#define PORTB_BASE_AHB  0x40059000
#define PORTC_BASE_APB  0x40006000
#define PORTC_BASE_AHB  0x4005A000
#define PORTD_BASE_APB  0x40007000
#define PORTD_BASE_AHB  0x4005B000
#define PORTE_BASE_APB  0x40024000
#define PORTE_BASE_AHB  0x4005C000
#define PORTF_BASE_APB  0x40025000
#define PORTF_BASE_AHB  0x4005D000

#define GPIO_PORTA  ((struct GPIO_registers *)PORTA_BASE_APB)
#define GPIO_PORTB  ((struct GPIO_registers *)PORTB_BASE_APB)
#define GPIO_PORTC  ((struct GPIO_registers *)PORTC_BASE_APB)
#define GPIO_PORTD  ((struct GPIO_registers *)PORTD_BASE_APB)
#define GPIO_PORTE  ((struct GPIO_registers *)PORTE_BASE_APB)
#define GPIO_PORTF  ((struct GPIO_registers *)PORTF_BASE_APB)

#endif