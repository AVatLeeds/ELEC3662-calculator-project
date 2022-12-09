#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

// Port B will be used to read from the keypad
// the rows connected to pins 0 to 3 and the
// columns connecting to pins 4 to 7.

class Keypad
{
    public:
    Keypad();

    uint16_t value();

    private:
    uint8_t     _poll_counter = 0;
    uint32_t    _keypad_state;
};

#endif