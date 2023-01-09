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
    const char * block_row = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
    uint8_t idx = 0;
    const char * logo_text_1 = "AV-calc         ";
    const char * logo_text_2 = "         ver:0.1";

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
    uint32_t traverse_counter = 0;
    uint8_t pressed = 0;
    uint8_t on_release = 0;

    logo_display();

    while (1)
    {
        //keypad_state_test();
        uint32_t keypress = keypad.value();
        if (!pressed)
        {
            switch (keypress)
            {
                case 0x8000: calc.buffer_insert_digit(1); pressed = 1; break;
                case 0x4000: calc.buffer_insert_digit(2); pressed = 1; break;
                case 0x2000: calc.buffer_insert_digit(3); pressed = 1; break;
                case 0x0800: calc.buffer_insert_digit(4); pressed = 1; break;
                case 0x0400: calc.buffer_insert_digit(5); pressed = 1; break;
                case 0x0200: calc.buffer_insert_digit(6); pressed = 1; break;
                case 0x0080: calc.buffer_insert_digit(7); pressed = 1; break;
                case 0x0040: calc.buffer_insert_digit(8); pressed = 1; break;
                case 0x0020: calc.buffer_insert_digit(9); pressed = 1; break;
                case 0x0008: calc.buffer_insert_decimal_point(); pressed = 1; break;
                case 0x0004: calc.buffer_insert_digit(0); pressed = 1; break;
                case 0x0002: calc.buffer_insert_exponent(); pressed = 1; break;

                case 0x9000: calc.buffer_insert_operator(POWER);    pressed = 1; break;
                case 0x5000: calc.buffer_insert_operator(MULTIPLY); pressed = 1; break;
                case 0x3000: calc.buffer_insert_operator(PLUS);     pressed = 1; break;
                case 0x1800: calc.buffer_insert_operator(ROOT);     pressed = 1; break;
                case 0x1400: calc.buffer_insert_operator(DIVIDE);   pressed = 1; break;
                case 0x1200: calc.buffer_insert_operator(MINUS);    pressed = 1; break;

                case 0x1080: calc.buffer_insert_open_bracket();       pressed = 1; break;
                case 0x1020: calc.buffer_insert_close_bracket();       pressed = 1; break;

                case 0x1100: calc.buffer_insert_text("ANS");    pressed = 1; break;

                case 0x0100:
                on_release = 1;
                while (keypress == 0x0100)
                {
                    keypress = keypad.value();
                    switch (keypress)
                    {
                        case 0x8100: calc.buffer_insert_text("sin("); pressed = 1; on_release = 0; break;
                        case 0x4100: calc.buffer_insert_text("cos("); pressed = 1; on_release = 0; break;
                        case 0x2100: calc.buffer_insert_text("tan("); pressed = 1; on_release = 0; break;
                        case 0x0900: calc.buffer_insert_text("asin("); pressed = 1; on_release = 0; break;
                        case 0x0500: calc.buffer_insert_text("acos("); pressed = 1; on_release = 0; break;
                        case 0x0300: calc.buffer_insert_text("atan("); pressed = 1; on_release = 0; break;
                        case 0x0180: calc.buffer_insert_text("deg("); pressed = 1; on_release = 0; break;
                        case 0x0120: calc.buffer_insert_text("rad("); pressed = 1; on_release = 0; break;
                        case 0x0108: calc.buffer_insert_text("ln("); pressed = 1; on_release = 0; break;
                        case 0x0102: calc.buffer_insert_text("log10("); pressed = 1; on_release = 0; break;

                        case 0x0140: calc.buffer_insert_pi(); pressed = 1; on_release = 0; break;
                        case 0x0104: calc.buffer_insert_e(); pressed = 1; on_release = 0; break;

                        case 0x0100:
                        case 0x0000: break;

                        default: pressed = 1; on_release = 0; break;
                    }
                }
                if (on_release) calc.toggle_sign();
                on_release = 0;
                pressed = 1;
                break;

                case 0x1040: calc.history_back();       pressed = 1; break;
                case 0x1004: calc.history_forward();    pressed = 1; break;

                case 0x1010:
                case 0x0010: calc.buffer_backspace();   pressed = 1; break; 
                case 0x1001:
                case 0x0001: calc.evaluate();           pressed = 1; break;

                case 0x1008: calc.cursor_left();    pressed = 1; break;
                case 0x1002: calc.cursor_right();   pressed = 1; break;

                default: break;             
            }
            delay_us(100); // delay is not accurate !!
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

                case 0x1008:
                if (traverse_counter >= 20000) // should be 2000000 if delay were actually 1us
                {
                    calc.cursor_home();
                    traverse_counter = 0;
                    break;
                }
                else
                {
                    traverse_counter ++;
                    break;
                }

                case 0x1002:
                if (traverse_counter >= 20000) // should be 2000000 if delay were actually 1us
                {
                    calc.cursor_end();
                    traverse_counter = 0;
                    break;
                }
                else
                {
                    traverse_counter ++;
                    break;
                }

                case 0x1000:
                case 0x0000:
                clear_counter = 0;
                traverse_counter = 0;
                delay_us(100);
                keypress = keypad.value();
                if (keypress == 0x0000 || keypress == 0x1000) pressed = 0;
                break;

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