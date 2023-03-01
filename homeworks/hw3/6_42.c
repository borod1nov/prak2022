#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 10

typedef struct
{
    int* data;
    int bottom;
    int top;
    int size;
} queue;

queue* create()
{
    queue* a = (queue*)malloc(sizeof(queue));
    a->data = (int*)malloc(INIT_SIZE * sizeof(int));
    a->bottom = -1;
    a->top = -1;
    a->size = INIT_SIZE;
    return a;
}

int push(queue* a, int elem)
{
    if (a->top >= a->size - 1)
    {
        a->size *= 2;
        a->data = (int*)realloc(a->data, a->size * sizeof(int));
    }
    if (a->bottom == -1)
        a->bottom ++;
    a->top ++;
    a->data[a->top] = elem;
    return 0;
}

int pop(queue* a)
{
    int elem = a->data[a->bottom];
    a->data[a->bottom] = 0;
    a->bottom++;
    return elem;
}

int delete(queue* a)
{
    free(a->data);
    free(a);
    return 0;
}