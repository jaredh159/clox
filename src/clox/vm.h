#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  chunk_t* chunk;
  uint8_t* ip;
  value_t stack[STACK_MAX];
  value_t* stack_top;
  table_t strings;
  obj_t* objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} interpret_result_t;

extern VM vm;

value_t vm_last_value;
void init_vm();
void free_vm();
interpret_result_t interpret(const char* source);
void push(value_t value);
value_t pop();

#endif
