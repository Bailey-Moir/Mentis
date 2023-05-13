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

    fpos_t fpos;
    int buffer_len = 0;
    char ch, buffer[L_TOKEN];
    while((ch = fgetc(fp)) != EOF) {


        
        // Update the current position in the stream, add character to buffer and move to next slot
        fgetpos(fp, &fpos);
        buffer[buffer_len++] = ch;
        buffer[buffer_len] = '\0';

        //printf("%s\n", buffer);

        char* operatorPointer = NULL;
        size_t operatorSize = 0;
        getOperator(buffer, &operatorPointer, &operatorSize);
        if (operatorPointer) {
            size_t pointerSize = strlen(operatorPointer);
            // If it's not first iteration of an operator of 1 size, and there are characters behind
            // the operator, save that token
            if (pointerSize == 2 && buffer_len > 2) {
                char startChar = *operatorPointer;
                *operatorPointer = '\0';
                addTokenUnknown(buffer, fpos);
                *operatorPointer = startChar;
            } 

            // If the operator is is 2 long, save it
            if (operatorSize == 2) {
                addToken(operatorPointer, fpos, operator);
            } else if (pointerSize != 1) { // if the operator is 1 long and it's checked the character after, save it
                // remove following space
                operatorPointer[1] = '\0';
                addToken(operatorPointer, fpos, operator);

                // Reread character after the operator if it's not space or newline
                if (ch != ' ' && ch != '\n') {
                    fpos--;
                    fsetpos(fp, &fpos);
                }
            }

            // Clear buffer if not about to check next character.
            if (pointerSize == 2) buffer_len = 0;
        } else if(ch == ' ' || ch == '\n') {
            // remove following space or new line
            buffer[--buffer_len] = '\0';
            // If there were characters before the space, store the token
            if (buffer_len > 0) addTokenUnknown(buffer, fpos);
            // Reset buffer counter as spaces/newlines aren't counted and characters have been stored
            buffer_len = 0;
        } else if (isPunctuation(ch) || isEncapsulation(ch)) {
            // If there is text in the buffer before the punctuation, save that token               
            if (buffer_len > 1) {
                buffer[--buffer_len] = '\0';
                addTokenUnknown(buffer, fpos);
                buffer[buffer_len++] = ch;
            }

            // Save the punctuation token
            addToken(buffer + sizeof(char)*(buffer_len-1), fpos, isEncapsulation(ch) ? encapsulation : punctuation);
            buffer_len = 0;
        }
    }

    for (int i = 0; i < i_tokens-1; i++) {
        enum Token type = tokens[i].type;

        printf("\" %s \" - %s\n", tokens[i].content, 
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
                "{ERROR: Invalid token type}"
        );
    }

    return 0;
}
