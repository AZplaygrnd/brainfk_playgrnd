#include <corecrt.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

extern FILE_IO_RESULT_CODE read_file(const char *path, char **buffer, size_t *fileSize) {
    FILE *filePtr;

    filePtr = fopen(path, "rb");
    if (filePtr == NULL) {
        return FILE_IO_RESULT_ERROR;
    }

    if (fseek(filePtr, 0, SEEK_END) != 0) {
        fclose(filePtr);
        return FILE_IO_RESULT_ERROR;
    }
    *fileSize = ftell(filePtr);
    rewind(filePtr);

    *buffer = (char *)malloc(*fileSize + 1);
    if (*buffer == NULL) {
        fclose(filePtr);
        return FILE_IO_RESULT_ERROR;
    }

    size_t bytesRead = fread(*buffer, 1, *fileSize, filePtr);
    if (bytesRead != *fileSize) {
        fclose(filePtr);
        free(*buffer);
        return FILE_IO_RESULT_ERROR;
    }

    (*buffer)[*fileSize] = '\0';

    fclose(filePtr);
    return FILE_IO_RESULT_OK;
}