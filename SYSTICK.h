#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define F_CPU 80000000

#define STCTRL      (*((volatile uint32_t *)0xE000E010))
#define STRELOAD    (*((volatile uint32_t *)0xE000E014))
#define STCURRENT   (*((volatile uint32_t *)0xE000E018))

#define delay_us(DELAY) (systick_delay((DELAY) * (F_CPU / 1E6)))

static inline void systick_delay(const uint32_t count)
{
    STRELOAD = count - 1;
    //STCURRENT = 0x0; //writing to this register clears it and starts the counter again from the value in the reload register
    STCTRL |= 0x1;
    while (!(STCTRL & (1U << 16)));
    STCTRL &= ~0x1;
}

#endif