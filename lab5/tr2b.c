//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int main(int argc, const char * argv[]) {
//    
//    if (argc < 3)
//    {
//        fprintf(stderr, "Wrong Number of Arguments");
//        exit(1);
//    }
//    
//    const char* from = argv[1];
//    const char* to = argv[2];
//    
//    if (strlen(from) != strlen(to))
//    {
//        fprintf(stderr, "Different Size of 'From' and 'To'");
//        exit(1);
//    }
//    
//    for (int i = 0; i < strlen(from) -1; i++)
//    {
//        for(int j = i + 1; j < strlen(from); j++)
//        {
//            if (from[i] == from[j])
//            {
//                fprintf(stderr, "Same element in 'From'");
//                exit(1);
//            }
//        }
//    }
//    
//    //read chars from stdin
//    char character = getchar();
//    while (character != EOF)
//    {
//        //if character == part of from, transfer
//        for (int i = 0; i < strlen(from); i++)
//        {
//            if (character == from[i])
//                character = to[i];
//            //if not, don't change
//        }
//        putchar(character);
//        character = getchar();
//        
//    }
//
//    return 0;
//}
