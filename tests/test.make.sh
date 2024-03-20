#!/bin/bash

INCLUDE_PATH="../include"
TEST_INCLUDE_PATH="./"

SRC_FILES=$(find "../src/lib" -name '*.c')
TEST_SRC_FILES=$(find "./" -name '*.c')

TARGET="./test_runner.exe"

gcc -std=c99 -Wall -Wextra -pedantic -I$INCLUDE_PATH -I$TEST_INCLUDE_PATH $SRC_FILES $TEST_SRC_FILES -o $TARGET