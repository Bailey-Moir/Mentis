#ifndef SYNTAX_H
#define SYNTAX_H

// Forward reference to allow for recursive type definition
typedef struct AST AST;

struct AST {
  enum {
    AST_MAIN,
    AST_NUMBER,
    AST_ADD,
    AST_MUL,
  } tag;
  union {
    struct AST_MAIN { AST *body; } AST_MAIN;
    struct AST_NUMBER { int number; } AST_NUMBER;
    struct AST_ADD { AST *left; AST *right; } AST_ADD;
    struct AST_MUL { AST *left; AST *right; } AST_MUL;
  } data;
};

typedef struct token token; // Forward declaration
AST* generateSyntaxTree(token* tokens);

#endif // SYNTAX_H