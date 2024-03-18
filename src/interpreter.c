#include <stdio.h>
#include <stdlib.h>
#include "bf_lexer.h"
#include "bf_parser.h"
#include "bf_interpreter.h"
#include "file_io.h"

#define CAPACITY 30000

static void printUsage(const char *executable) {
    fprintf(stderr, "\nUsage: %s <filename>\n", executable);
    fprintf(stderr, "\t<filename>: Path to the Brainf*ck source file.\n\n");
}

static int execute(const char *filename) {
    char *buffer;
    size_t bufferSize;

    if (read_file(filename, &buffer, &bufferSize) != FILE_IO_RESULT_OK) {
        fprintf(stderr, "Error: Unable to read the input file: %s.\n", filename);
        return EXIT_FAILURE;
    }

    Lexer *lexer = create_lexer(CAPACITY);
    if (tokenize(lexer, buffer) != TOKENIZE_SUCCESS) {
        fprintf(stderr, "Error: Unable to tokenize the input.\n");
        free(buffer);
        destroy_lexer(lexer);
        return EXIT_FAILURE;
    }

    ASTNode *root = create_ast_from_lexer(lexer);
    if (root == NULL) {
        fprintf(stderr, "Error: Unable to create the AST.\n");
        free(buffer);
        destroy_lexer(lexer);
        return EXIT_FAILURE;
    }

    interpret(root, CAPACITY);

    destroy_ast(root);
    destroy_lexer(lexer);
    free(buffer);

    return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    return execute(argv[1]);
}