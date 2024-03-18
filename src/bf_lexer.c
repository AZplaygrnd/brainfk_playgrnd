#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bf_lexer.h"

#define CAPACITY_INCREASE_FACTOR 2

static Token create_token(OpCodeType type, size_t index) {
    Token token = {
        .type = type,
        .index = index
    };

    return token;
}

static bool add_token(Lexer *lexer, Token token) {
    if (lexer->size >= lexer->capacity) {
        size_t newCapacity = lexer->capacity * CAPACITY_INCREASE_FACTOR;
        Token *newTokens = (Token *)realloc(lexer->tokens, sizeof(Token) * newCapacity);
        if (newTokens == NULL) {
            return false;
        }
        lexer->tokens = newTokens;
        lexer->capacity = newCapacity;
    }

    lexer->tokens[lexer->size++] = token;
    return true;
}

extern Lexer *create_lexer(size_t capacity) {
    Lexer *lexerPtr = (Lexer *)malloc(sizeof(Lexer));
    if (lexerPtr == NULL) {
        return NULL;
    }

    lexerPtr->tokens = (Token *)malloc(sizeof(Token) * capacity);
    if (lexerPtr->tokens == NULL) {
        free(lexerPtr);
        return NULL;
    }

    lexerPtr->capacity = capacity;
    lexerPtr->size = 0;

    return lexerPtr;
}


extern void destroy_lexer(Lexer *lexer) {
    if (lexer == NULL) {
        return;
    }

    free(lexer->tokens);
    free(lexer);
}

extern TokenizationResult tokenize(Lexer *lexer, char *input) {
    if (lexer == NULL || input == NULL) {
        return TOKENIZE_INVALID_INPUT;
    }

    unsigned char character;
    size_t charPtr = 0;

    while ((character = input[charPtr++]) != '\0') {
        Token token;

        switch (character)
        {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                token = create_token((OpCodeType)character, charPtr);
                break;

            default:
                // Not supported characters are handled as comments
                continue;
        }

        if (!add_token(lexer, token)) {
            return TOKENIZE_ADD_TOKEN_FAILED;
        }
    }
    
    return TOKENIZE_SUCCESS;
}