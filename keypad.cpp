#include <stdint.h>
#include "SYSCTL.h"
#include "SYSTICK.h"
#include "GPIO.h"
#include "keypad.h"

Keypad::Keypad()
{
    SYSCTL->RCGCGPIO |= (0x1 << 1); // enable the clock to port B
    PORTB->LOCK = 0x4C4F434B; // unlock the commit register for port B
    PORTB->CR = 0xFF; // set the commit register bits for all 8 port B pins
    PORTB->PUR = 0xFF; // enable pull up registers for all port B pins
    PORTB->ODR = 0x0F; // set the row pins as open drain
    PORTB->DR8R = 0x0F; // set the row pins to 8 mA drive
    PORTB->DIR = 0x0F; // set the row pins as output, the rest as input
    PORTB->DEN = 0xFF; // enable all port B pins
}

uint16_t Keypad::value()
{
    uint16_t ambiguity = 0;
    _keypad_state = 0;
    for (uint8_t i = 0; i < 4; i ++)
    {
        // several conditions need to be met for a key combination on the keypad to be ambiguous. If more than
        // one key is pressed on a row and any key in the same columns is pressed on any other row then the
        // keypad state result is ambiguous
        PORTB->DATA = ~(0x1 << i);
        // Delay is required due to the slow rise time on the open drain outputs using the internal pull-ups.
        // Open drain outputs have to be used so that pressing a combination of keys can't short an active high
        // pin into an active low pin on an adjacent row
        delay_us(3.6); 
        _keypad_state |= ((~PORTB->DATA & 0xF0) << (i << 2));
    }
    _keypad_state >>= 4;
    // determine ambiguity
    for (uint8_t i = 0; i < 4; i ++)
    {
        ambiguity += (_keypad_state & (0x1111 << i)) & ((_keypad_state & (0x1111 << i)) - 1);
        //ambiguity &= (ambiguity - 0x1111);
    }
    return (ambiguity & (ambiguity - 1)) ? 0 : _keypad_state;
}
