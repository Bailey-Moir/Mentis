#include <string.h>
#include <ctype.h>
#include "tokens.h"

// === PRIVATE ===

bool isInt(char* string) {
    for (int i = 0; i < strlen(string); i++) 
        if (!isdigit(string[i])) return false;
    
    return true;
}

//      OPERATORS
#define N_OPERATORS 26
/**
 * @brief All of the operators in Mentis. 
 */
char operators[N_OPERATORS][3] = {
    "+", "-", "^", "*", "/", "%", "=", "+=", "-=", "*=", "/=", "%=", "^=", ">", "<", ">=", "<=", "==", "!=", "&&", "||", "?", ":", "!", "++", "--"
};
/**
 * @brief Get the position and size of the first operator in the given string; searching as a substring. Has a higher priority for longer operators.
 * 
 * @param string String to search in.
 * @param bufferPointer A pointer to the buffer to fill.
 * @param sizePointer A pointer to the variable where the size of the buffer is to be saved.
 */
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
}

//      ENCAPSULATION
#define N_ENCAPSULATIONS 6
/**
 * @brief All of the brackets used in Mentis.
 */
char encapsulations[N_ENCAPSULATIONS] = "[{()}]";
/**
 * @brief Checks if the given characeter is an encapsulator (bracket/parenthesis).
 * 
 * @param ch The character to check.
 * @return If it is encapsulation or not.
 */
bool isEncapsulation(char ch) {
    for(int i = 0; i < N_ENCAPSULATIONS; i++)
        // If encapsulation is equal to string, return true.
        if(encapsulations[i] == ch) return true;
    
    return false;
}


//      PUNCTUATION
#define N_PUNCTUATIONS 7
/**
 * @brief All of the punctuation used in Mentis.
 */
char punctuations[N_PUNCTUATIONS] = "`:'\",.;";
/**
 * @brief Checks if the given characeter is a piece of punctuation.
 * 
 * @param ch The character to check.
 * @return If it is punctuation or not.
 */
bool isPunctuation(char ch) {
    for(int i = 0; i < N_PUNCTUATIONS; i++)
        // If punctuation is equal to string, return true.
        if(punctuations[i] == ch) return true;
    
    return false;
}

//      KEYWORDS
#define N_KEYWORDS 11
#define L_KEYWORD 10
/**
 * @brief All of the keywords in Mentis.
 */
char keywords[N_KEYWORDS][L_KEYWORD] = {
    "for", "return", "break", "while", "if", "else", "void", "constant", "string", "enum", "number"
};
/**
 * @brief Checks if the given string is a keyword in Mentis.
 * 
 * @param string The string to check.
 * @return If it is a keyword or not.
 */
bool isKeyword(char* string){
    for(int i = 0; i < N_KEYWORDS; i++)
        // If keyword is equal to string, return true.
        if(!strcmp(keywords[i], string)) return true;
    
    return false;
}

/**
 * @brief The amount of items currently in the 'tokens' array.
 */
int i_tokens = 0;
/**
 * @brief All of the tokens in the given file.
 */
token tokens[500];
/**
 * @brief Add a token to the 'token' array.
 * 
 * @param string The content of the token.
 * @param pos The position in the stream where the token begins.
 * @param type The type of the token.
 */
void addToken(char* string, fpos_t pos, enum Token type) {
    strcpy(tokens[i_tokens].content, string);
    tokens[i_tokens].pos = pos;
    tokens[i_tokens++].type = type;
}
/**
 * @brief Add a token of unknown type to the 'token' array.
 * 
 * @param string The content of the token.
 * @param pos The position in the stream where the token begins.
 */
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



// === PUBLIC ===

token* generateTokens(FILE* fp, size_t* sizePointer) {
    fpos_t fpos;
    int buffer_len = 0;
    char ch, buffer[L_TOKEN];
    while((ch = fgetc(fp)) != EOF) {        
        // Update the current position in the stream, add character to buffer and move to next slot
        fgetpos(fp, &fpos);
        buffer[buffer_len++] = ch;
        buffer[buffer_len] = '\0';

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
                addTokenUnknown(buffer, fpos - buffer_len);
                *operatorPointer = startChar;
            } 

            // If the operator is is 2 long, save it
            if (operatorSize == 2) {
                addToken(operatorPointer, fpos-1, operator);
            } else if (pointerSize != 1) { // if the operator is 1 long and it's checked the character after, save it
                // remove following space
                operatorPointer[1] = '\0';
                addToken(operatorPointer, fpos--, operator);

                // Reread character after the operator if it's not space or newline
                if (ch != ' ' && ch != '\n') fsetpos(fp, &fpos);
            }

            // Clear buffer if not about to check next character.
            if (pointerSize == 2) buffer_len = 0;
        } else if(ch == ' ' || ch == '\n') {
            // remove following space or new line
            buffer[--buffer_len] = '\0';
            // If there were characters before the space, store the token
            if (buffer_len > 0) addTokenUnknown(buffer, fpos - buffer_len);
            // Reset buffer counter as spaces/newlines aren't counted and characters have been stored
            buffer_len = 0;
        } else if (isPunctuation(ch) || isEncapsulation(ch)) {
            // If there is text in the buffer before the punctuation, save that token               
            if (buffer_len > 1) {
                buffer[--buffer_len] = '\0';
                addTokenUnknown(buffer, fpos - buffer_len);
                buffer[buffer_len++] = ch;
            }
            
            // Save the punctuation token
            addToken(buffer + sizeof(char)*(buffer_len-1), fpos, isEncapsulation(ch) ? encapsulation : punctuation);
            buffer_len = 0;
        }
    }

    *sizePointer = i_tokens;    
    return tokens;
}