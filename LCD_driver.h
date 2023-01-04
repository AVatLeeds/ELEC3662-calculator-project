#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#include <stdint.h>

#define LCD_CLEAR               0x01
#define LCD_HOME                0x02
#define LCD_CURSOR_BACK         0x10
#define LCD_CURSOR_FWD          0x14
#define LCD_PAN_LEFT            0x18
#define LCD_PAN_RIGHT           0x1C
#define LCD_CURSOR_OFF          0x0C
#define LCD_CURSOR_ON           0x0E
#define LCD_CURSOR_BLINK        0x0F
#define LCD_CURSOR_LINE2        0xC0
    
#define MODE_4BIT               0x20
#define FUNCTION_SET            0x20
#define TWO_LINE                0x08
#define BIG_FONT                0x04
#define MODE_8BIT               0x10
#define DISPLAY_SETUP           0x08
#define DISPLAY_ON              0x04
#define CURSOR_ON               0x02
#define CURSOR_BLINK            0x01
#define LCD_CLEAR               0x01
#define ENTRY_MODE              0x04
#define INCREMENT_CURSOR        0x02
#define SHIFT_DISPLAY           0x01

#define NUM_ROWS                2
#define NUM_COLS                16

class LCD_driver
{
    public:
    LCD_driver();

    void clear();
    void display_on();
    void display_off();
    void cursor_on();
    void cursor_off();
    void cursor_blink_on();
    void cursor_blink_off();
    void putchar(char character);
    void print (const char * string);
    void cursor_pos(uint8_t row, uint8_t column);

    private:
    void _command(uint8_t command_byte);
    void _write_lower_nibble(uint8_t data_byte);
    void _write_upper_nibble(uint8_t data_byte);
    uint8_t _check_busy();

    uint8_t _cursor_state;
    uint8_t _display_state;
};

#endif