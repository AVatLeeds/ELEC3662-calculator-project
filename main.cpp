#include <stdint.h>
#include "SYSTICK.h"
#include "calculator.h"
#include "status.h"
#include "LCD_driver.h"
#include "keypad.h"

status_LED status;
LCD_driver LCD;
Keypad keypad;
Calculator calc;

void logo_display()
{
    char * block_row = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
    uint8_t idx = 0;
    char * logo_text_1 = "AV-calc         ";
    char * logo_text_2 = "         ver:0.1";

    LCD.cursor_blink_off();
    LCD.cursor_off();

    LCD.cursor_pos(0, 0);
    LCD.print(block_row);
    LCD.cursor_pos(1, 0);
    LCD.print(block_row);

    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);

    while (idx < 16)
    {
        LCD.cursor_pos(0, idx);
        LCD.putchar(logo_text_1[idx]);
        LCD.cursor_pos(1, 15 - idx);
        LCD.putchar(logo_text_2[15 - idx]);
        delay_us(100000);
        idx ++;
    }
    
    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);
    delay_us(50000000);

    LCD.clear();

    LCD.cursor_pos(0, 0);
    LCD.cursor_on();
}

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
    uint32_t clear_counter = 0;
    uint8_t pressed = 0;

    logo_display();

    while (1)
    {
        //keypad_state_test();
        uint32_t keypress = keypad.value();
        if (!pressed)
        {
            switch (keypress)
            {
                case 0x8000: calc.buffer_insert('1'); pressed = 1; break;
                case 0x4000: calc.buffer_insert('2'); pressed = 1; break;
                case 0x2000: calc.buffer_insert('3'); pressed = 1; break;
                case 0x0800: calc.buffer_insert('4'); pressed = 1; break;
                case 0x0400: calc.buffer_insert('5'); pressed = 1; break;
                case 0x0200: calc.buffer_insert('6'); pressed = 1; break;
                case 0x0080: calc.buffer_insert('7'); pressed = 1; break;
                case 0x0040: calc.buffer_insert('8'); pressed = 1; break;
                case 0x0020: calc.buffer_insert('9'); pressed = 1; break;
                case 0x0008: calc.buffer_insert('.'); pressed = 1; break;
                case 0x0004: calc.buffer_insert('0'); pressed = 1; break;
                case 0x0002: calc.buffer_insert('E'); pressed = 1; break;

                case 0x9000: calc.buffer_insert_operator(POWER);    pressed = 1; break;
                case 0x5000: calc.buffer_insert_operator(MULTIPLY); pressed = 1; break;
                case 0x3000: calc.buffer_insert_operator(PLUS);     pressed = 1; break;
                case 0x1800: calc.buffer_insert_operator(ROOT);     pressed = 1; break;
                case 0x1400: calc.buffer_insert_operator(DIVIDE);   pressed = 1; break;
                case 0x1200: calc.buffer_insert_operator(MINUS);    pressed = 1; break;
                case 0x1080: calc.buffer_insert('(');       pressed = 1; break;
                case 0x1020: calc.buffer_insert(')');       pressed = 1; break;

                case 0x1100: calc.buffer_insert_text("ANS");    pressed = 1; break;

                case 0x1040: calc.history_back();       pressed = 1; break;
                case 0x1004: calc.history_forward();    pressed = 1; break;

                case 0x0100: calc.toggle_sign();        pressed = 1; break;
                case 0x1010:
                case 0x0010: calc.buffer_backspace();   pressed = 1; break; 
                case 0x1001:
                case 0x0001: calc.evaluate();           pressed = 1; break;

                case 0x1008: calc.cursor_left();    pressed = 1; break;
                case 0x1002: calc.cursor_right();   pressed = 1; break;

                default: break;             
            }
        }
        else
        {
            delay_us(1); // delay is not accurate !!
            switch (keypress)
            {
                case 0x0010:
                if (clear_counter >= 20000) // should be 2000000 if delay were actually 1us
                {
                    calc.buffer_clear();
                    clear_counter = 0;
                    break;
                }
                else
                {
                    clear_counter ++;
                    break;
                }

                case 0x1000:
                case 0x0000: clear_counter = 0; pressed = 0; break;

                default: break;
            }
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