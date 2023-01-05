#include <cstdlib>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <cctype>
#include "recursive_descent.h"

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
    uint32_t exponent = 0;
    char * marker;

    result = 0.0;

    switch(*source_text)
    {
        case '+': sign = 1; source_text ++; break;
        case '-': sign = -1; source_text ++; break;
    }

    if (isdigit(*source_text))
    {
        while (isdigit(*source_text)) result = result * 10 + (*source_text ++ - '0');
    }

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
                    result *= pow(10, (double)exponent * exponent_sign) * sign;
                    return 1;
                }
            }
            else
            {
                result *= sign;
                return 1;
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
            result *= pow(10, (double)exponent * exponent_sign) * sign;
            return 1;
        }
    }
    else
    {
        result *= sign;
        return 1;
    }

    return 0;
}

int parse_factor(char * &source_text, double &result)
{
    if (parse_number(source_text, result)) return 1;
    else if (*source_text == '(')
    {
        source_text ++;
        if (parse_expression(source_text, result))
        {
            if (*source_text == ')')
            {
                source_text ++;
                return 1;
            }
        }
    }
    else if (!strncmp(source_text, "ANS", 3))
    {
        result = last_result;
        source_text += 3;
        return 1;
    }
    return 0;
}

int parse_power(char * &source_text, double &result)
{
    double temp;
    if (*source_text == (char)ROOT) // square root character
    {
        source_text ++;
        if (parse_factor(source_text, result))
        {
            result = sqrt(result);
            return 1;
        }
        else return 0;
    }
    else if (parse_factor(source_text, result))
    {
        while (*source_text == POWER)
        {
            source_text ++;
            if (parse_special(source_text, temp)) result = pow(result, temp);
            else return 0;
        }
        return 1;
    }
    return 0;
}

int parse_term(char * &source_text, double &result)
{
    double temp;
    if (parse_power(source_text, result))
    {
        while (*source_text == MULTIPLY || *source_text == (char)DIVIDE)
        {
            switch (*source_text)
            {
                case MULTIPLY:
                source_text ++;
                if (parse_power(source_text, temp)) result *= temp;
                else return 0;
                break;

                case DIVIDE:
                source_text ++;
                if (parse_power(source_text, temp)) result /= temp;
                else return 0;
                break;
            }
        }
        return 1;
    }
    return 0;
}

int parse_expression(char * &source_text, double &result)
{
    double temp;
    if (parse_term(source_text, result))
    {
        while (*source_text == PLUS || *source_text == MINUS)
        {
            switch (*source_text)
            {
                case PLUS:
                source_text ++;
                if (parse_term(source_text, temp)) result += temp;
                else return 0;
                break;

                case MINUS:
                source_text ++;
                if (parse_term(source_text, temp)) result -= temp;
                else return 0;
                break;
            }
        }
        return 1;
    }
    return 0;
}

int parser(char * source_text, double &result)
{
    last_result = result;
    if (parse_expression(source_text, result))
    {
        if (*source_text == '\0') return 1;
    }
    return 0;
}