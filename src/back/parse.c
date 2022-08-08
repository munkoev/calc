/// \file
#include "./smart_calc.h"

/**
 * @brief main function for the project
 * it takes string and returns result
 * @param input string
 * @param x value of x from calculator
 * @return double. If input is invalid returns 0.
 */
double calc_input(char* input, double x) {
    double res = 0;
    if (!validate(input)) {
        stack* i = str_to_infix(input);
        stack* p = infix_to_postfix(*i);
        res = calc_postfix(*p, x);
        stack_remove(i);
        stack_remove(p);
    }
    return res;
}

/**
 * @brief calculates postfix stack and returns result
 * 
 * @param postfix correct postfix stack
 * @param x value of (double) x
 * @return (double) result of calculation. it can return nan, inf
 */
double calc_postfix(stack postfix, double x) {
    stack* s = stack_create(INPUT_SIZE);
    for (int i = 0; i <= postfix.top; i++) {
        if (postfix.array[i].type <= 1) {
            lexem tmp = {0};
            tmp.value = postfix.array[i].type ? x : postfix.array[i].value;
            stack_push(s, tmp);
        } else {
            lexem tmp = {0};
            double right = stack_pop(s).value;
            double left = 0;
            if (postfix.array[i].type < 8) {
                left = stack_pop(s).value;
            }
            switch (postfix.array[i].type) {
                case 2:
                    tmp.value = left + right;
                    break;
                case 3:
                    tmp.value = left - right;
                    break;
                case 4:
                    tmp.value = left * right;
                    break;
                case 5:
                    tmp.value = left / right;
                    break;
                case 6:
                    tmp.value = fmod(left, right);
                    break;
                case 7:
                    tmp.value = pow(left, right);
                    break;
                case 8:
                    tmp.value = cos(right);
                    break;
                case 9:
                    tmp.value = sin(right);
                    break;
                case 10:
                    tmp.value = tan(right);
                    break;
                case 11:
                    tmp.value = acos(right);
                    break;
                case 12:
                    tmp.value = asin(right);
                    break;
                case 13:
                    tmp.value = atan(right);
                    break;
                case 14:
                    tmp.value = sqrt(right);
                    break;
                case 15:
                    tmp.value = log(right);
                    break;
                case 16:
                    tmp.value = log10(right);
                    break;
                default:
                    break;
            }
            stack_push(s, tmp);
        }
    }
    double ret = s->array[0].value;
        stack_remove(s);
    return ret;
}

/**
 * @brief converts infix notation stack to postfix stack
 * 
 * @param infix correct stack with infix notation
 * @return pointer to postfix stack, it should be freed after use 
 */
stack* infix_to_postfix(stack infix) {
    stack* postfix = stack_create(INPUT_SIZE);
    stack* op_queue = stack_create(INPUT_SIZE);
    for (int i = 0; i < infix.top + 1; i++) {
        if (infix.array[i].type <= 1) {
            stack_push(postfix, infix.array[i]);

        } else if (infix.array[i].type >= 8 && infix.array[i].type <= 16) {
            stack_push(op_queue, infix.array[i]);

        } else if (infix.array[i].type <= 7) {
            lexem q_top = stack_peek(op_queue);
            while ( (q_top.type != 19 && q_top.type != 17) &&
                    ( (q_top.prio > infix.array[i].prio) ||
                    ((q_top.prio == infix.array[i].prio) && (infix.array[i].type != 7)) ) ) {
                lexem tmp = stack_pop(op_queue);
                stack_push(postfix, tmp);
                q_top = stack_peek(op_queue);
            }
            stack_push(op_queue, infix.array[i]);

        } else if (infix.array[i].type == 17) {
            stack_push(op_queue, infix.array[i]);

        } else if (infix.array[i].type == 18) {
            lexem q_top = stack_peek(op_queue);
            while (q_top.type != 17) {
                lexem tmp = stack_pop(op_queue);
                stack_push(postfix, tmp);
                q_top = stack_peek(op_queue);
            }
            stack_pop(op_queue);
            if (stack_peek(op_queue).type >= 8 && stack_peek(op_queue).type <= 16) {
                lexem tmp = stack_pop(op_queue);
                stack_push(postfix, tmp);
            }
        }
    }
    while (op_queue->top >= 0) {
        lexem tmp = stack_pop(op_queue);
        stack_push(postfix, tmp);
    }
        stack_remove(op_queue);

    return postfix;
}

/**
 * @brief converts string to stack filled with infix notation
 * input should be validated and normalised(see validate function)
 * @param input correct input string (i.e. it should be first validated and spaces removed)
 * @return pointer to created stack, it should be freed after use
 */
stack* str_to_infix(char* input) {
    stack* s = stack_create(INPUT_SIZE);
    for (int i = 0; i < (int)strlen(input); i++) {
        lexem l = {0};
        switch (input[i]) {
            case 'x':
                l.type = 1;
                l.prio = 0;
                break;
            case '+':
                l.type = 2;
                l.prio = 1;
                break;
            case '-':
                l.type = 3;
                l.prio = 1;
                break;
            case '*':
                l.type = 4;
                l.prio = 2;
                break;
            case '/':
                l.type = 5;
                l.prio = 2;
                break;
            case 'm':
                l.type = 6;
                l.prio = 2;
                break;
            case '^':
                l.type = 7;
                l.prio = 3;
                break;
            case 'c':
                l.type = 8;
                l.prio = 4;
                break;
            case 's':
                l.type = 9;
                l.prio = 4;
                break;
            case 't':
                l.type = 10;
                l.prio = 4;
                break;
            case 'C':
                l.type = 11;
                l.prio = 4;
                break;
            case 'S':
                l.type = 12;
                l.prio = 4;
                break;
            case 'T':
                l.type = 13;
                l.prio = 4;
                break;
            case 'q':
                l.type = 14;
                l.prio = 4;
                break;
            case 'n':
                l.type = 15;
                l.prio = 4;
                break;
            case 'g':
                l.type = 16;
                l.prio = 4;
                break;
            case '(':
                l.type = 17;
                l.prio = 5;
                break;
            case ')':
                l.type = 18;
                l.prio = 5;
                break;
            default:
                if ( ((input[i] >= '0') && (input[i] <= '9')) || input[i] == '.' ) {
                    l.type = 0;
                    l.prio = 0;
                    char val_str[INPUT_SIZE] = {0};
                    int j = 0;
                    for (; j < (int)strlen(input) - i; j++) {
                        if ( ((input[i+j] >= '0') && (input[i+j] <= '9')) || input[i+j] == '.' ) {
                            char tmp_str[2] = "\0";
                            tmp_str[0] = input[i+j];
                            snprintf(val_str + strlen(val_str), sizeof val_str, "%s", tmp_str);
                        } else {
                            break;
                        }
                    }
                    l.value = atof(val_str);
                    i += j - 1;
                }
                break;
        }
        stack_push(s, l);
    }
    return s;
}
