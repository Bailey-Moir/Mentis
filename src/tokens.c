#include <string.h>
#include <ctype.h>
#include "tokens.h"

bool isInt(char* string) {
    for (int i = 0; i < strlen(string); i++) 
        if (!isdigit(string[i])) return false;
    
    return true;
}

char operators[N_OPERATORS][3] = {
    "+", "-", "^", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=", "^=", ">", "<", ">=", "<=", "==", "!=", "&&", "||", "?", ":", "!", "++", "--"
};

void getOperator(char* string, char** bufferPointer, size_t* sizePointer) {
    *sizePointer = 0;
    *bufferPointer = NULL;

    int j = 0;
    for(int i = 0; i < N_OPERATORS; i++) {
        char* substring = strstr(string,operators[i]);
        size_t size = strlen(operators[i]);
        
        if (substring && size > *sizePointer) {
            *bufferPointer = substring;
            *sizePointer = strlen(operators[i]);
        }
    }

    // if (*bufferPointer) printf("%s : %d token %s\n", string, j, *bufferPointer);
}

char encapsulations[N_ENCAPSULATIONS] = "[{()}]";
bool isEncapsulation(char ch) {
    for(int i = 0; i < N_ENCAPSULATIONS; i++)
        // If encapsulation is equal to string, return true.
        if(encapsulations[i] == ch) return true;
    
    return false;
}

char punctuations[N_PUNCTUATIONS] = "`:'\",.;";
bool isPunctuation(char ch) {
    for(int i = 0; i < N_PUNCTUATIONS; i++)
        // If punctuation is equal to string, return true.
        if(punctuations[i] == ch) return true;
    
    return false;
}

char keywords[N_KEYWORDS][L_KEYWORD] = {
    "for", "return", "break", "while", "if", "else", "void", "constant", "string", "enum", "number"
};
bool isKeyword(char* string){
    for(int i = 0; i < N_KEYWORDS; i++)
        // If keyword is equal to string, return true.
        if(!strcmp(keywords[i], string)) return true;
    
    return false;
}

int i_tokens = 0;
token tokens[500];
void addToken(char* string, fpos_t pos, enum Token type) {
    strcpy(tokens[i_tokens].content, string);
    tokens[i_tokens++].type = type;
}
void addTokenUnknown(char* string, fpos_t pos) {
    addToken(string, pos,
        isKeyword(string) ?
                keyword :
        isInt(string) ?
            constant            
        :
            identifier
    );
}