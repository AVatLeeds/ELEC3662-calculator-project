#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "recursive_descent.h"

double last_result;

int parse_number(char * &source_text, double &result);
int parse_factor(char * &source_text, double &result);
int parse_term(char * &source_text, double &result);
int parse_expression(char * &source_text, double &result);

int parse_number(char * &source_text, double &result)
{
    char * end = source_text;
    result = strtod(source_text, &end);
    if (source_text == end)
    {
        return 0;
    }
    source_text = end;
    return 1;
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
    else if (source_text[0] == 'A' && source_text[1] == 'N' && source_text[2] == 'S')
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
            if (parse_factor(source_text, temp)) result = pow(result, temp);
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