// сортировки

#include <stdio.h>

int main()
{
    //пузырьком
    int a[10];

    for(int i = 0 ; i < 10; i++)
    { 
        scanf("%d", &a[i]);
    }
    for(int i = 0 ; i < 9; i++)
    { 
        for(int j = 0 ; j < 8; j++)
        {  
            if(a[j] > a[j+1]) 
            {           
                int swap = a[j];
                a[j] = a[j+1] ;
                a[j+1] = swap; 
            }
        }
    }
    for (int i = 0; i < 10; i++)
        printf("%d ", a[i]);


    //вставками
    int b[10];

    for(int i = 0 ; i < 10; i++)
    { 
        scanf("%d", &b[i]);
    }
    for(int i = 0 ; i < 9; i++)
    { 
        for(int j = 0 ; j < 10; j++)
        {  
            if(b[i] > a[j]) 
            {           
                int swap = b[j];
                b[j] = b[i] ;
                b[i] = swap; 
            }
        }
    }
    for (int i = 0; i < 10; i++)
        printf("%d ", b[i]);
}
