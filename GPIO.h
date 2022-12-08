#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

struct GPIO_registers
{
    volatile uint32_t DATA;
    volatile const uint32_t PADDING0[0xFF];
    volatile uint32_t DIR;
    volatile uint32_t IS;
    volatile uint32_t IBE;
    volatile uint32_t IEV;
    volatile uint32_t IM;
    volatile uint32_t RIS;
    volatile uint32_t MIS;
    volatile uint32_t ICR;
    volatile uint32_t AFSEL;
    volatile const uint32_t PADDING1[0x37];
    volatile uint32_t DR2R;
    volatile uint32_t DR4R;
    volatile uint32_t DR8R;
    volatile uint32_t ODR;
    volatile uint32_t PUR;
    volatile uint32_t PDR;
    volatile uint32_t SLR;
    volatile uint32_t DEN;
    volatile uint32_t LOCK;
    volatile uint32_t CR;
    volatile uint32_t AMSEL;
    volatile uint32_t PCTL;
    volatile uint32_t ADCCTL;
    volatile uint32_t DMACTL;
    volatile const uint32_t PADDING2[0x2A6];
    volatile uint32_t PID4;
    volatile uint32_t PID5;
    volatile uint32_t PID6;
    volatile uint32_t PID7;
    volatile uint32_t PID0;
    volatile uint32_t PID1;
    volatile uint32_t PID2;
    volatile uint32_t PID3;
    volatile uint32_t PCID0;
    volatile uint32_t PCID1;
    volatile uint32_t PCID2;
    volatile uint32_t PCID3;
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

#define PORTA  ((struct GPIO_registers *)PORTA_BASE_APB)
#define PORTB  ((struct GPIO_registers *)PORTB_BASE_APB)
#define PORTC  ((struct GPIO_registers *)PORTC_BASE_APB)
#define PORTD  ((struct GPIO_registers *)PORTD_BASE_APB)
#define PORTE  ((struct GPIO_registers *)PORTE_BASE_APB)
#define PORTF  ((struct GPIO_registers *)PORTF_BASE_APB)

#endif