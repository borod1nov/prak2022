#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    struct data *p;
    struct node *next;
};

struct data
{
    double f;
    char *s[2];
};

struct node* copy_list(struct node* l1)
{
    struct node* l2 = (struct node*)malloc(sizeof(struct node));
    l2->p = (struct data*)malloc(sizeof(struct data));
    struct node* first = l2;
    while (l1->next != NULL)
    {
        l2->p->f = l1->p->f;
        strcpy(*(l2->p->s), *(l1->p->s));
        struct node* new = (struct node*)malloc(sizeof(struct node));
        new->p = (struct data*)malloc(sizeof(struct data));
        l2->next = new;
        l2 = new;
        l1 = l1->next;
    }
    l2->next = NULL;
    return first;
}