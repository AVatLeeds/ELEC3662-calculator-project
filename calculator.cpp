#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <cmath>
#include "calculator.h"
#include "recursive_descent.h"

#define emax    1023
#define emin    -1022
#define bias    emax

Calculator::Calculator() : _LCD()
{
    _LCD.cursor_pos(0, 0);
}

void Calculator::buffer_insert(char character)
{
    if (computed) buffer_clear(), computed = false;
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

void Calculator::buffer_insert_text(const char * text)
{
    if (computed) buffer_clear(), computed = false;
    unsigned int length = 0;
    while (text[length ++]);
    if (_pos < _head)
    {
        for (uint16_t i = _head + length - 1; i > _pos; _expression_buffer[i] = _expression_buffer[i - length], i --); 
    }
    length = 0;
    while (text[length])
    {
        _expression_buffer[_pos ++] = text[length ++];
    }
    _head += length;
    if (_pos == (_window_start + _window_length)) _window_start += length;
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::buffer_backspace()
{
    computed = false;
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
    computed = false;
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
    computed = false;
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
    clear_result();
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

void Calculator::toggle_sign()
{
    uint16_t save_pos;

    save_pos = _pos;

    while ((isdigit(_expression_buffer[_pos]) || _pos == _head) && _pos)
    {
        cursor_left();
    }

    if (_pos == 0)
    {
        if (_expression_buffer[_pos] == '-')
        {
            cursor_right();
            buffer_backspace();
            if (save_pos) save_pos --;
        }
        else
        {
            buffer_insert('-');
            save_pos ++;
        }
    }
    else if (_expression_buffer[_pos] == '-' && !isdigit(_expression_buffer[_pos - 1]))
    {
        cursor_right();
        buffer_backspace();
        if (save_pos - _pos) save_pos --;
    }
    else if (_pos != save_pos)
    {
        cursor_right();
        buffer_insert('-');
        save_pos ++;
    }

    _pos = save_pos;
    _LCD.cursor_pos(0, _pos);
}

void Calculator::evaluate()
{
    clear_result();
    if (parser(_expression_buffer, _result)) display_result();
    else _LCD.print("Bad expression");
    computed = true;
    _pos = _head;
}

void Calculator::clear_result()
{
    _LCD.cursor_pos(1, 0);
    _LCD.print("                "); // a hack to clear the row. REPLACE!!
    _LCD.cursor_pos(1, 0);
}

void Calculator::display_result()
{
    uint64_t double_bits = *reinterpret_cast<uint64_t *>(&_result);

    uint8_t S = (double_bits & 0x8000000000000000) ? 1 : 0;
    uint16_t E = (uint16_t)((double_bits & 0x7FF0000000000000UL) >> 52);
    uint64_t T = double_bits & 0x000FFFFFFFFFFFFFUL;

    if (_result < 0) _result *= -1;

    int exponent;
    double mantissa = frexp(_result, &exponent);

    double normalised_decimal_exponent;
    int decimal_exponent;
    double decimal_value;

    char number_text[16];
    uint8_t text_idx = 0;

    if (exponent == 0x7FF)
    {
        if (T)
        {
            _LCD.print("NaN");
        }
        else
        {
            if (S)
            {
                _LCD.print("-Inf");
            }
            else
            {
                _LCD.print("+Inf");
            }
        }
    }
    else if (!E && !T)
    {
        if (S)
        {
            _LCD.print("-0.0");
        }
        else
        {
            _LCD.print("+0.0");
        }
    }
    else
    {
        normalised_decimal_exponent = std::log10(mantissa) + (double)exponent * std::log10(2.0);
        decimal_exponent = (int)normalised_decimal_exponent;
        decimal_value = pow(10, normalised_decimal_exponent - (double)decimal_exponent);
        
        int integer = (int)round((decimal_value * 10000000));

        _LCD.putchar(S ? '-' : '+');
        text_idx = 9;
        number_text[text_idx --] = '\0';
        while (text_idx > 1)
        {
            number_text[text_idx --] = '0' + (integer % 10);
            integer /= 10;
        }
        number_text[text_idx --] = '.';
        number_text[text_idx] = '0' + (integer % 10);
        _LCD.print(number_text);
        _LCD.putchar(' ');
        _LCD.putchar('E');
        _LCD.putchar((decimal_exponent < 0) ? '-' : '+');
        decimal_exponent *= (decimal_exponent < 0) ? -1 : 1;
        
        text_idx = 3;
        number_text[text_idx --] = '\0';
        while (text_idx > 0)
        {
            number_text[text_idx --] = '0' + (decimal_exponent % 10);
            decimal_exponent /= 10;
        }
        number_text[text_idx] = '0' + (decimal_exponent % 10);
        _LCD.print(number_text);
    }
}