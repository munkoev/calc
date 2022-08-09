/// \file
#ifndef SRC_SMART_CALC_H_
#define SRC_SMART_CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>

#define INPUT_SIZE 256

/* priority - 0:0-1, 1:2-3, 2:4-6, 3:7, 4:8-16, 5:17-21 */
typedef enum {
    l_number    =  0,    l_pow       =  7,    l_sqrt      = 14,
    l_x         =  1,    l_cos       =  8,    l_ln        = 15,
    l_plus      =  2,    l_sin       =  9,    l_log_10    = 16,
    l_minus     =  3,    l_tan       = 10,    l_par_left  = 17,
    l_mul       =  4,    l_acos      = 11,    l_par_right = 18,
    l_div       =  5,    l_asin      = 12,    incorrect = 19,
    l_mod       =  6,    l_atan      = 13,
} lexem_type;

typedef struct lexem lexem;
typedef struct state state;
typedef struct stack stack;
struct lexem {
    double value;
    int prio;
    lexem_type type;
};

struct stack {
    int top;
    unsigned int capacity;
    lexem* array;
};

struct state {
    int par_opened;
    int dot_placed;
    int printing_number;
    int printing_x;
    char prev;
    int error;
};

int validate(char* input);
void shift_arr(char* str, ssize_t arrsize, int shift, int from);
void remove_unary(char* input);
void remove_spaces(char* input);
void str_replace(char* input, const char* toreplace, const char* replacement);
void shrink_func_names(char* input);

stack* stack_create(unsigned int capacity);
void stack_remove(stack* s);
int stack_is_full(stack* s);
int stack_is_empty(stack* s);
void stack_push(stack* s, lexem item);
lexem stack_pop(stack* s);
lexem stack_peek(stack* s);
void stack_print(stack* s);
void stack_print_str(stack* s);

stack* str_to_infix(char* input);
stack* infix_to_postfix(stack infix);
double calc_postfix(stack postfix, double x);
double calc_input(char* input, double x);

#endif  // SRC_SMART_CALC_H_
