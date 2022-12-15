#include <stdint.h>
#include "status.h"
#include "LCD_driver.h"
#include "keypad.h"

status_LED status;
LCD_driver LCD;
Keypad keypad;

void keypad_state_test()
{
    LCD.cursor_pos(1, 0);
    uint32_t keypress = keypad.value();
    LCD.print("Keypad: 0x");
    LCD.putchar(((keypress <<= 4), ((keypress & 0xF0000) >> 16) + 0x30 + ((keypress & 0xF0000) > 0x90000) * 0x7));
    LCD.putchar(((keypress <<= 4), ((keypress & 0xF0000) >> 16) + 0x30 + ((keypress & 0xF0000) > 0x90000) * 0x7));
    LCD.putchar(((keypress <<= 4), ((keypress & 0xF0000) >> 16) + 0x30 + ((keypress & 0xF0000) > 0x90000) * 0x7));
    LCD.putchar(((keypress <<= 4), ((keypress & 0xF0000) >> 16) + 0x30 + ((keypress & 0xF0000) > 0x90000) * 0x7));
}

int main(void)
{   
    status = WHITE;
    LCD.print("Hello Oti :)");
    uint8_t pressed = 0;

    while (1)
    {
        keypad_state_test();
    }
}

void hard_fault()
{
    status = RED;
    while (1);
}

void usage_fault()
{
    status = MAGENTA;
    while (1);
}

void bus_fault()
{
    status = YELLOW;
    while (1);
}