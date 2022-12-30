#include <stdint.h>
#include "SYSCTL.h"
#include "SYSTICK.h"
#include "GPIO.h"
#include "LCD_driver.h"

// LCD control lines are connected to
// port A pin 2 - EN
// port A pin 3 - RS
// port A pin 4 - R/W

// bit specific addressing is used here, where the full data register address is the mask
#define EN  (*((volatile uint32_t *)(PORTA_BASE_APB + 0x010))) //(*((&(PORTA->DATA_BASE)) + 0x010))
#define RS  (*((volatile uint32_t *)(PORTA_BASE_APB + 0x020))) //(*((&(PORTA->DATA_BASE)) + 0x020))
#define RW  (*((volatile uint32_t *)(PORTA_BASE_APB + 0x040))) //(*((&(PORTA->DATA_BASE)) + 0x040))

#define HIGH    0xFF
#define LOW     0x00

// Port C pins 4 to 7 are used for the LCD data bits
// bit specific addressing is used here again

#define LCD_DATA_PINS   (*((volatile uint32_t *)(PORTC_BASE_APB + 0x3C0)))

int x = 0, y = 0;

LCD_driver::LCD_driver()
{
    // setup port A pins
    SYSCTL->RCGCGPIO |= 0x1;
    PORTA->LOCK = 0x4C4F434B;
    PORTA->CR |= 0x1C;
    PORTA->AFSEL &= ~0x1C;
    PORTA->PCTL &= ~0x1C;
    PORTA->DIR |= 0x1C;
    PORTA->DEN |= 0x1C;

    // setup port C pins
    SYSCTL->RCGCGPIO |= 0x4;
    PORTC->LOCK = 0x4C4F434B;
    PORTC->CR |= 0xF0;
    PORTC->AFSEL &= ~0xF0;
    PORTC->PCTL &= ~0xFFFF0000;
    PORTC->DEN |= 0xF0;

    RS = LOW;
    delay_us(15000); // delay ~15 ms
    _write_upper_nibble(MODE_8BIT);
    delay_us(4500); // delay ~4.5 ms
    _write_upper_nibble(MODE_8BIT);
    delay_us(100); // delay ~100 us
    _write_upper_nibble(MODE_8BIT);
    _write_upper_nibble(MODE_4BIT);
    _command(FUNCTION_SET | MODE_4BIT | TWO_LINE);
    _command(DISPLAY_SETUP);
    _command(LCD_CLEAR);
    _command(DISPLAY_SETUP | DISPLAY_ON | CURSOR_ON); //| CURSOR_BLINK);
    _command(ENTRY_MODE | INCREMENT_CURSOR);
}

void LCD_driver::_write_lower_nibble(uint8_t data_byte)
{
    data_byte <<= 4;
    PORTC->DIR |= 0xF0; // need a more explicit way of setting LCD data pins to output / input
    RW = LOW;
    EN = HIGH;
    LCD_DATA_PINS = data_byte;
    delay_us(1);
    EN = LOW;
    delay_us(1);
    LCD_DATA_PINS = 0x00;
}

void LCD_driver::_write_upper_nibble(uint8_t data_byte)
{
    PORTC->DIR |= 0xF0; // need a more explicit way of setting LCD data pins to output / input
    RW = LOW;
    EN = HIGH;
    LCD_DATA_PINS = data_byte;
    delay_us(1);
    EN = LOW;
    delay_us(1);
    LCD_DATA_PINS = 0x00;
}

uint8_t LCD_driver::_check_busy()
{
    uint8_t busy;
    PORTC->DIR &= ~0xF0; // need a more explicit way of setting LCD data pins to output / input
    RS = LOW;
    RW = HIGH;
    // small delay required here to meet the minimum 40 ns t_AS requirement during read
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    EN = HIGH;
    delay_us(0.5);   
    busy = LCD_DATA_PINS & 0x80;
    delay_us(0.5);   
    EN = LOW;
    delay_us(1);
    EN = HIGH;
    delay_us(1);
    EN = LOW;
    delay_us(1);
    return busy;
}

void LCD_driver::_command(uint8_t data_byte)
{
    while (_check_busy());
    RS = LOW;
    _write_upper_nibble(data_byte);
    _write_lower_nibble(data_byte);
}

void LCD_driver::clear(void) {
    _command(LCD_CLEAR);
}

void LCD_driver::putchar(char character) {
    while (_check_busy());
    RS = HIGH;
    _write_upper_nibble(character);
    _write_lower_nibble(character);
}

void LCD_driver::print(const char *str) {
    uint32_t i = 0;
    while (str[i])
    {
        putchar(str[i++]);
    }
}

void LCD_driver::cursor_pos(uint8_t row, uint8_t column) {
    if ((row > (NUM_ROWS - 1)) || (column > (NUM_COLS - 1))) {
        return;
    }
    _command((row == 1) ? (0xC0 | column) : (0x80 | column));
}
