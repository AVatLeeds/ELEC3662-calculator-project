#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H

enum op {PLUS = '+', MINUS = '-', MULTIPLY = 'x', DIVIDE = 0xFD, POWER = '^', ROOT = 0xE8};

int parser(char * source_text, double &result);

#endif