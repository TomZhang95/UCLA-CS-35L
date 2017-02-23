#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>

int countCmp = 0;

int optionf(int value);
int frobcmp(char unsigned const *a, char unsigned const *b);
int frobcmpf(char unsigned const *a, char unsigned const *b);
int cmp(const void *a,const void *b);
int cmpf(const void *a,const void *b);


int main(int argc, const char * argv[])
{
    int fOption = 0;
    if (argc == 2 && !strcmp(argv[1], "-f"))
        fOption = 1;
    struct stat file;
    if (fstat(0, &file) != 0)
    {
        fprintf(stderr, "Fail to read file info");
        exit(1);
    }
    
    if (!S_ISREG(file.st_mode))
    {
        fprintf(stderr, "File read in is not a regular file");
        exit(1);
    }
    
    off_t file_size = file.st_size;
    int wordsSize = 64;
    unsigned char* ch = (unsigned char*) malloc(file_size);
    unsigned char** words = (unsigned char**) malloc(sizeof(unsigned char*)*wordsSize);
    if(ch == NULL || words == NULL)
    {
        fprintf(stderr, "Memory Allocation Error of words/ch/tmp");
        free(ch);
        free(words);
        exit(1);
    }
    int arraySize = 0;
    int stringSize = 0;
    
    unsigned char curr[1];
    unsigned char next[1];
    ssize_t currState = read(0, curr, 1);
    
    while (currState > 0)
    {
        if (file_size < file.st_size)
        {
            ch = (unsigned char*) realloc(ch, file.st_size);
            file_size = file.st_size;
        }
        
        if (curr[0] != '\n')
        {
            ch[stringSize] = curr[0];
            stringSize ++;
        }
        
        currState = read(0, next, 1);
        if (curr[0] != ' ' && currState <= 0)
        {
            ch[stringSize] = ' ';
            curr[0] = ' ';
        }
        
        if (curr[0] == ' ')
        {
            if (arraySize == wordsSize)
            {
                words = (unsigned char**) realloc(words, sizeof(unsigned char*)*(wordsSize*2));
                wordsSize *= 2;
            }
            if (words == NULL)
            {
                fprintf(stderr, "words realloc error");
                free(words);
                exit(1);
            }
            words[arraySize] = (unsigned char*) malloc(stringSize + 1);
            strcpy(words[arraySize], ch);
            arraySize++;
            memset(ch, 0, stringSize);
            stringSize = 0;
        }
        strcpy(curr, next);
        fstat(0, &file);
    }
    if (fOption == 1)
        qsort(words, arraySize, sizeof(unsigned char*), cmpf);
    else
        qsort(words, arraySize, sizeof(unsigned char*), cmp);
    for (unsigned long i = 0; i < arraySize; i++)
    {
        printf("%s", words[i]);
    }

    printf("Comparison Times: ");
    printf("%d", countCmp);
    free(ch);
    free(words);
    
    return 0;
}

int optionf(int value)
{
    return value;
}

int frobcmp(unsigned char const *a, unsigned char const *b)
{
  countCmp++;
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

int frobcmpf(unsigned char const *a, unsigned char const *b)
{
    countCmp++;
    for(;; a++, b++)
    {
      if ((toupper(*a^42)) < (toupper(*b^42)))
            return -1;
      else if ((toupper(*a^42)) > (toupper(*b^42)))
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
    return frobcmp(*(const unsigned char**)a, *(const unsigned char**)b);
}

int cmpf(const void *a,const void *b)
{
    return frobcmpf(*(const unsigned char**)a, *(const unsigned char**)b);
}
