#include <cstdlib>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <cctype>
#include "recursive_descent.h"

# define M_PI		3.14159265358979323846
# define M_E		2.7182818284590452354

enum error state;
double last_result;

int parse_number(char * &source_text, double &result);
int parse_factor(char * &source_text, double &result);
int parse_term(char * &source_text, double &result);
int parse_expression(char * &source_text, double &result);

int parse_number(char * &source_text, double &result)
{
    int8_t sign = 1;
    int8_t exponent_sign = 1;
    double fractional_part = 0;
    double exponent = 0;
    char * marker;

    result = 0.0;

    switch(*source_text)
    {
        case '+': sign = 1; source_text ++; break;
        case '-': sign = -1; source_text ++; break;
    }

    if (isdigit(*source_text) || *source_text == '.')
    {
        while (isdigit(*source_text)) result = result * 10 + (*source_text ++ - '0');

        if (*source_text == '.')
        {
            marker = ++ source_text;

            if (isdigit(*source_text))
            {
                while (isdigit(*source_text)) fractional_part = fractional_part * 10 + (*source_text ++ - '0');
                result += fractional_part / pow(10.0, (source_text - marker));

                if (*source_text == 'E')
                {
                    source_text ++;

                    switch(*source_text)
                    {
                        case '+': exponent_sign = 1; source_text ++; break;
                        case '-': exponent_sign = -1; source_text ++; break;
                    }
                    if (isdigit(*source_text))
                    {
                        while (isdigit(*source_text)) exponent = exponent * 10 + (*source_text ++ - '0');
                        exponent *= exponent_sign;
                        if (exponent <= 308 && exponent >= -323) result *= pow(10, exponent) * sign;
                        else return state = E_ERR;
                        return state = SUCCESS;
                    }
                }
                else
                {
                    result *= sign;
                    return SUCCESS;
                }
            }
        }
        else if (*source_text == 'E')
        {
            source_text ++;
        
            switch(*source_text)
            {
                case '+': exponent_sign = 1; source_text ++; break;
                case '-': exponent_sign = -1; source_text ++; break;
            }
            if (isdigit(*source_text))
            {
                while (isdigit(*source_text)) exponent = exponent * 10 + (*source_text ++ - '0');
                exponent *= exponent_sign;
                if (exponent <= 308 && exponent >= -323) result *= pow(10, exponent) * sign;
                else return state = E_ERR;
                return SUCCESS;
            }
        }
        else
        {
            result *= sign;
            return SUCCESS;
        }
    }

    return state = MAL_NUM;
}

int parse_factor(char * &source_text, double &result)
{
    int8_t sign = 1;
    if (*source_text == MINUS)
    {
        source_text ++;
        sign = -1;
    }
    if (*source_text == '\xF7') // Pi character code on LCD
    {
        result = M_PI * sign;
        source_text ++;
        return SUCCESS;
    }
    else if (*source_text == 'e')
    {
        result = M_E * sign;
        source_text ++;
        return SUCCESS;
    }
    else if (sign == -1)
    {
        source_text --;
    }

    if (!parse_number(source_text, result))
    {
        return SUCCESS;
    }
    else if (*source_text == '(')
    {
        source_text ++;
        if (!parse_expression(source_text, result))
        {
            if (*source_text == ')')
            {
                source_text ++;
                return SUCCESS;
            }
        }
    }
    else if (!strncmp(source_text, "ANS", 3))
    {
        result = last_result;
        source_text += 3;
        return SUCCESS;
    }
    
    if (state) return state;
    return state = MAL_EXPR;
}

int parse_special(char * &source_text, double &result)
{
    double temp;
    int8_t sign = 1;

    if (*source_text == MINUS)
    {
        source_text ++;
        sign = -1;
    }
    if (!strncmp(source_text, "sin", 3))
    {
        source_text += 3;
        if (!parse_factor(source_text, temp))
        {
            result = sin(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "cos", 3))
    {
        source_text += 3;
        if (!parse_factor(source_text, temp))
        {
            result = cos(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "tan", 3))
    {
        source_text += 3;
        if (!parse_factor(source_text, temp))
        {
            result = tan(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "asin", 3))
    {
        source_text += 4;
        if (!parse_factor(source_text, temp))
        {
            if (temp < -1 || temp > 1) return state = TRIG_ERR;
            result = asin(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "acos", 3))
    {
        source_text += 4;
        if (!parse_factor(source_text, temp))
        {
            if (temp < -1 || temp > 1) return state = TRIG_ERR;
            result = acos(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "atan", 3))
    {
        source_text += 4;
        if (!parse_factor(source_text, temp))
        {
            if (temp < -1 || temp > 1) return state = TRIG_ERR;
            result = atan(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "deg", 3))
    {
        source_text += 3;
        if (!parse_factor(source_text, temp))
        {
            result = temp * (180 / M_PI) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "rad", 3))
    {
        source_text += 3;
        if (!parse_factor(source_text, temp))
        {
            result = temp * (M_PI / 180) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "ln", 2))
    {
        source_text += 2;
        if (!parse_factor(source_text, temp))
        {
            if (temp <= 0) return state = LOG_ERR;
            result = log(temp) * sign;
            return SUCCESS;
        }
    }
    else if (!strncmp(source_text, "log10", 5))
    {
        source_text += 5;
        if (!parse_factor(source_text, temp))
        {
            if (temp <= 0) return state = LOG_ERR;
            result = log10(temp) * sign;
            return SUCCESS;
        }
    }
    else if (sign == -1)
    {
        source_text --;
    }

    if (!parse_factor(source_text, result)) return SUCCESS;

    if (state) return state;
    return state = MAL_EXPR;
}

int parse_power(char * &source_text, double &result)
{
    double temp;
    int8_t sign = 1;

    if (*source_text == MINUS)
    {
        source_text ++;
        sign = -1;
    }
    if (*source_text == (char)ROOT)
    {
        source_text ++;
        if (!parse_special(source_text, result))
        {
            if (result < 0) return state = SQRT_ERR;
            result = sqrt(result) * sign;
            return SUCCESS;
        }
        else if (state) return state;
        return state = MAL_EXPR;
    }
    else if (sign == -1)
    {
        source_text --;
    }

    if (!parse_special(source_text, result))
    {
        while (*source_text == POWER)
        {
            source_text ++;
            if (!parse_special(source_text, temp))
            {
                if (result == 0 && temp < 0) result = 1.0 / pow(result, temp * -1.0);
                else if (result < 0 && (temp < 1 && temp > -1)) return state = POW_ERR;
                else result = pow(result, temp);
            }
            else
            {
                if (state) return state;
                return state = MAL_EXPR;
            }
        }
        return SUCCESS;
    }

    if (state) return state;
    return state = MAL_EXPR;
}

int parse_term(char * &source_text, double &result)
{
    double temp;
    if (!parse_power(source_text, result))
    {
        while (*source_text == MULTIPLY || *source_text == (char)DIVIDE)
        {
            switch (*source_text)
            {
                case MULTIPLY:
                source_text ++;
                if (!parse_power(source_text, temp)) result *= temp;
                else if (state) return state;
                else return state = MAL_EXPR;
                break;

                case DIVIDE:
                source_text ++;
                if (!parse_power(source_text, temp)) result /= temp;
                else if (state) return state;
                else return state = MAL_EXPR;
                break;
            }
        }
        return SUCCESS;
    }

    if (state) return state;
    return state = MAL_EXPR;
}

int parse_expression(char * &source_text, double &result)
{
    double temp;
    if (!parse_term(source_text, result))
    {
        while (*source_text == PLUS || *source_text == MINUS)
        {
            switch (*source_text)
            {
                case PLUS:
                source_text ++;
                if (!parse_term(source_text, temp)) result += temp;
                else if (state) return state;
                else return state = MAL_EXPR;
                break;

                case MINUS:
                source_text ++;
                if (!parse_term(source_text, temp)) result -= temp;
                else if (state) return state;
                else return state = MAL_EXPR;
                break;
            }
        }
        return SUCCESS;
    }
    
    if (state) return state;
    return state = MAL_EXPR;
}

enum error parser(char * source_text, double &result)
{
    last_result = result;
    if (*source_text == '\0') return EXPR_EMPTY;
    else if (!parse_expression(source_text, result))
    {
        if (*source_text == '\0') return SUCCESS;
    }
    return state;
}