#include "test_file_io.h"
#include "test_lexer.h"
#include "test_parser.h"

int main(void) {
    test_file_io_run();
    test_lexer_run();
    test_parser_run();

    return 0;
}