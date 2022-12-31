#include <stdint.h>
#include <stdio.h>
#include "calculator.h"
#include "recursive_descent.h"

Calculator::Calculator() : _LCD()
{
    _LCD.cursor_pos(0, 0);
}

void Calculator::buffer_insert(char character)
{
    if (_pos < _head)
    {
        for (uint16_t i = _head; i > _pos; _expression_buffer[i] = _expression_buffer[i - 1], i --); 
    }
    _expression_buffer[_pos++] = character;
    _head ++;
    _window_start += 1 & (_pos == (_window_start + _window_length));
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::buffer_backspace()
{
    if (_pos)
    {
        _pos--;
        if (_pos < _head)
        {
            for (uint16_t i = _pos; i < _head; _expression_buffer[i] = _expression_buffer[i + 1], i ++);
        }
        _head--;
        if (_pos < (_window_start + (_window_length - _view_threshold)) && _window_start)
        {
            _window_start --;
        }
        buffer_redisplay();
        _LCD.cursor_pos(0, _pos - _window_start);
    } 
}

void Calculator::buffer_clear()
{
    _pos = 0;
    _head = 0;
    _window_start = 0;
    buffer_redisplay();
    _LCD.cursor_pos(0, 0);
}

void Calculator::cursor_left()
{
    if (_pos)
    {
        _pos --;
        if (_pos < (_window_start + (_window_length - _view_threshold)) && _window_start)
        {
            _window_start --;
            buffer_redisplay();
        }
        _LCD.cursor_pos(0, _pos - _window_start);
    }
}

void Calculator::cursor_right()
{
    if (_pos < _head)
    {
        _pos ++;
        if (_pos == (_window_start + _window_length))
        {
            _window_start ++;
            buffer_redisplay();
        }
        _LCD.cursor_pos(0, _pos - _window_start);
    }
}

void Calculator::buffer_redisplay()
{
    _LCD.cursor_pos(0, 0);
    for (uint8_t i = _window_start; i < (_window_start + _window_length); i ++)
    {
        if (i < _head)
        {
            _LCD.putchar(_expression_buffer[i]);
        }
        else
        {
            _LCD.putchar(' ');
        }
    }
}

void Calculator::buffer_insert_text(const char * text)
{
    _LCD.print(text);
}

void Calculator::toggle_sign()
{
    if (_expression_buffer[_pos] == '-')
    {
        buffer_backspace();
    }
    else
    {
        buffer_insert('-');
    }
}

void Calculator::evaluate()
{
    char * expression = _expression_buffer;
    _LCD.cursor_pos(1, 0);
    int return_value;
    if (parse_expression(expression, _result))
    {
        return_value = snprintf(_result_buffer, 16, "%f", _result);
        _LCD.print(_result_buffer);
    }
    else {
    _LCD.print("Bad expression");
    }
}