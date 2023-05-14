#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#include "tokens.h"

FILE* fp;
char root[] = "C:/Users/Bailey/OneDrive/Documents/Programming/Mentis";
char filename[] = "proto.mt";

int main() {
    char path[100];
    sprintf(path, "%s/%s", root, filename);
    
    fp = fopen(path, "r");
    // Catch error opening file
    if (fp == NULL) {
        printf("Error opening file %s\n", path);
        exit(1);
    }

    size_t num_tokens;
    token* tokens = generateTokens(fp, &num_tokens);

    for (int i = 0; i < num_tokens; i++) {
        enum Token type = tokens[i].type;

        printf("\"%s\" is a %s at %d\n", tokens[i].content, 
            type == 0 ?
                "operator" :
            type == 1 ?
                "identifier" :
            type == 2 ?
                "constant" :
            type == 3 ?
                "keyword" :
            type == 4 ?
                "punctuation" :
            type == 5 ?
                "encapsulation" 
            :   
                "{ERROR: Invalid token type}",
            tokens[i].pos
        );
    }

    return 0;
}
