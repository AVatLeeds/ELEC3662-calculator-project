#ifndef CALCULATOR_H
#define CALCULATOR_H

#define HISTORY_LENGTH  16

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
    void history_back();
    void history_forward();
    void buffer_backspace();
    void buffer_clear();
    void buffer_redisplay();
    void evaluate();

    private:

    void display_result();
    void clear_result();
    bool _computed = false;

    LCD_driver _LCD;

    char _expression_buffer[256];

    uint16_t _pos = 0;
    uint16_t _head = 0;
    uint8_t _window_start = 0;
    uint8_t _window_length = 16;
    uint8_t _view_threshold = 4;

    char _expression_history[HISTORY_LENGTH][256];
    int8_t _hist_idx = 0;
    uint8_t _hist_head = 0;
    bool _hist_overflow = false;

    double _result;
    char _result_buffer[16];
};

#endif