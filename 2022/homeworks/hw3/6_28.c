#include <stddef.h>
#include <stdlib.h>

struct node
{
    double* data;
    struct node* next;
};

int swap_first_and_last(struct node* list)
{
    struct node* first = list;
    while (list->next != NULL)
        list = list->next;
    double* swap = first->data;
    first->data = list->data;
    list->data = swap;
    return 0;
}

int delete(struct node* list, double* elem)
{
    struct node* prev;
    while ((list->next != NULL) && (list->data != elem))
    {
        prev = list;
        list = list->next;
    }
    prev->next = list->next;
    list->next = NULL;
    return 0;
}

int delete_all(struct node* list, double* elem)
{
    struct node* prev;
    while (list->next != NULL)
    {
        while (list->data != elem)
        {
            prev = list;
            list = list->next;
        }
        prev->next = list->next;
        list = prev;
    }
    return 0;
}

int add_the_same(struct node* list, double* elem)
{
    while (list->next != NULL)
    {
        struct node* new = (struct node*)malloc(sizeof(struct node));
        while (list->data != elem)
        {
            list = list->next;
        }
        new->next = list->next;
        new->data = list->data;
        list->next = new->next;
        list = new;
    }
    return 0;
}

