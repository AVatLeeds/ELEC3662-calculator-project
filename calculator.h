#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>
#include "LCD_driver.h"
#include "recursive_descent.h"

#define HISTORY_LENGTH  16

class Calculator
{
    public:
    
    Calculator();

    void buffer_insert(char character);
    void buffer_insert_digit(uint8_t digit);
    void buffer_insert_operator(enum op op);
    void buffer_insert_exponent();
    void buffer_insert_decimal_point();
    void buffer_insert_open_bracket();
    void buffer_insert_close_bracket();
    void buffer_insert_pi();
    void buffer_insert_e();
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

    enum type {DIGIT = 1, OPERATOR = 2, EXPONENT = 3, DECIMAL_POINT = 4, OPEN_BRACKET = 5, CLOSE_BRACKET = 6, TEXT = 7};
    char _expression_buffer[256];
    enum type _buffer_mask[256];

    uint8_t _pos = 0;
    uint8_t _head = 0;
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