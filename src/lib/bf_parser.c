#include <stdlib.h>
#include <stdio.h>
#include "bf_lexer.h"
#include "bf_parser.h"

NodeType get_node_type_from_op(OpCodeType opCode) {
    switch (opCode) {
        case OP_INCREMENT_PTR: return NODE_INCREMENT_PTR;
        case OP_DECREMENT_PTR: return NODE_DECREMENT_PTR;
        case OP_INCREMENT_VAL: return NODE_INCREMENT_VAL;
        case OP_DECREMENT_VAL: return NODE_DECREMENT_VAL;
        case OP_OUTPUT: return NODE_OUTPUT;
        case OP_INPUT: return NODE_INPUT;
        case OP_LOOP_START: return NODE_LOOP_START;
        case OP_LOOP_END: return NODE_LOOP_END;
        default: return NODE_UNKNOWN;
    }
}

static ASTNode *create_ast_node(NodeType type, size_t index, ASTNode *next, ASTNode *jumpRef) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    node->type = type;
    node->tokenIndex = index;
    node->next = next;
    node->jumpRef = jumpRef;

    return node;
}

extern ASTNode *create_ast_from_lexer(Lexer *lexer) {
    ASTNode *root = create_ast_node(NODE_ROOT, 0, NULL, NULL);
    ASTNode *currentNode = root;

    ASTNode **loopStack = (ASTNode **)malloc(sizeof(ASTNode *) * (lexer->size - 1));
    if (loopStack == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    size_t loopStackPtr = 0;
    size_t tokenPtr = 0;

    while(tokenPtr < lexer->size) {
        OpCodeType opType = lexer->tokens[tokenPtr].type;
        size_t index = lexer->tokens[tokenPtr++].index;

        switch (opType)
        {
            case OP_INCREMENT_PTR:
            case OP_DECREMENT_PTR:
            case OP_INCREMENT_VAL:
            case OP_DECREMENT_VAL:
            case OP_OUTPUT:
            case OP_INPUT:
                currentNode->next = create_ast_node(get_node_type_from_op(opType), index, NULL, NULL);
                currentNode = currentNode->next;
                break;
            
            case OP_LOOP_START:
                loopStack[loopStackPtr] = create_ast_node(get_node_type_from_op(opType), index, NULL, NULL);
                currentNode->next = loopStack[loopStackPtr++]; 
                currentNode = currentNode->next;
                break;

            case OP_LOOP_END:
                if (loopStackPtr == 0) {
                    fprintf(stderr, "Error at character index %lu: Unmatched loop end encountered. Missing loop start.\n", index);
                    break; 
                }  

                currentNode->next = create_ast_node(get_node_type_from_op(opType), index, NULL, loopStack[--loopStackPtr]);
                currentNode = currentNode->next;
                loopStack[loopStackPtr]->jumpRef = currentNode;
                break;

            default:
                fprintf(stderr, "Error at character index %lu: Unrecognized opcode encountered.\n", index);
                break;
        }
    }

    if (loopStackPtr != 0) {
        for (size_t i = 0; i < loopStackPtr; ++i) {
            fprintf(stderr, "Error at character index %lu: Unmatched loop start encountered. Missing loop end.\n", loopStack[i]->tokenIndex);
        }
        return NULL;
    }

    return root;
}

extern void destroy_ast(ASTNode *root) {
    if (root == NULL) {
        return;
    }

    destroy_ast(root->next);

    free(root);
}