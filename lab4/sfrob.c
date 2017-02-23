#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int frobcmp(char const *a, char const *b);
int cmp(const void *a,const void *b);


int main(int argc, const char * argv[])
{
    
    char** words = (char**) malloc(sizeof(char*));
    char* ch = (char*) malloc(sizeof(char));
    if(words == NULL || ch == NULL)
    {
        fprintf(stderr, "Memory Allocation Error of words/temp");
        free(words);
        free(ch);
        exit(1);
    }
    int arraySize = 0;
    int stringSize = 0;
    
    char curr;
    char next;
    curr = getchar();
    
    while ( curr != EOF)
    {
        if (curr != '\n')
        {
            ch = realloc(ch, sizeof(char)*(stringSize + 1));
            if (ch == NULL)
            {
                fprintf(stderr, "ch realloc error");
                free(ch);
                exit(1);
            }
            ch[stringSize] = curr;
            stringSize ++;
        }
        
        next = getchar();
        if (curr != ' ' && next == EOF)
        {
            ch = realloc(ch, sizeof(char)*(stringSize + 1));
            ch[stringSize] = ' ';
            curr = ' ';
        }
        
        if (curr == ' ')
        {
            words = realloc(words, sizeof(char*)*(arraySize + 1));
            if (words == NULL)
            {
                fprintf(stderr, "words realloc error");
                free(words);
                exit(1);
            }
            words[arraySize] = ch;
            arraySize++;
            ch = NULL;
            ch = realloc(ch, sizeof(char));
            stringSize = 0;
        }
        curr = next;
        
    }
    qsort(words, arraySize, sizeof(words[0]), cmp);
    for (unsigned long i = 0; i < arraySize; i++)
    {
        printf("%s", words[i]);
    }
    
    free(ch);
    free(words);
    
    return 0;
}

int frobcmp(char const *a, char const *b)
{
    for(;; a++, b++)
    {
        if ((*a^42) < (*b^42))
            return -1;
        else if ((*a^42) > (*b^42))
            return 1;
        else if (*a == ' ' && *b == ' ')
            return 0;
        else if (*a == ' ' && *b != ' ')
            return -1;
        else if (*a != ' ' && *b == ' ')
            return 1;
    }
}

int cmp(const void *a,const void *b)
{
    return frobcmp(*(const char**)a, *(const char**)b);
}
