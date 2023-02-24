#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

word_list* create_list()
{
    word_list* list = (word_list*)malloc(sizeof(word_list));
    list->data = (char**)malloc(SIZE * sizeof(char*));
    list->top = -1;
    list->size = SIZE;
    return list;
}

int resize_list(word_list* list)
{
    list->size += SIZE;
    list->data = (char**)realloc(list->data, list->size * sizeof(char*));
    return 0;
}

int push_word(word_list* list, char* word)
{
    int len = strlen(word);
    char* word_copy = (char*)malloc((len + 1) * sizeof(char));
    strcpy(word_copy, word);
    if (list->top  + 1 >= list->size)
        resize_list(list);
    list->top++;
    list->data[list->top] = word_copy;
    return 0;
}

int sort_list(word_list* list)
{
    if (list->top < 0)
        return 1;
    for (int i = 0; i <= list->top; i++)
        for (int j = i + 1; j <= list->top; j++)
            if (strcmp(list->data[i], list->data[j]) > 0)
            {
                char* swap = list->data[i];
                list->data[i] = list->data[j];
                list->data[j] = swap;
            }
    return 0;
}

int print_list(word_list* list)
{
    if (list->top < 0)
        return 1;
    printf("%d\n", list->top + 1);
    for (int i = 0; i <= list->top; i++)
    {
        printf("%s\n", list->data[i]);
    }
    return 0;
}

int clear_list(word_list* list)
{
    for (int i = list->top + 1; i < list->size; i++)
        list->data[i] = NULL;
    for (int i = 0; i < list->size; i++)
        free(list->data[i]);
    for (int i = 0; i < list->size; i++)
        list->data[i] = NULL;
    list->data = (char**)realloc(list->data, SIZE * sizeof(char*));
    list->top = -1;
    list->size = SIZE;
}

int delete_list(word_list* list)
{
    for (int i = list->top + 1; i < list->size; i++)
        list->data[i] = NULL;
    for(int i = 0 ; i < list->size; i++)
        free(list->data[i]);
    free(list->data);
    free(list);
    return 0;
}