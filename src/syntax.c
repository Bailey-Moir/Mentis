#include "syntax.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

AST *ast_new(AST ast) {
    AST *ptr = malloc(sizeof(AST));
    if (ptr) *ptr = ast;
    return ptr;
}
#define AST(tag, ...) \
ast_new((AST){AST_##tag, {.AST_##tag=(struct AST_##tag){__VA_ARGS__}}})

#define emitf printf
void ast_emit(AST *ptr) {
    AST ast = *ptr;
    switch (ast.tag) {
        case AST_MAIN: {
            struct AST_MAIN data = ast.data.AST_MAIN;
            emitf(".global main\n");
            emitf("main:\n");  // "_main" on macOS
            ast_emit(data.body);
            emitf("  ret\n");
            emitf("\n");
            return;
        }
        case AST_NUMBER: {
            struct AST_NUMBER data = ast.data.AST_NUMBER;
            emitf("  mov rax, %d\n", data.number);
            return;
        }
        case AST_ADD: {
            struct AST_ADD data = ast.data.AST_ADD;
            ast_emit(data.left);
            emitf("  push rax\n");
            ast_emit(data.right);
            emitf("  pop rbx\n");
            emitf("  add rax, rbx\n");
            return;
        }
        case AST_MUL: {
            struct AST_MUL data = ast.data.AST_MUL;
            ast_emit(data.left);
            emitf("  push rax\n");
            ast_emit(data.right);
            emitf("  pop rbx\n");
            emitf("  mul rbx\n");
            return;
        }
    }
}

void ast_free(AST *ptr) {
    AST ast = *ptr;
    switch (ast.tag) {
        case AST_NUMBER: {
            struct AST_NUMBER data = ast.data.AST_NUMBER;
            break;
        }
        case AST_ADD: {
            struct AST_ADD data = ast.data.AST_ADD;
            ast_free(data.left);
            ast_free(data.right);
            break;
        }
        case AST_MUL: {
            struct AST_MUL data = ast.data.AST_MUL;
            ast_free(data.left);
            ast_free(data.right);
            break;
        }
    }
    free(ptr);
}

AST* generateSyntaxTree(token* tokens) {
    AST* main = AST(MAIN, NULL);
    
    

    return main;
}
