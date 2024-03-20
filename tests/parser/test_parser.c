#include <stdio.h>
#include <assert.h>
#include "bf_lexer.h"
#include "bf_parser.h"

static void test_parse_without_a_loop(void) {
    Token tokens[] = { 
        {OP_INCREMENT_PTR, 0}, 
        {OP_DECREMENT_PTR, 1}, 
        {OP_INCREMENT_VAL, 2}, 
        {OP_DECREMENT_VAL, 3}, 
        {OP_OUTPUT, 4}
    };  
    
    Lexer mockLexer;
    mockLexer.tokens = tokens;
    mockLexer.size = sizeof(tokens) / sizeof(Token);

    ASTNode *root = create_ast_from_lexer(&mockLexer);

    assert(root->type == NODE_ROOT);
    assert(root->next != NULL);
    assert(root->next->type == NODE_INCREMENT_PTR);
    assert(root->next->next != NULL);
    assert(root->next->next->type == NODE_DECREMENT_PTR);
    assert(root->next->next->next != NULL);
    assert(root->next->next->next->type == NODE_INCREMENT_VAL);
    assert(root->next->next->next->next != NULL);
    assert(root->next->next->next->next->type == NODE_DECREMENT_VAL);
    assert(root->next->next->next->next->next != NULL);
    assert(root->next->next->next->next->next->type == NODE_OUTPUT);
    assert(root->next->next->next->next->next->next == NULL);

    destroy_ast(root);

    printf("test_parse passed!\n");
}

static void test_parse_with_a_loop(void) {
    Token mockTokens[] = {
        { OP_LOOP_START, 0 },
        { OP_INCREMENT_PTR, 1 },
        { OP_LOOP_END, 2 },
        { OP_DECREMENT_VAL, 3 }
    };

    Lexer mockLexer;
    mockLexer.tokens = mockTokens;
    mockLexer.size = sizeof(mockTokens) / sizeof(Token);

    ASTNode *root = create_ast_from_lexer(&mockLexer);

    assert(root->type == NODE_ROOT);
    assert(root->next != NULL);
    assert(root->next->type == NODE_LOOP_START);
    assert(root->next->jumpRef != NULL);
    assert(root->next->jumpRef->type == NODE_LOOP_END);
    assert(root->next->next != NULL);
    assert(root->next->next->type == NODE_INCREMENT_PTR);
    assert(root->next->next->next != NULL);
    assert(root->next->next->next->type == NODE_LOOP_END);
    assert(root->next->next->next->jumpRef != NULL);
    assert(root->next->next->next->jumpRef->type == NODE_LOOP_START);
    assert(root->next->next->next->next != NULL);
    assert(root->next->next->next->next->type == NODE_DECREMENT_VAL);

    destroy_ast(root);

    printf("test_parse_with_loop passed!\n");
}

extern void test_parser_run(void) {
    test_parse_without_a_loop();
    test_parse_with_a_loop();
}