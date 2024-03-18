#ifndef FILE_IO_IMPL_H
#define FILE_IO_IMPL_H

extern enum {
    FILE_IO_RESULT_OK = 0,
    FILE_IO_RESULT_ERROR = 1,
} FILE_IO_RESULT_CODE;

extern int read_file(const char *path, char **buffer, size_t *fileSize);

#endif