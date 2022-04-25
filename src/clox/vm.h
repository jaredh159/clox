#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  chunk_t* chunk;
  uint8_t* ip;
  value_t stack[STACK_MAX];
  value_t* stack_top;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} interpret_result;

void init_vm();
void free_vm();
interpret_result interpret(chunk_t* chunk);
void push(value_t value);
value_t pop();

#endif