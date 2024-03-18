#!/bin/bash

set -xe
gcc src\\*.c src\\lib\\*.c -I.\\include -o .\\bin\\win-interpreter.exe -std=c99 -Wall -Wextra -pedantic