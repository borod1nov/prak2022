#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

word* create_word()
{
    word* w = (word*)malloc(sizeof(word));
    w->symbols = (char*)malloc(SIZE * sizeof(char));
    w->top = -1;
    w->size = SIZE;
    return w;
}

int resize_word(word* w)
{
    w->size += SIZE;
    w->symbols = (char*)realloc(w->symbols, w->size * sizeof(char));
    return 0;
}

int push_sym(word* w, char c)
{
    if (w->top + 1 >= w->size)
        resize_word(w);
    w->top++;
    w->symbols[w->top] = c;
    return 0;
}

int delete_word(word* w)
{
    free(w->symbols);
    free(w);
    return 0;
}

int clear_word(word* w)
{
    for (int i = 0; i < w->size; i++)
        w->symbols[i] = '\0';
    w->symbols = (char*)realloc(w->symbols, SIZE * sizeof(char));
    w->top = -1;
    w->size = SIZE;
    return 0;
}
