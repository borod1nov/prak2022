#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 10

struct tnode
{
    int data;
    struct tnode *left;
    struct tnode *right;
};

typedef struct
{
    struct tnode* node_pointer;
    int node_level;
} node_info;

typedef struct
{
    node_info* data;
    int size;
    int top;
} stack;

stack* create()
{
    stack* a = (stack*)malloc(sizeof(stack));
    a->data = (node_info*)malloc(INIT_SIZE * sizeof(node_info));
    a->size = INIT_SIZE;
    a->top = -1;
    return a;
}

int push(stack* a, struct tnode* node_ptr, int level)
{
    if (a->top >= a->size - 1)
    {
        a->size *= 2;
        a->data = (node_info*)realloc(a->data, a->size * sizeof(node_info));
    }
    a->top ++;
    a->data[a->top].node_pointer = node_ptr;
    a->data[a->top].node_level = level;
    return 0;
}

node_info pop(stack* a)
{
    node_info node = a->data[a->top];
    a->data[a->top].node_level = 0;
    a->data[a->top].node_pointer = NULL;
    a->top--;
    return node;
}

int delete(stack* a)
{
    free(a->data);
    free(a);
    return 0;
}

int is_empty(stack* a)
{
    if (a->top < 0)
        return 1;
    return 0;
}

int count_nodes(struct tnode* tree, int n)
{
    if (tree == NULL)
        return 0;
    int count = 0;
    stack* nodes_stack = create();
    push(nodes_stack, tree, 1);
    while (!is_empty(nodes_stack))
    {
        node_info node = pop(nodes_stack);
        int level = node.node_level;
        if (level == n)
            count++;
        if (node.node_pointer->left != NULL)
            push(nodes_stack, node.node_pointer->left, level + 1);
        if (node.node_pointer->right != NULL)
            push(nodes_stack, node.node_pointer->right, level + 1);
    }
    delete(nodes_stack);
    return count;
}

void test0()
{
    int res = (count_nodes(NULL, 1) == 0);
    printf("test0:\n\n_\n\n%d/1 tests passed\n\n", res);
}

void test1()
{
    struct tnode c;
    c.left = NULL;
    c.right = NULL;
    int res = (count_nodes(&c, 1) == 1);
    printf("test1:\n\no\n\n%d/1 tests passed\n\n", res);
}

void test2()
{
    struct tnode c, cl;
    c.left = &cl;
    c.right = NULL;
    cl.left = NULL;
    cl.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 1);
    printf("test2:\n\n o\no _\n\n%d/2 tests passed\n\n", res1 + res2);
}

void test3()
{
    struct tnode c, cl, cr;
    c.left = &cl;
    c.right = &cr;
    cl.left = NULL;
    cl.right = NULL;
    cr.left = NULL;
    cr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    printf("test3:\n\n o\no o\n\n%d/2 tests passed\n\n", res1 + res2);
}

void test4()
{
    struct tnode c, cl, cr, clr;
    c.left = &cl;
    c.right = &cr;
    cl.left = NULL;
    cl.right = &clr;
    cr.left = NULL;
    cr.right = NULL;
    clr.left = NULL;
    clr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    int res3 = (count_nodes(&c, 3) == 1);
    printf("test4:\n\n   o\n o   o\n_ o _ _\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test5()
{
    struct tnode c, cl, cr, cll, crl;
    c.left = &cl;
    c.right = &cr;
    cl.left = &cll;
    cl.right = NULL;
    cr.left = &crl;
    cr.right = NULL;
    cll.left = NULL;
    cll.right = NULL;
    crl.left = NULL;
    crl.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    int res3 = (count_nodes(&c, 3) == 2);
    printf("test5:\n\n   o\n o   o\no _ o _\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test6()
{
    struct tnode c, cr, crr, crl;
    c.left = NULL;
    c.right = &cr;
    cr.left = &crl;
    cr.right = &crr;
    crl.left = NULL;
    crl.right = NULL;
    crr.left = NULL;
    crr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 1);
    int res3 = (count_nodes(&c, 3) == 2);
    printf("test6:\n\n   o\n _   o\n_ _ o o\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test7()
{
    struct tnode c, cl, cr, crr, crl, clr;
    c.left = &cl;;
    c.right = &cr;
    cl.left = NULL;
    cl.right = &clr;
    cr.left = &crl;
    cr.right = &crr;
    clr.left = NULL;
    clr.right = NULL;
    crl.left = NULL;
    crl.right = NULL;
    crr.left = NULL;
    crr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    int res3 = (count_nodes(&c, 3) == 3);
    printf("test7:\n\n   o\n o   o\n_ o o o\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test8()
{
    struct tnode c, cl, cr, cll, clr, crr, crl;
    c.left = &cl;
    c.right = &cr;
    cl.left = &cll;
    cl.right = &clr;
    cr.left = &crl;
    cr.right = &crr;
    cll.left = NULL;
    cll.right = NULL;
    clr.left = NULL;
    clr.right = NULL;
    crl.left = NULL;
    crl.right = NULL;
    crr.left = NULL;
    crr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    int res3 = (count_nodes(&c, 3) == 4);
    printf("test8:\n\n   o\n o   o\no o o o\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test9()
{
    struct tnode c, cl, cll;
    c.left = &cl;
    c.right = NULL;
    cl.left = &cll;
    cl.right = NULL;
    cll.left = NULL;
    cll.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 1);
    int res3 = (count_nodes(&c, 3) == 1);
    printf("test9:\n\n   o\n o   _\no _ _ _\n\n%d/3 tests passed\n\n", res1 + res2 + res3);
}

void test10()
{
    struct tnode c, cl, cr, cll, clr, crr, cllr, clrl, clrr, crrr, cllrl, cllrr, clrlr, crrrl, crrrr;
    c.left = &cl;
    c.right = &cr;
    cl.left = &cll;
    cl.right = &clr;
    cr.left = NULL;
    cr.right = &crr;
    cll.left = NULL;
    cll.right = &cllr;
    clr.left = &clrl;
    clr.right = &clrr;
    crr.left = NULL;
    crr.right = &crrr;//
    cllr.left = &cllrl;
    cllr.right = &cllrr;
    clrl.left = NULL;
    clrl.right = &clrlr;
    clrr.left = NULL;
    clrr.right = NULL;
    crrr.left = &crrrl;
    crrr.right = &crrrr;
    cllrl.left = NULL;
    cllrl.right = NULL;
    cllrr.left = NULL;
    cllrr.right = NULL;
    clrlr.left = NULL;
    clrlr.right = NULL;
    crrrl.left = NULL;
    crrrl.right = NULL;
    crrrr.left = NULL;
    crrrr.right = NULL;
    int res1 = (count_nodes(&c, 1) == 1);
    int res2 = (count_nodes(&c, 2) == 2);
    int res3 = (count_nodes(&c, 3) == 3);
    int res4 = (count_nodes(&c, 4) == 4);
    int res5 = (count_nodes(&c, 5) == 5);
    printf("test10:\n\n               o\n       o               o\n   o       o       _       o\n _   o   o   o   _   _   _   o\n_ _ o o _ o _ _ _ _ _ _ _ _ o o\n\n%d/5 tests passed\n\n", res1 + res2 + res3 + res4 + res5);
}

int main()
{
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return 0;
}