#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "word.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#define INIT_SIZE 10
#define MULTIPLIER 2
#define MAX_NAME 20
#define MAX_SIZE 20

typedef struct array_tag
{
    char** data;
    size_t size;
    size_t top;
} array_t;

typedef struct cmd
{
    array_t* argv;
    char input[MAX_NAME];
    char output1[MAX_NAME];
    char output2[MAX_NAME];
    int background;
}cmd;

typedef struct cmd_data
{
    char name[MAX_NAME];
    char input[MAX_NAME];
    char output1[MAX_NAME];
    char output2[MAX_NAME];
    int background;
}cmd_data;

typedef struct cmd_data_array
{
    cmd_data info[MAX_SIZE];
    int background;
    int top;
}cmd_data_array;

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

void inv()
{
    printf("%s", "\033[01;33m");
    char s[100];
    gethostname(s, 100);
    printf("%s@%s", getenv("USER"), s);
    printf("%s", "\033[22;31m");
    getcwd(s, 100);
    printf(":%s", s);
    printf("%s", "\033[0m");
    printf("$ ");
}

array_t* create_array()
{
    array_t *out = malloc(sizeof(array_t));
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(char*));
    out->top = 0;
    return out;
}

int resize_array(array_t *array)
{
    array->size *= MULTIPLIER;
    array->data = realloc(array->data, array->size * sizeof(char*));
    return 0;
}

int append_array(array_t *array, const char* value)
{
    if (array->top >= array->size)
        resize_array(array);

    int len = strlen(value);
    char* value_copy = malloc((len + 1) * sizeof(char));
    strcpy(value_copy, value);

    array->data[array->top] = value_copy;
    array->top++;
    return 0;
}

int delete_array(array_t* array)
{
    for (int i = array->top; i < array->size; i++)
        array->data[i] = NULL;
    for (int i = 0 ; i < array->size; i++)
        free(array->data[i]);
    free(array->data);
    free(array);
    return 0;
}

int expr_type(array_t* tokens)
{
    for (int i = 0; i < tokens->top; i++)
    {
        if (!strcmp(tokens->data[i], "|"))
            return 2;
        else if (!strcmp(tokens->data[i], "||"))
            return 3;
    }
    return 1;
}

void init_cmds(cmd_data_array* arr)
{
    arr->top = 0;
    arr->background = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        arr->info[i].name[0] = '\0';
        arr->info[i].input[0] = '\0';
        arr->info[i].output1[0] = '\0';
        arr->info[i].output2[0] = '\0';
        arr->info[i].background = 0;
    }
}

void fill_cmds(cmd_data_array* arr, array_t* tokens)
{
    for (int i = 0; i < tokens->top; i++)
    {
        if (((i == 0) && (!strstr(">><||&", tokens->data[i]))) || ((!strstr(">><||&", tokens->data[i])) && (!strstr(">><", tokens->data[i - 1]))))
        {
            strcpy(arr->info[arr->top].name, tokens->data[i]);

            if ((i < tokens->top - 2) && (!strcmp(tokens->data[i + 1], ">")))
                strcpy(arr->info[arr->top].output1, tokens->data[i + 2]);
            else if ((i < tokens->top - 2) && (!strcmp(tokens->data[i + 1], ">>")))
                strcpy(arr->info[arr->top].output2, tokens->data[i + 2]);
            else if ((i < tokens->top - 2) && (!strcmp(tokens->data[i + 1], "<")))
                strcpy(arr->info[arr->top].input, tokens->data[i + 2]);
            
            arr->top++;
        }
    }
}

void fill_background(cmd_data_array* arr, array_t* tokens)
{
    if (!strcmp(tokens->data[tokens->top - 1], "&"))
        arr->background = 1;
}

void execute_conv(cmd_data_array* arr)
{
    int fd[2], file;
    int oldfd0;
    for (int i = 0; i < arr->top; i++)
    {
        if (pipe(fd) != 0)
            exit(0);
        if (fork() == 0)
        {
            if (i + 1 != arr->top)
            {
                dup2(fd[1], 1);
            }
            if (i != 0)
            {
                dup2(oldfd0, 0);
            }
            if (arr->info[i].output1[0] != '\0')
            {
                file = open(arr->info[i].output1, O_WRONLY | O_CREAT, 0666);
                dup2(file, 1);
                close(file);
            }
            else if (arr->info[i].output2[0] != '\0')
            {
                file = open(arr->info[i].output2, O_WRONLY | O_CREAT | O_APPEND, 0666);
                dup2(file, 1);
                close(file);
            }
            else if (arr->info[i].input[0] != '\0')
            {
                file = open(arr->info[i].input, O_RDONLY);
                dup2(file, 0);
                close(file);
            }
            close(fd[0]);
            close(fd[1]);
            execlp(arr->info[i].name, arr->info[i].name, NULL);
            exit(0);
        }
        oldfd0 = fd[0];
        close(fd[1]);
    }
    if (arr->background == 0)
        while(wait(NULL) != -1);
}

void init_command(cmd* command)
{
    command->argv = create_array();
    command->input[0] = '\0';
    command->output1[0] = '\0';
    command->output2[0] = '\0';
    command->background = 0;
}

void fill_command(cmd* command, array_t* tokens)
{
    int i = 0;
    while ((i < tokens->top) && (!strstr(">><&", tokens->data[i])))
    {
        append_array(command->argv, tokens->data[i]);
        i++;
    }
    command->argv->data[command->argv->top] = NULL;
    while (i < tokens->top)
    {
        if ((!strcmp(tokens->data[i], "<")) && (i < tokens->top - 1))
            strcpy(command->input, tokens->data[i + 1]);
        else if ((!strcmp(tokens->data[i], ">")) && (i < tokens->top - 1))
            strcpy(command->output1, tokens->data[i + 1]);
        else if ((!strcmp(tokens->data[i], ">>")) && (i < tokens->top - 1))
            strcpy(command->output2, tokens->data[i + 1]);
        i++;
    }
    if (!strcmp(tokens->data[tokens->top - 1], "&"))
        command->background = 1;
    
}

void execute_command(cmd* cmd)
{
    int file1;
    int file2;
    if (fork() == 0)
    {
        if (cmd->output1[0] != '\0')
        {
            file1 = open(cmd->output1, O_WRONLY | O_CREAT, 0666);
            dup2(file1, 1);
            close(file1);
        }
        else if (cmd->output2[0] != '\0')
        {
            file1 = open(cmd->output2, O_WRONLY | O_CREAT | O_APPEND, 0666);
            dup2(file1, 1);
            close(file1);
        }
        if (cmd->input[0] != '\0')
        {
            file2 = open(cmd->input, O_RDONLY);
            dup2(file2, 0);
            close(file2);
        }
        execvp(cmd->argv->data[0], cmd->argv->data);
        exit(0);
    }
    if (cmd->background == 0)
        while(wait(NULL) != -1);
}

void execute3(array_t* tokens_array)
{
    int status = 256, forkRet;
    char programs[2][MAX_NAME];
    strcpy(programs[0], tokens_array->data[0]);
    strcpy(programs[1], tokens_array->data[2]);
    if (fork() == 0)
    {
        execlp(programs[0], programs[0], NULL);
        exit(1);
    }
    wait(&status);
    if (WIFEXITED(status) && (WEXITSTATUS(status) != 0))
    {
        if (fork() == 0)
        {
            execlp(programs[1], programs[1], NULL);
            exit(1);
        }
        wait(&status);
    }
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
        inv();
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
        array_t* tokens_array = create_array();
        for (int j = 0; j <= list->top; j++)
            append_array(tokens_array, list->data[j]);

        int type = expr_type(tokens_array);
        if (type == 1)
        {
            cmd command;
            init_command(&command);
            fill_command(&command, tokens_array);
            execute_command(&command);
        }
        else if (type == 2)
        {
            cmd_data_array cda;
            init_cmds(&cda);
            fill_cmds(&cda, tokens_array);
            fill_background(&cda, tokens_array);
            execute_conv(&cda);
        }
        else
        {
            execute3(tokens_array);
        }
        delete_array(tokens_array);
        clear_list(list);
    }
    delete_word(buf);
    delete_list(list);
}