#define SIZE 5

typedef struct
{
    char** data;
    int top;
    int size;
} word_list;

word_list* create_list();
int resize_list(word_list* list);
int push_word(word_list* list, char* word);
int sort_list(word_list* list);
int print_list(word_list* list);
int clear_list(word_list* list);
int delete_list(word_list* list);
