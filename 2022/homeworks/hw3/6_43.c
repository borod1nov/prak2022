#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 10

typedef struct
{
    int* data;
    int size;
    int top;
} stack;

stack* create()
{
    stack* a = (stack*)malloc(sizeof(stack));
    a->data = (int*)malloc(INIT_SIZE * sizeof(int));
    a->size = INIT_SIZE;
    a->top = -1;
    return a;
}

int push(stack* a, int elem)
{
    if (a->top >= a->size - 1)
    {
        a->size *= 2;
        a->data = (int*)realloc(a->data, a->size * sizeof(int));
    }
    a->top ++;
    a->data[a->top] = elem;
    return 0;
}

int pop(stack* a)
{
    if (a->top <= (a->size - 1) / 2)
    {
        a->size /= 2;
        a->data = (int*)realloc(a->data, a->size * sizeof(int));
    }
    int elem = a->data[a->top];
    a->data[a->top] = 0;
    a->top--;
    return elem;
}

int delete(stack* a)
{
    free(a->data);
    free(a);
    return 0;
}