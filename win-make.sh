set -xe
gcc src\\*.c -I.\\include -o .\\bin\\win-interpreter.exe -std=c99 -Wall -Wextra -pedantic