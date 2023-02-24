#define SIZE 5

typedef struct
{
    char* symbols;
    int top;
    int size;
} word;

word* create_word();
int resize_word(word* w);
int push_sym(word* w, char c);
int delete_word(word* w);
int clear_word(word* w);
