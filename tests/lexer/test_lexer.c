#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bf_lexer.h"

static void test_lexer_initialization(void) {
    Lexer *lexer = create_lexer(10);

    assert(lexer != NULL);
    assert(lexer->size == 0);
    assert(lexer->capacity == 10);

    destroy_lexer(lexer);

    printf("test_lexer_initialization_and_destruction passed!\n");
}

static void test_tokenization(void) {
    Lexer *lexer = create_lexer(10);

    char input[] = "><+-.,[]";
    OpCodeType expectedOp[] = { OP_INCREMENT_PTR, OP_DECREMENT_PTR, OP_INCREMENT_VAL, OP_DECREMENT_VAL, OP_OUTPUT, OP_INPUT, OP_LOOP_START, OP_LOOP_END }; 

    TokenizationResult result = tokenize(lexer, input);

    assert(result == TOKENIZE_SUCCESS);
    assert(lexer->size == strlen(input));

    for (size_t i = 0; i < lexer->size; ++i) {
        assert(lexer->tokens[i].type == expectedOp[i]);
    }

    destroy_lexer(lexer);

    printf("test_tokenization passed!\n");
}

static void test_lexer_capacity_growth(void) {
    Lexer *lexer = create_lexer(5);

    char input[] = "++++++";
    TokenizationResult result = tokenize(lexer, input);

    assert(result == TOKENIZE_SUCCESS);
    assert(lexer->size == strlen(input));
    assert(lexer->capacity == 10);

    destroy_lexer(lexer);

    printf("test_lexer_capacity_growth passed!\n");
}

static void test_tokenization_empty_input(void) {
    Lexer *lexer = create_lexer(10);

    char input[] = "";

    TokenizationResult result = tokenize(lexer, input);

    assert(result == TOKENIZE_SUCCESS);
    assert(lexer->size == 0);

    destroy_lexer(lexer);

    printf("test_tokenization_empty_input passed!\n");
}

extern void test_lexer_run(void) { 
    test_lexer_initialization();
    test_tokenization();
    test_lexer_capacity_growth();
    test_tokenization_empty_input();
}