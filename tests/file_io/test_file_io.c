#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_io.h"
#include "test_file_io.h"

static void test_read_file(char *filePath, const size_t expectedContentSize, const char *expectedContent) {
    char *contentBuffer;
    size_t contentSize;

    int result = read_file(filePath, &contentBuffer, &contentSize);

    assert(result == FILE_IO_RESULT_OK);
    assert(contentSize == expectedContentSize);
    assert(strcmp(contentBuffer, expectedContent) == 0);

    free(contentBuffer);

    fprintf(stdout, "test_read_file(%s) has passed!\n", filePath);
}

extern void test_file_io_run(void) {
    test_read_file("./tests/file_io/0_example.txt", 12, "Hello World!");
    test_read_file("./tests/file_io/1_example.txt", 409, "Lorem ipsum dolor sit amet, consetetur sadipscing elitr.\n\
At vero eos et accusam et justo duo dolores et ea rebum.\n\
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\n\
At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren,\n\
no sea takimata sanctus est Lorem ipsum dolor sit amet.");
}