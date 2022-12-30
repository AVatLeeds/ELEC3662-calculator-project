#include <bits/types/struct_timespec.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define DIGIT       < 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 >
#define NUMBER      < [ - ] DIGIT { DIGIT } [ . DIGIT { DIGIT } ] [ E [ - ] DIGIT { DIGIT } ] >
#define FACTOR      ( # | '(' @ ')' )
#define TERM        FACTOR { ( * | / ) FACTOR }.
#define EXPRESSION  TERM { ( + | - ) TERM }.

#define STR(S)      #S
#define XSTR(S)     STR(S)



enum state {FAIL, CONTINUE, MATCHED};

float value_stack[32];
uint8_t value_stack_idx = 0;

void traverse_to_matching_bracket(char bracket_type, char ** source_text)
{
    char closing_bracket_type = ((bracket_type == 40) ? (bracket_type + 1) : (bracket_type + 2));
    uint8_t count = 0;
    while ((**source_text != closing_bracket_type) || count)
    {
        if (**source_text == bracket_type) count ++;
        if (**source_text == closing_bracket_type) count --;
        (*source_text) ++;
    }
}

void eval(char op, float value_1, float * value_2)
{
    switch (op)
    {
        case '+': *value_2 += value_1; break;
        case '-': *value_2 -= value_1; break;
        case '*': *value_2 *= value_1; break;
        case '/': *value_2 /= value_1; break;
    }
}


enum state parser(char * ruleset, char ** source_text_ptr, float * result)
{
    float accumulator = *result;
    float temp = 0;

    char op_stack[32]; // how big a stack is required?
    int op_stack_idx = 0;
    uint8_t op_count = 0;

    char * rule_start = ruleset;

    char * nesting_stack[256];
    uint8_t nesting_stack_idx = 0;

    uint32_t literal_length = 0;

    enum state state = CONTINUE;
    enum state state_was;

    uint32_t offset;

    uint8_t skip = 0;

    while (*ruleset)
    {
        switch (state)
        {
            case FAIL:
            switch (*ruleset)
            {
                case '|':
                state = CONTINUE;
                break;

                case ']':
                nesting_stack_idx --;
                state = state_was;
                break;

                case '}':
                nesting_stack_idx --;
                state = state_was;
                break;

                case ')':
                nesting_stack_idx --;
                break;

                case ' ': // skip over whitespace
                break;

                default:
                skip = 1;
                break;
            }
            break;

            case MATCHED:
            switch (*ruleset)
            {
                case '}':
                ruleset = nesting_stack[-- nesting_stack_idx];
                op_count ++;
                break;

                case '|':
                skip = 1;
                break;
            }
            case CONTINUE:
            switch (*ruleset)
            {
                case '[':
                case '{': state_was = state;
                case '(':
                nesting_stack[nesting_stack_idx ++] = ruleset;
                break;

                case '+':
                case '-':
                case '*':
                case '/':
                if (**source_text_ptr == *ruleset)
                {
                    op_stack[op_stack_idx ++] = **source_text_ptr;
                    (*source_text_ptr) ++;
                    state = MATCHED;
                }
                else
                {
                    state = FAIL;
                }
                break;

                case '\'':
                ruleset ++;
                while (*(ruleset + literal_length) != '\'') literal_length ++;
                if (strncmp(ruleset, *source_text_ptr, literal_length) == 0)
                {
                    state = MATCHED;
                    *source_text_ptr += literal_length;
                    ruleset += literal_length;
                }
                else
                {
                    state = FAIL;
                    ruleset += literal_length;
                }
                break;

                case '@':
                state = parser(rule_start, source_text_ptr, &value_stack[value_stack_idx ++]);
                break;

                case '#':
                if ((**source_text_ptr >= '0') && (**source_text_ptr <= '9'))
                {
                    value_stack[value_stack_idx ++] = (float)(**source_text_ptr - '0');
                    (*source_text_ptr) ++;
                    state = MATCHED;
                }
                else
                {
                    state = FAIL;
                }
                break;

                case '.':
                while (op_count)
                {
                    -- value_stack_idx;
                    eval(op_stack[-- op_stack_idx], value_stack[value_stack_idx], &value_stack[value_stack_idx - 1]);
                    op_count --;
                }
                break;
            }
            break;
        }

        printf("%s\n", rule_start);
        offset = ruleset - rule_start;
        while (offset --) printf(" ");
        printf("^\n");
        printf("%d\n", state);
        printf("%c\n", **source_text_ptr);
        printf("%f\n", value_stack[value_stack_idx - 1]);
        printf("%d\n", op_count);

        if (skip)
        {
            traverse_to_matching_bracket(*nesting_stack[-- nesting_stack_idx], &ruleset);
            skip = 0;
        }
        else
        {
            ruleset ++;
        }

        struct timespec req{0, 800000000};
        clock_nanosleep(CLOCK_MONOTONIC, 0, &req, NULL);
    }
    *result = value_stack[-- value_stack_idx];
    return state;
}

//char * source_text = "2+3";
//char * source_text = "2+(3*6-1)";
//char * source_text = "2+(3-6*4)";
char * source_text = "6/4*7+(8-9*2+3/6)-1";

float result;

int main()
{
    printf("%d\n", parser(XSTR(EXPRESSION), &source_text, &result));
}

/*switch (state)
        {
            case FAIL:
            switch (*ruleset ++)
            {
                case '|': state = NORM; break;
                case ')': bracket_matcher(*nesting_stack[index --], &ruleset);
                case ']': state = NORM; break;
                case '}': state = NORM; break;
                default: bracket_matcher(*nesting_stack[index --], &ruleset);
            }
            break;

            case NORM:
            switch (*ruleset ++)
            {
                case '(':
                case '[':
                case '{':
                nesting_stack[index ++] = ruleset;
                break;
            }
            break;

            case SUCCESS:
            switch (*ruleset++)
            {
                case '|': bracket_matcher(*nesting_stack[index --], &ruleset); break;
            }
            break;
        }*/

/*int parser(char * ruleset, char * source_text)
{
    // state variables
    uint8_t match;
    uint8_t fail;
    enum mode {NORMAL, ZERO_OR_MORE, ZERO_OR_ONE} mode;
    char * rule_start = ruleset;
    char * nesting_stack[256];
    uint8_t index = 0;
    int offset = 0;
    uint8_t must_match = 0;
    uint8_t dont_care = 0;
    uint8_t success_flag = 0;

    uint8_t failure = 0;
    uint8_t success = 0;
    uint8_t skip = 0;

    enum state {FAIL, NORM, NECESSARY, OPTIONAL, SUCCESS} state;

    while (*source_text && *ruleset)
    {
        printf("%s\n", rule_start);
        offset = ruleset - rule_start;
        while (offset --) printf(" ");
        printf("^\n");
        printf("%c\n", *source_text);

        //while (*ruleset == ' ') ruleset ++;
        if (skip)
        {
            switch (*ruleset ++)
            {
                case ' ': break;
                case '|': skip = 0; fail = 0; break;
                default: skip = 0; bracket_matcher(*nesting_stack[-- index], &ruleset); 
            }
        }
        else
        {
            switch (*ruleset ++)
            {
                case '(':
                case '[':
                case '{':
                nesting_stack[index ++] = ruleset - 1;
                break;

                case ')':
                index --;
                break;

                case ']':
                fail = 0;
                break;

                case '}': 
                fail = 0;
                if (success) ruleset = nesting_stack[-- index];
                break;

                case '|':
                if (success)
                {
                    bracket_matcher(*nesting_stack[-- index], &ruleset);
                }
                if (!success_flag) success_flag = 1;
                break;

                case '@':
                if (success) ruleset = rule_start;
                break;

                case '#':
                if ((*source_text > '0') && (*source_text < '9'))
                {
                    success = 1;
                    source_text ++;
                }
                else
                {
                    skip = 1;
                }
                break;

                case '\'':
                success = (*source_text == *ruleset ++) ? source_text ++, 1 : 0;
                if (!success) skip = 1;
                ruleset ++;
                break;

                //case '+': match = (*source_text == '+') ? source_text ++, 1 : 0; break;
                //case '-': match = (*source_text == '-') ? source_text ++, 1 : 0; break;
                //case '*': match = (*source_text == '*') ? source_text ++, 1 : 0; break;
                //case '/': match = (*source_text == '/') ? source_text ++, 1 : 0; break;

                //case 0 ... 9 : break;

                default: break;
            }
        }

        struct timespec req{1, 0};
        clock_nanosleep(CLOCK_MONOTONIC, 0, &req, NULL);
    }
    return match;
}*/