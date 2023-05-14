#include <stdbool.h>
#include <stdio.h>
#ifndef TOKENS_H
#define TOKENS_H

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
    /**
     * @brief The position in the file of the start of the token.
     */
    fpos_t pos;
} typedef token;

/**
 * @brief Generates a list of all the tokens in the given file.
 * 
 * @param fp The file pointer to get the tokens from.
 * @param sizePointer An optional pointer to stor the size of the token array generated.
 * @return The token array.
 */
token* generateTokens(FILE* fp, size_t* sizePointer);

#endif // TOKENS_H