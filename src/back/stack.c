/// \file
#include "./smart_calc.h"

/**
 * @brief function to create a stack of given capacity.
 * It initializes size of stack as 0.
 * memory is allocated, so stack needs to be removed (freed)
 * @param capacity <=256 for current project 
 * @return pointer to created stack. in case of error exit(1)
 */
stack* stack_create(unsigned int capacity) {
    stack* s;
    if (NULL != (s = (stack*)malloc(sizeof(stack)))) {
        s->capacity = capacity;
        s->top = -1;
        if (NULL == (s->array = (lexem*)malloc(s->capacity * sizeof(lexem)))) exit(1);
    } else {
        exit(1);
    }
    return s;
}

/**
 * @brief remove stack if it exists, free memory
 * 
 * @param s pointer to stack to be removed
 */
void stack_remove(stack* s) {
    if (s) {
        free(s->array);
        free(s);
    }
}

/**
 * @brief Stack is full when top is equal to the last index
 * 
 * @param s pointer to stack
 * @return int 0 - not full, 1 - full
 */
int stack_is_full(stack* s) {
    return (unsigned int)s->top == s->capacity - 1;
}

/**
 * @brief Stack is empty when top is equal to -1
 * 
 * @param s pointer to stack
 * @return int 0 - empty, 1 - not empty
 */
int stack_is_empty(stack* s) {
    return s->top == -1;
}

/**
 * @brief Function to add an item to stack.  It increases top by 1
 * if stack is full nothing happens
 * @param s pointer to stack
 * @param item lexem to push
 */
void stack_push(stack* s, lexem item) {
    if (!stack_is_full(s)) s->array[++s->top] = item;
}

/**
 * @brief Function to remove an item from stack.  It decreases top by 1
 * returns lexem with type 19 if stack is empty already
 * @param s pointer to stack
 * @return popped lexem 
 */
lexem stack_pop(stack* s) {
    lexem a = {0};
    a.type = 19;
    return stack_is_empty(s) ? a : s->array[s->top--];
}

/**
 * @brief Function to return the top from stack without removing it
 * returns lexem with type 19 if stack is empty
 * @param s pointer to stack
 * @return peeked lexem 
 */
lexem stack_peek(stack* s) {
    lexem a = {0};
    a.type = 19;
    return stack_is_empty(s) ? a :s->array[s->top];
}

/* for debugging
void stack_print(stack* s) {
    printf("capacity %u, top %d, array:\n", s->capacity, s->top);
    for (int i = 0; i < s-> top + 1; i++) {
        printf("val %lf, prio %d, type %d\n", s->array[i].value,
                                            s->array[i].prio,
                                            s->array[i].type);
    }
}

void stack_print_str(stack* s) {
    for (int i = 0; i < s-> top + 1; i++) {
        switch (s->array[i].type) {
        case 0:
            printf("%.2f", s->array[i].value);
            break;
        case 1:
            printf("x");
            break;
        case 2:
            printf("+");
            break;
        case 3:
            printf("-");
            break;
        case 4:
            printf("*");
            break;
        case 5:
            printf("/");
            break;
        case 6:
            printf("mod");
            break;
        case 7:
            printf("^");
            break;
        case 8:
            printf("cos");
            break;
        case 9:
            printf("sin");
            break;
        case 10:
            printf("tan");
            break;
        case 11:
            printf("acos");
            break;
        case 12:
            printf("asin");
            break;
        case 13:
            printf("atan");
            break;
        case 14:
            printf("sqrt");
            break;
        case 15:
            printf("ln");
            break;
        case 16:
            printf("log");
            break;
        case 17:
            printf("(");
            break;
        case 18:
            printf(")");
            break;
        default:
            break;
        }
        printf(" ");
    }
    printf("\n");
}
*/
