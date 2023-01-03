#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>
#include "LCD_driver.h"

class Calculator
{
    public:
    
    Calculator();

    void buffer_insert(char character);
    void buffer_insert_text(const char * text);
    void toggle_sign();
    void cursor_left();
    void cursor_right();
    void buffer_backspace();
    void buffer_clear();
    void buffer_redisplay();
    void evaluate();

    private:

    void display_result();

    LCD_driver _LCD;
    char _expression_buffer[4096];
    uint16_t _pos = 0;
    uint16_t _head = 0;
    uint8_t _window_start = 0;
    uint8_t _window_length = 16;
    uint8_t _view_threshold = 4;

    double _result;
    char _result_buffer[16];
};

#endif