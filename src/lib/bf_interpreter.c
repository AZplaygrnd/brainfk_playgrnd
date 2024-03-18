#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bf_lexer.h"
#include "bf_parser.h"

typedef struct {
    unsigned char *cells;
    size_t capacity; 
    size_t dataPtr;
} VirtualMemory;

static VirtualMemory *create_virtual_memory(size_t capacity) {
    VirtualMemory *vm = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    vm->capacity = capacity;
    vm->dataPtr = capacity / 2;
    vm->cells = (unsigned char *)malloc(sizeof(unsigned char) * capacity);
    
    for (size_t i = 0; i < capacity; ++i) {
        vm->cells[i] = 0;
    }

    return vm; 
}

static void destroy_virtual_memory(VirtualMemory *vm) {
    if (vm == NULL) {
        return;
    }

    free(vm->cells);
    free(vm);
}

void interpret(ASTNode *root, size_t capacity) {
    VirtualMemory *vm = create_virtual_memory(capacity);

    while (root != NULL) {
        switch (root->type)
        {
            case NODE_INCREMENT_PTR:
                ++(vm->dataPtr);
                break;
            case NODE_DECREMENT_PTR:
                --(vm->dataPtr);
                break;
            case NODE_INCREMENT_VAL:
                ++(vm->cells[vm->dataPtr]);
                break;
            case NODE_DECREMENT_VAL:
                --(vm->cells[vm->dataPtr]);
                break;
            case NODE_OUTPUT:
                putchar(vm->cells[vm->dataPtr]);
                break;
            case NODE_INPUT:
                vm->cells[vm->dataPtr] = getchar();
                break;
            case NODE_LOOP_START:
                if (vm->cells[vm->dataPtr] == 0) {
                    root = root->jumpRef;
                }
                break;
            case NODE_LOOP_END:
                if (vm->cells[vm->dataPtr] != 0) {
                    root = root->jumpRef;
                }
                break;

            default:
                break;
        }

        root = root->next;
    }

    destroy_virtual_memory(vm);
}