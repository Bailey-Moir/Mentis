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

    char map[6][14] = { "operator", "identifier", "constant", "keyword", "punctuation", "encapsulation" };
    for (int i = 0; i < num_tokens; i++) 
        printf("\"%s\" is a %s at %d\n", tokens[i].content, map[tokens[i].type], tokens[i].pos);

    return 0;
}
