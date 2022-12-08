// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 11, 2014

// Lab 8
//      Jon Valvano and Ramesh Yerraballi
//      November 21, 2013

// ***** 1. Pre-processor Directives Section *****
//#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
//void DisableInterrupts(void); // Disable interrupts
//void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

// System control registers
#define SYSTEM_CTRL_BASE	0x400FE000

#define RCGCGPIO	(*(volatile uint32_t *)(SYSTEM_CTRL_BASE + 0x608))


// GPIO port base addresses on APB bus
#define PORTA	0x40004000
#define PORTB	0x40005000
#define PORTC	0x40006000
#define PORTD	0x40007000
#define PORTE	0x40024000
#define PORTF	0x40025000

#define GPIO_DATA(BASE)		(*(volatile uint32_t *)((BASE) + 0x000))
	
#define GPIO_DIR(BASE)		(*(volatile uint32_t *)((BASE) + 0x400))
#define GPIO_IS(BASE)			(*(volatile uint32_t *)((BASE) + 0x404))
#define GPIO_IBE(BASE)		(*(volatile uint32_t *)((BASE) + 0x408))
#define GPIO_IEV(BASE)		(*(volatile uint32_t *)((BASE) + 0x40C))
#define GPIO_IM(BASE)			(*(volatile uint32_t *)((BASE) + 0x410))
#define GPIO_RIS(BASE)		(*(volatile uint32_t *)((BASE) + 0x414))
#define GPIO_MIS(BASE)		(*(volatile uint32_t *)((BASE) + 0x418))
#define GPIO_ICR(BASE)		(*(volatile uint32_t *)((BASE) + 0x41C))
#define GPIO_AFSEL(BASE)	(*(volatile uint32_t *)((BASE) + 0x420))
#define GPIO_DR2R(BASE)		(*(volatile uint32_t *)((BASE) + 0x500))
#define GPIO_DR4R(BASE)		(*(volatile uint32_t *)((BASE) + 0x504))
#define GPIO_DR8R(BASE)		(*(volatile uint32_t *)((BASE) + 0x508))
#define GPIO_ODR(BASE)		(*(volatile uint32_t *)((BASE) + 0x50C))
#define GPIO_PUR(BASE)		(*(volatile uint32_t *)((BASE) + 0x510))
#define GPIO_PDR(BASE)		(*(volatile uint32_t *)((BASE) + 0x514))
#define GPIO_SLR(BASE)		(*(volatile uint32_t *)((BASE) + 0x518))
#define GPIO_DEN(BASE)		(*(volatile uint32_t *)((BASE) + 0x51C))
#define GPIO_LOCK(BASE)		(*(volatile uint32_t *)((BASE) + 0x520))
#define GPIO_CR(BASE)			(*(volatile uint32_t *)((BASE) + 0x524))
#define GPIO_AMSEL(BASE)	(*(volatile uint32_t *)((BASE) + 0x528))
#define GPIO_PCTL(BASE)		(*(volatile uint32_t *)((BASE) + 0x52C))
#define GPIO_ADCCTL(BASE)	(*(volatile uint32_t *)((BASE) + 0x530))
#define GPIO_DMACTL(BASE)	(*(volatile uint32_t *)((BASE) + 0x534))
	
#define GPIO_PERIPHID4(BASE)	(*(volatile uint32_t *)((BASE) + 0xFD0))
#define GPIO_PERIPHID5(BASE)	(*(volatile uint32_t *)((BASE) + 0xFD4))
#define GPIO_PERIPHID6(BASE)	(*(volatile uint32_t *)((BASE) + 0xFD8))
#define GPIO_PERIPHID7(BASE)	(*(volatile uint32_t *)((BASE) + 0xFDC))
#define GPIO_PERIPHID0(BASE)	(*(volatile uint32_t *)((BASE) + 0xFE0))
#define GPIO_PERIPHID1(BASE)	(*(volatile uint32_t *)((BASE) + 0xFE4))
#define GPIO_PERIPHID2(BASE)	(*(volatile uint32_t *)((BASE) + 0xFE8))
#define GPIO_PERIPHID3(BASE)	(*(volatile uint32_t *)((BASE) + 0xFEC))
#define GPIO_CELLID0(BASE)		(*(volatile uint32_t *)((BASE) + 0xFF0))
#define GPIO_CELLID1(BASE)		(*(volatile uint32_t *)((BASE) + 0xFF4))
#define GPIO_CELLID2(BASE)		(*(volatile uint32_t *)((BASE) + 0xFF8))
#define GPIO_CELLID3(BASE)		(*(volatile uint32_t *)((BASE) + 0xFFC))

#define GPIO_OUTPUT(PORT, PIN)	(GPIO_DIR((PORT)) |= (1 << (PIN)))
#define GPIO_INPUT(PORT, PIN)		(GPIO_DIR((PORT)) &= ~(1 << (PIN)))

#define GPIO_SET(PORT, PIN)			(GPIO_DATA((PORT)) |= (1 << (PIN)))
#define GPIO_CLEAR(PORT, PIN)		(GPIO_DATA((PORT)) &= ~(1 << (PIN)))

#define GPIO_ALTERNATIVE_FUNCTION(PORT, PIN, STATE)	(GPIO_AFSEL(PORT) = (STATE) ? (

void GPIO_digital_out(uint32_t BASE)
{
	
}


// PE0, PB0, or PA2 connected to positive logic momentary switch using 10 k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
//  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1);  // activate grader and set system clock to 80 MHz
  
        
//  EnableInterrupts();           // enable interrupts for the grader
  while(1){
    
  }
  
}
