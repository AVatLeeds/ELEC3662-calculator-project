#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H

enum op {PLUS = '+', MINUS = '-', MULTIPLY = 'x', DIVIDE = 0xFD, POWER = '^', ROOT = 0xE8};

enum error {SUCCESS, EXPR_EMPTY, MAL_EXPR, MAL_NUM, TRIG_ERR, LOG_ERR, POW_ERR, SQRT_ERR, E_ERR};

enum error parser(char * source_text, double &result);

#endif