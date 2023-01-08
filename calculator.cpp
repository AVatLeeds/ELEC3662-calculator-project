#include <cstring>
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

void Calculator::buffer_insert(char character, enum type type)
{
    if (_computed)
    {
        _computed = false;
        _hist_back = false;
        buffer_clear();
    }

    if (_buffer_mask[_pos] == TEXT && (_buffer_mask[_pos - 1] == TEXT && _expression_buffer[_pos - 1] != '(')) return;

    if (_pos < _head)
    {
        for (uint16_t i = _head; i > _pos; i --)
        {
            _buffer_mask[i] = _buffer_mask[i - 1];
            _expression_buffer[i] = _expression_buffer[i - 1];
        }
    }
    _buffer_mask[_pos] = type;
    _expression_buffer[_pos++] = character;
    _head ++;
    _window_start += 1 & (_pos == (_window_start + _window_length));
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::buffer_insert_digit(uint8_t digit)
{
    digit %= 10;
    digit += '0';
    buffer_insert(digit, DIGIT);
}

void Calculator::buffer_insert_operator(enum op op)
{
    if (_computed)
    {
        _computed = false;
        buffer_clear();
    }

    switch (op)
    {
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
        case POWER: 
        if (_pos == 0) buffer_insert_text("ANS");
        break;

        default: break;
    }

    buffer_insert(op, OPERATOR);
}

void Calculator::buffer_insert_exponent()
{
    buffer_insert('E', EXPONENT);
}

void Calculator::buffer_insert_decimal_point()
{
    buffer_insert('.', DECIMAL_POINT);
}

void Calculator::buffer_insert_open_bracket()
{
    buffer_insert('(', OPEN_BRACKET);
}

void Calculator::buffer_insert_close_bracket()
{
    buffer_insert(')', CLOSE_BRACKET);
}

void Calculator::buffer_insert_pi()
{
    buffer_insert('\xF7', DIGIT); // code for Pi character on LCD
}

void Calculator::buffer_insert_e()
{
    buffer_insert('e', DIGIT);
}

void Calculator::buffer_insert_text(const char * text)
{
    if (_computed)
    {
        _computed = false;
        _hist_back = false;
        buffer_clear();
    }

    if (_buffer_mask[_pos] == TEXT && (_buffer_mask[_pos - 1] == TEXT && _expression_buffer[_pos - 1] != '(')) return;

    unsigned int length = 0;
    while (text[length]) length ++;
    if (_pos < _head)
    {
        for (uint16_t i = _head + length - 1; i > _pos; i --)
        {
            _buffer_mask[i] = _buffer_mask[i - length];
            _expression_buffer[i] = _expression_buffer[i - length]; 
        }
    }
    length = 0;
    while (text[length])
    {
        _buffer_mask[_pos] = TEXT;
        _expression_buffer[_pos ++] = text[length ++];
    }
    _buffer_mask[_pos] = DEFAULT;
    _head += length;
    if (_pos >= (_window_start + _window_length)) _window_start += length;
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::buffer_backspace()
{
    _computed = false;
    uint8_t length = 0;

    if (_pos)
    {
        if (_buffer_mask[_pos - 1] != TEXT)
        {
            _pos --;
            if (_pos < _head)
            {
                for (uint16_t i = _pos; i < _head; i ++)
                {
                    _buffer_mask[i] = _buffer_mask[i + 1];
                    _expression_buffer[i] = _expression_buffer[i + 1];
                }
            }
            _head --;
        }
        else
        {
            _pos --;
            while (_buffer_mask[_pos] == TEXT)
            {
                if (_expression_buffer[_pos] == '(')
                {
                    length ++;
                    break;
                }
                _pos ++;
            }
            while (_buffer_mask[-- _pos] == TEXT)
            {
                if (_expression_buffer[_pos] == '(') break;
                length ++;
                if (_pos == 0) break;
            }

            for (uint16_t i = (_pos) ? ++ _pos : _pos; i < (_head - length); i ++)
            {
                _buffer_mask[i] = _buffer_mask[i + length];
                _expression_buffer[i] = _expression_buffer[i + length];
            }
            _head -= length;
        }

        if (_pos < (_window_start + (_window_length - _view_threshold)) && _window_start)
        {
            _window_start --;
        }
    }
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
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
    _computed = false;
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
    _computed = false;
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

void Calculator::cursor_home()
{
    _pos = 0;
    _window_start = 0;
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::cursor_end()
{
    _pos = _head;
    _window_start = (_pos >= _window_length) ? _pos - (_window_length - 1) : 0;
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::history_back()
{
    _window_start = 0;
    _head = 0;

    _hist_back = true;
    if (_computed) _hist_idx = _hist_head;

    if (!_hist_overflow || _hist_head == (HISTORY_LENGTH - 1))
    {
        _hist_idx = (_hist_idx > 0) ? _hist_idx - 1 : 0;
    }
    else
    {
        _hist_idx = (_hist_idx == 0) ? HISTORY_LENGTH - 1 : _hist_idx - ((_hist_idx == (_hist_head + 1)) ? 0 : 1); 
    }

    while ((_expression_buffer[_head] = _expression_history[_hist_idx][_head])) _head ++;

    if (_head > _window_length) _window_start = _head - (_window_length - 1);
    buffer_redisplay();
    _pos = _head;
    _LCD.cursor_pos(0, _pos - _window_start);
    _computed = false;
}

void Calculator::history_forward()
{
    if (_hist_back)
    {
        _window_start = 0;
        _head = 0;
        
        if (!_hist_overflow)
        {
            _hist_idx = (_hist_idx < _hist_head) ? _hist_idx + 1 : _hist_head;
        }
        else
        {
            _hist_idx = (_hist_idx == (HISTORY_LENGTH - 1)) ? 0 : _hist_idx + ((_hist_idx == _hist_head) ? 0 : 1);
        }

        while ((_expression_buffer[_head] = _expression_history[_hist_idx][_head])) _head ++;

        if (_head > _window_length) _window_start = _head - (_window_length - 1);
        buffer_redisplay();
        _pos = _head;
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
    uint8_t saved_pos = _pos;
    uint8_t saved_win_start = _window_start;

    if (_computed)
    {
        _computed = false;
        _hist_back = false;
        _pos = 0;
        saved_pos = 0;
        buffer_clear();
    }

    if (_pos == 0)
    {
        AT_BEGINNING:
        switch (_buffer_mask[_pos])
        {
            case DIGIT:
            case TEXT:
            case OPEN_BRACKET:
            buffer_insert('-', DEFAULT);
            saved_pos ++;
            break;

            case OPERATOR:
            if (_expression_buffer[_pos] == (char)ROOT)
            {
                buffer_insert('-', DEFAULT);
                saved_pos ++;
            }
            break;

            default:
            if (_expression_buffer[_pos] == '-')
            {
                _pos ++;
                buffer_backspace();
                if (saved_pos) saved_pos --;
            }
            else
            {
                buffer_insert('-', DEFAULT);
                saved_pos ++;
            }
        }
    }
    else if (_pos == _head)
    {
        _pos --;
        switch (_buffer_mask[_pos])
        {
            case DECIMAL_POINT:
            case CLOSE_BRACKET:
            break;

            case DIGIT:
            goto SEEK;
            break;

            case TEXT:
            if (_expression_buffer[_pos] != '(') goto SEEK;
            default:
            if (_expression_buffer[_pos] == '-' && _buffer_mask[_pos] != OPERATOR)
            {
                _pos ++;
                buffer_backspace();
                saved_pos --;
                break;
            }
            else
            {
                _pos ++;
                buffer_insert('-', DEFAULT);
                saved_pos ++;
            }
            break;
        }
    }
    else
    {
        switch (_buffer_mask[_pos])
        {
            case TEXT:
            case DIGIT:
            case DECIMAL_POINT:
            SEEK:
            if (_buffer_mask[_pos] == TEXT)
            {
                _pos --;
                while (_buffer_mask[_pos] == TEXT && _pos && _expression_buffer[_pos] != '(') _pos --;
            }
            else if (_buffer_mask[_pos] == DIGIT || _buffer_mask[_pos] == DECIMAL_POINT)
            {
                while ((_buffer_mask[_pos] == DIGIT || _buffer_mask[_pos] == DECIMAL_POINT) && _pos) _pos --;
            }

            if (_pos)
            {
                if (_expression_buffer[_pos] == '-' && _buffer_mask[_pos] != OPERATOR)
                {
                    _pos ++;
                    buffer_backspace();
                    if (saved_pos) saved_pos --;
                }
                else
                {
                    _pos ++;
                    buffer_insert('-', DEFAULT);
                    saved_pos ++;
                }
            }
            else
            {
                goto AT_BEGINNING;
            }
            break;

            case OPERATOR:
            if (_expression_buffer[_pos] != (char)ROOT) break;
            case OPEN_BRACKET:
            if (_expression_buffer[_pos - 1] == '-' && _buffer_mask[_pos - 1] != OPERATOR)
            {
                buffer_backspace();
                if (saved_pos) saved_pos --;
            }
            else
            {
                buffer_insert('-', DEFAULT);
                saved_pos ++;
            }
            break;

            default: break;
        }
    }

    _pos = saved_pos;
    _window_start = saved_win_start;
    if (_pos == (_window_start + _window_length)) _window_start ++;
    buffer_redisplay();
    _LCD.cursor_pos(0, _pos - _window_start);
}

void Calculator::evaluate()
{
    clear_result();

    _expression_buffer[_head] = '\0';
    switch (parser(_expression_buffer, _result))
    {
        case SUCCESS:       display_result(); break;
        case EXPR_EMPTY:    _LCD.print("Err: Empty      "); break;
        case MAL_EXPR:      _LCD.print("Err: Expression "); break;
        case MAL_NUM:       _LCD.print("Err: Number     "); break;
        case TRIG_ERR:      _LCD.print("Err: trig       "); break;
        case LOG_ERR:       _LCD.print("Err: Logarithm  "); break;
        case POW_ERR:       _LCD.print("Err: Power      "); break;
        case SQRT_ERR:      _LCD.print("Err: Square root"); break;
        case E_ERR:         _LCD.print("Err: Exponent   "); break;
    }
    _pos = _head;
    _computed = true;
    _hist_back = false;

    if (strcmp(_expression_buffer, _expression_history[_hist_idx]))
    {
        uint8_t i = 0;
        _hist_idx = _hist_head;
        while ((_expression_history[_hist_idx][i] = _expression_buffer[i])) i ++;
        _hist_head = (_hist_head == (HISTORY_LENGTH - 1)) ? _hist_overflow = true, 0 : _hist_head + 1;
        _expression_history[_hist_head][0] = '\0';
    }
}

void Calculator::clear_result()
{
    _LCD.cursor_pos(1, 0);
    _LCD.print("                "); // a hack to clear the row. REPLACE!!
    _LCD.cursor_pos(1, 0);
}

void Calculator::display_result()
{
    double display_value = _result;
    uint64_t double_bits = *reinterpret_cast<uint64_t *>(&display_value);

    uint8_t S = (double_bits & 0x8000000000000000) ? 1 : 0;
    uint16_t E = (uint16_t)((double_bits & 0x7FF0000000000000UL) >> 52);
    uint64_t T = double_bits & 0x000FFFFFFFFFFFFFUL;

    if (display_value < 0) display_value *= -1;

    int exponent;
    double mantissa = frexp(display_value, &exponent);

    double normalised_decimal_exponent;
    int decimal_exponent;
    double decimal_value;

    char number_text[16];
    uint8_t text_idx = 0;

    if (E == 0x7FF)
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
        uint8_t number_length = 8;
        uint8_t fraction_digits = number_length - 1;
        normalised_decimal_exponent = std::log10(mantissa) + (double)exponent * std::log10(2.0);
        decimal_exponent = (int)normalised_decimal_exponent;
        decimal_value = pow(10, normalised_decimal_exponent - (double)decimal_exponent);
        if (decimal_exponent > 0 && decimal_exponent < 7)
        {
            fraction_digits = number_length - decimal_exponent - 1;
            decimal_exponent = 0;
        }
        int integer = (int)round((decimal_value * pow(10, number_length - 1)));

        _LCD.putchar(S ? MINUS : PLUS);
        text_idx = number_length + 1;
        number_text[text_idx --] = '\0';
        while (fraction_digits --)
        {
            number_text[text_idx --] = '0' + (integer % 10);
            integer /= 10;
        }
        number_text[text_idx --] = '.';
        while (text_idx)
        {
            number_text[text_idx --] = '0' + (integer % 10);
            integer /= 10;
        }
        number_text[text_idx --] = '0' + (integer % 10);
        _LCD.print(number_text);
        _LCD.putchar(' ');
        _LCD.putchar('E');
        _LCD.putchar((decimal_exponent < 0) ? MINUS : PLUS);
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