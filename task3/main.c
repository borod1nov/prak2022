#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "word.h"

int end_push_clear(word* w, word_list* list)
{
    push_sym(w, '\0');
    push_word(list, w->symbols);
    clear_word(w);
}

int regular_sym(char c)
{
    return ((c == '$') || (c == '_') || (c == '/') || (c == '.') || ((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

int special_sym(char c)
{
    return ((c == '|') || (c == '&') || (c == ';') || (c == '>') || (c == '<') || (c == '(') || (c == ')'));
}

int could_be_double(char c)
{
    return ((c == '>') || (c == '&') || (c == '|'));
}

int space_sym(char c)
{
    return ((c == ' ') || (c == '\t'));
}

int main()
{
    word* buf = create_word();
    word_list* list = create_list();
    int eof_flag = 0;
    int double_count = 0;
    int incorrect_sym = 0;
    while (!eof_flag)
    {
        int c = getc(stdin);
        int prevc = -1;
        while ((c != '\n') && (c != EOF))
        {
            
            if (!could_be_double(c))
            {
                double_count = 0;
            }
            if (space_sym(c))
            {
                if (buf->top > -1)
                {
                    end_push_clear(buf, list);
                }
            }
            else if (regular_sym(c))
            {
                if (could_be_double(prevc))
                {
                    if (buf->top > -1)
                    {
                        end_push_clear(buf, list);
                    }
                }
                push_sym(buf, c);
            }
            else if (special_sym(c))
            {
                if (could_be_double(c))
                {
                    if ((double_count == 1) && (prevc == c))
                    {
                        push_sym(buf, c);
                        end_push_clear(buf, list);
                        double_count = 0;
                    }
                    else
                    {
                        if (buf->top > -1)
                        {
                            end_push_clear(buf, list);
                        }
                        push_sym(buf, c);
                        double_count = 1;
                    }
                }
                else
                {
                    if (buf->top > -1)
                    {
                        end_push_clear(buf, list);
                    }
                    push_sym(buf, c);
                    end_push_clear(buf, list);
                }
            }
            else
            {
                incorrect_sym = 1;
            }
            prevc = c;
            c = getc(stdin);
        }
        if (buf->top > -1)
        {
            end_push_clear(buf, list);
        }
        if (c == EOF)
        {
            eof_flag = 1;
            continue;
        }
        if (incorrect_sym)
        {
            printf("Incorrect input. Enter your string again:\n");
            incorrect_sym = 0;
            clear_list(list);
            continue;
        }
        print_list(list);
        sort_list(list);
        print_list(list);
        clear_list(list);
    }
    delete_word(buf);
    delete_list(list);
}