#ifndef BF_PARSER_IMPL_H
#define BF_PARSER_IMPL_H

typedef enum {
    NODE_INCREMENT_PTR,
    NODE_DECREMENT_PTR,
    NODE_INCREMENT_VAL,
    NODE_DECREMENT_VAL,
    NODE_OUTPUT,
    NODE_INPUT,
    NODE_LOOP_START,
    NODE_LOOP_END,
    NODE_ROOT,
    NODE_UNKNOWN,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    size_t tokenIndex;
    struct ASTNode *next;
    struct ASTNode *jumpRef;
} ASTNode;

extern ASTNode *create_ast_from_lexer(Lexer *lexer);
extern void destroy_ast(ASTNode *root);

#endif