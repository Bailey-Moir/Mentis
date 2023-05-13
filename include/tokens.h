#include <stdbool.h>
#include <stdio.h>
#ifndef TOKENS_H
#define TOKENS_H

//      OPERATORS
#define N_OPERATORS 26
/**
 * @brief All of the operators in Mentis. 
 */
extern char operators[N_OPERATORS][3];
/**
 * @brief Get the position and size of the first operator in the given string; searching as a substring. Has a higher priority for longer operators.
 * 
 * @param string String to search in.
 * @param bufferPointer A pointer to the buffer to fill.
 * @param sizePointer A pointer to the variable where the size of the buffer is to be saved.
 */
void getOperator(char* string, char** bufferPointer, size_t* sizePointer);



//      ENCAPSULATION
#define N_ENCAPSULATIONS 6
/**
 * @brief All of the brackets used in Mentis.
 */
extern char encapsulations[N_ENCAPSULATIONS];
/**
 * @brief Checks if the given characeter is an encapsulator (bracket/parenthesis).
 * 
 * @param ch The character to check.
 * @return If it is encapsulation or not.
 */
bool isEncapsulation(char ch);


//      PUNCTUATION
#define N_PUNCTUATIONS 7
/**
 * @brief All of the punctuation used in Mentis.
 */
extern char punctuations[N_PUNCTUATIONS];
/**
 * @brief Checks if the given characeter is a piece of punctuation.
 * 
 * @param ch The character to check.
 * @return If it is punctuation or not.
 */
bool isPunctuation(char ch);



//      KEYWORDS
#define N_KEYWORDS 11
#define L_KEYWORD 10
/**
 * @brief All of the keywords in Mentis.
 */
extern char keywords[N_KEYWORDS][L_KEYWORD];
/**
 * @brief Checks if the given string is a keyword in Mentis.
 * 
 * @param string The string to check.
 * @return If it is a keyword or not.
 */
bool isKeyword(char* string);



//      TOKENS
#define L_TOKEN 20
/**
 * @brief Specifies the type of a token.
 */
enum Token {
    operator,
    identifier,
    constant,
    keyword,
    punctuation,
    encapsulation
};
/**
 * @brief Represents a token for lexical analysis.
 */
struct token {
    /**
     * @brief The type of token.
     */
    enum Token type;
    /**
     * @brief The text of the token (e.g. "=>", "}", "constant").
     */
    char content[L_TOKEN];
} typedef token;
/**
 * @brief The amount of items currently in the 'tokens' array.
 */
extern int i_tokens;
/**
 * @brief All of the tokens in the given file.
 */
extern token tokens[500];
/**
 * @brief Add a token to the 'token' array.
 * 
 * @param string The content of the token.
 * @param pos The position in the stream where the token begins.
 * @param type The type of the token.
 */
void addToken(char* string, fpos_t pos, enum Token type);
/**
 * @brief Add a token of unknown type to the 'token' array.
 * 
 * @param string The content of the token.
 * @param pos The position in the stream where the token begins.
 */
void addTokenUnknown(char* string, fpos_t fpos);

#endif // TOKENS_H