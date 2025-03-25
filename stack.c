#include "stack.h"
#include <stdlib.h>

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

Bool stack_is_full(const Stack *s);
Status stack_grow(Stack *s);

struct _Stack
{
    void **item;  /*!<Static array of elements*/
    int top;      /*!<index of the top element in the stack*/
    int capacity; /*!<xcapacity of the stack*/
};

Stack *stack_init()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    int i;

    if (!s)
        return NULL;

    s->item = (void **)malloc(INIT_CAPACITY * sizeof(void *));

    if (!s->item)
        return NULL;

    s->capacity = INIT_CAPACITY;
    for (i = 0; i < s->capacity; i++)
        s->item[i] = NULL;

    s->top = -1;

    return s;
}

void stack_free(Stack *s)
{
    if (!s)
        return;

    free(s->item);

    free(s);
}

Status stack_push(Stack *s, const void *ele)
{
    if ((s == NULL) || (s == NULL))
        return ERROR;
    if (stack_is_full(s))
    {
        stack_grow(s);
    }
    s->top++;
    s->item[s->top] = (void *)ele;

    return OK;
}

Bool stack_isEmpty(const Stack *s)
{
    if (s == NULL || s->top == -1)
        return TRUE;

    return FALSE;
}

Bool stack_is_full(const Stack *s)
{
    if (s == NULL || s->top == s->capacity - 1)
        return TRUE;

    return FALSE;
}

Status stack_grow(Stack *s)
{
    int new_capacity;
    void **new_items;

    if (s == NULL)
        return ERROR;

    new_capacity = s->capacity * FCT_CAPACITY;

    new_items = (void **)realloc(s->item, new_capacity * sizeof(void *));
    if (new_items == NULL)
    {
        
        return ERROR;
    }

   
    s->item = new_items;
    s->capacity = new_capacity;

    return OK;
}

void *stack_pop(Stack *s)
{
    void *elem = NULL;

    elem = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;

    return elem;
}

void *stack_top(const Stack *s)
{

    return s->item[s->top];
}

size_t stack_size(const Stack *s)
{

    return s->top;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)
{
    int size = 0, i;

    printf("SIZE:%i", s->top);

    for (i = s->top; i < -1; i++)
        if (f(fp, s->item[i])){
            printf("\n");
            size++;
        }
            

    return size;
}