#ifndef BF_LEXER_IMPL_H
#define BF_LEXER_IMPL_H

#include <stddef.h>

typedef enum {
    OP_INCREMENT_PTR = 62,  // '>'
    OP_DECREMENT_PTR = 60,  // '<'
    OP_INCREMENT_VAL = 43,  // '+'
    OP_DECREMENT_VAL = 45,  // '-'
    OP_OUTPUT = 46,         // '.'
    OP_INPUT = 44,          // ','
    OP_LOOP_START = 91,     // '['
    OP_LOOP_END = 93,       // ']'
} OpCodeType;

typedef enum {
    TOKENIZE_SUCCESS,
    TOKENIZE_INVALID_INPUT,
    TOKENIZE_ADD_TOKEN_FAILED
} TokenizationResult;

typedef struct {
    OpCodeType type;
    size_t index;
} Token;

typedef struct {
    Token *tokens;
    size_t capacity;
    size_t size;
} Lexer;

extern Lexer *create_lexer(size_t capacity);
extern void destroy_lexer(Lexer *lexer);
extern TokenizationResult tokenize(Lexer *lexer, char *input);

#endif