#include <stdint.h>
#include "calculator.h"
#include "status.h"
#include "LCD_driver.h"
#include "keypad.h"

status_LED status;
LCD_driver LCD;
Keypad keypad;
Calculator calc;

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
    //LCD.print("Hello Oti :)");
    uint8_t pressed = 0;

    while (1)
    {
        //keypad_state_test();
        uint32_t keypress = keypad.value();
        switch (keypress)
        {
            case 0x8000: pressed ? : (calc.buffer_insert('1'), pressed = 1); break;
            case 0x4000: pressed ? : (calc.buffer_insert('2'), pressed = 1); break;
            case 0x2000: pressed ? : (calc.buffer_insert('3'), pressed = 1); break;
            case 0x0800: pressed ? : (calc.buffer_insert('4'), pressed = 1); break;
            case 0x0400: pressed ? : (calc.buffer_insert('5'), pressed = 1); break;
            case 0x0200: pressed ? : (calc.buffer_insert('6'), pressed = 1); break;
            case 0x0080: pressed ? : (calc.buffer_insert('7'), pressed = 1); break;
            case 0x0040: pressed ? : (calc.buffer_insert('8'), pressed = 1); break;
            case 0x0020: pressed ? : (calc.buffer_insert('9'), pressed = 1); break;
            case 0x0008: pressed ? : (calc.buffer_insert('.'), pressed = 1); break;
            case 0x0004: pressed ? : (calc.buffer_insert('0'), pressed = 1); break;
            case 0x0002: pressed ? : (calc.buffer_insert('E'), pressed = 1); break;

            case 0x9000: pressed ? : (calc.buffer_insert_operator(POWER), pressed = 1); break;
            case 0x5000: pressed ? : (calc.buffer_insert_operator(MULTIPLY), pressed = 1); break;
            case 0x3000: pressed ? : (calc.buffer_insert_operator(PLUS), pressed = 1); break;
            case 0x1800: pressed ? : (calc.buffer_insert_operator(ROOT), pressed = 1); break;
            case 0x1400: pressed ? : (calc.buffer_insert_operator(DIVIDE), pressed = 1); break;
            case 0x1200: pressed ? : (calc.buffer_insert_operator(MINUS), pressed = 1); break;
            case 0x1080: pressed ? : (calc.buffer_insert('('), pressed = 1); break;
            case 0x1020: pressed ? : (calc.buffer_insert(')'), pressed = 1); break;

            case 0x1100: pressed ? : (calc.buffer_insert_text("ANS"), pressed = 1); break;

            case 0x1040: pressed ? : (calc.history_back(), pressed = 1); break;
            case 0x1004: pressed ? : (calc.history_forward(), pressed = 1); break;

            case 0x0100: pressed ? : (calc.toggle_sign(), pressed = 1); break;
            case 0x1010:
            case 0x0010: pressed ? : (calc.buffer_backspace(), pressed = 1); break; 
            case 0x1001:
            case 0x0001: pressed ? : (calc.evaluate(), pressed = 1); break;

            case 0x1008: pressed ? : (calc.cursor_left(), pressed = 1); break;
            case 0x1002: pressed ? : (calc.cursor_right(), pressed = 1); break;
            
            case 0x1000:
            case 0x0000: pressed = 0; break;

            default: break;             
        }
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

void NMI()
{
    status = BLUE;
    while (1);
}

void _ISR_system_control()
{
    status = CYAN;
    while (1);
}