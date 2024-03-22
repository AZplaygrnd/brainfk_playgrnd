#!/bin/bash

INCLUDE_PATH="./include"
TEST_INCLUDE_PATH="./tests"

SRC_FILES=$(find "./src/lib" -name '*.c')
TEST_SRC_FILES=$(find "./tests" -name '*.c')

TARGET="./bin/test_runner.bin"

gcc -std=c99 -Wall -Wextra -pedantic -I$INCLUDE_PATH -I$TEST_INCLUDE_PATH $SRC_FILES $TEST_SRC_FILES -o $TARGET

if [ $? -eq 0 ]; then
    $TARGET
else
    echo "Compilation failed"
    exit 1
fi