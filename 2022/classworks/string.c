#include <stdio.h>
#define MAX_STR 255

int main(void)
{
    
    char string[MAX_STR];
    int counts[MAX_STR];
    char c;
    int end = 0, i = 0;
    
    for (int i = 0; i < MAX_STR; i++)
        counts[i] = 0;
        
    scanf("%c", &c);
    while (!end)
    {
        if ((i >= 2) && (c == 'D'))
        {
            if ((string[i - 1] == 'N') && (string[i - 2] == 'E'))
            {
                end = 1;
                continue;
            }
        }
        string[i] = c;
        scanf("%c", &c);
        i++;
        
    }
    i -= 2;
    string[i] = '\0';
    
    for (int j = 0; j < i; j++)
    {
        
        counts[string[j]] += 1;
    }
    
    for (int i = 0; i < MAX_STR; i++)
    {
        if (counts[i] > 0)
            printf("%c %d\n", i, counts[i]);
    }
}
