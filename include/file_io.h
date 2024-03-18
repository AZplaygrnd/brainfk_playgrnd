#ifndef FILE_IO_IMPL_H
#define FILE_IO_IMPL_H

typedef enum {
    FILE_IO_RESULT_OK = 0,
    FILE_IO_RESULT_ERROR = 1,
} FILE_IO_RESULT_CODE;

extern FILE_IO_RESULT_CODE read_file(const char *path, char **buffer, size_t *fileSize);

#endif