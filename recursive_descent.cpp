#include <stdint.h>
#include <stdlib.h>

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
    return 0;
}

int parse_term(char * &source_text, double &result)
{
    double temp;
    if (parse_factor(source_text, result))
    {
        while (*source_text == '*' || *source_text == '/')
        {
            switch (*source_text)
            {
                case '*':
                source_text ++;
                if (parse_factor(source_text, temp)) result *= temp;
                else return 0;
                break;

                case '/':
                source_text ++;
                if (parse_factor(source_text, temp)) result /= temp;
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
        while (*source_text == '+' || *source_text == '-')
        {
            switch (*source_text)
            {
                case '+':
                source_text ++;
                if (parse_term(source_text, temp)) result += temp;
                else return 0;
                break;

                case '-':
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