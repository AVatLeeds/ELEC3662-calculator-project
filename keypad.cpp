#include <stdint.h>
#include "SYSCTL.h"
#include "GPIO.h"
#include "keypad.h"

Keypad::Keypad()
{
    SYSCTL->RCGCGPIO |= (0x1 < 1); // enable the clock to port B
    PORTB->LOCK = 0x4C4F434B; // unlock the commit register for port B
    PORTB->CR = 0xFF; // set the commit register bits for all 8 port B pins
    PORTB->DIR = 0xF; // set the lower 4 pins as output, the rest as input
    PORTB->DEN = 0xFF; // enable all port B pins
}

uint16_t Keypad::value()
{
    for (_keypad_state = 0, PORTB->DATA = 0x1, _poll_counter = 0; _poll_counter < 13; _poll_counter += 4)
    {
        _keypad_state |= ((PORTB->DATA & 0xF0) << _poll_counter);
        PORTB->DATA <<= 1;
    }
    return _keypad_state >> 4;
}
