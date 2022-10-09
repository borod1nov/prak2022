#include <stddef.h>
#include <stdlib.h>

struct node
{
    char* data;
    struct node* next;
};

struct node* merge(struct node* l1, struct node* l2)
{
    struct node* l3 = (struct node*)malloc(sizeof(struct node));
    struct node* first1 = l1;
    struct node* first2 = l2;
    struct node* first3 = l3;
    while (l1->next != NULL)
    {
        int unique = 1;
        while (l2->next != NULL)
        {
            if (l1->data != l2->data)
                l2 = l2->next;
            else
            {
                unique = 0;
                break;
            }        
        }
        if (unique == 1)
        {
            struct node* new = (struct node*)malloc(sizeof(struct node));
            l3->data = l1->data;
            l3->next = new;
            l3 = l3->next;
        }
        l2 = first2;
        l1 = l1->next;
    }
    l1 = first1;
    l2 = first2;
    while (l2->next != NULL)
    {
        int unique = 1;
        while (l1->next != NULL)
        {
            if (l1->data != l2->data)
                l1 = l1->next;
            else
            {
                unique = 0;
                break;
            }        
        }
        if (unique == 1)
        {
            struct node* new = (struct node*)malloc(sizeof(struct node));
            l3->data = l2->data;
            l3->next = new;
            l3 = l3->next;
        }
        l1 = first1;
        l2 = l2->next;
    }
    return first3;
}