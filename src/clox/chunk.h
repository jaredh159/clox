#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_ADD,
  OP_CALL,
  OP_CLOSE_UPVALUE,
  OP_CLOSURE,
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_DEFINE_GLOBAL,
  OP_DIVIDE,
  OP_EQUAL,
  OP_FALSE,
  OP_GET_GLOBAL,
  OP_GET_LOCAL,
  OP_GET_UPVALUE,
  OP_GREATER,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LESS,
  OP_LOOP,
  OP_MULTIPLY,
  OP_NEGATE,
  OP_NIL,
  OP_NOT,
  OP_POP,
  OP_PRINT,
  OP_RETURN,
  OP_SET_GLOBAL,
  OP_SET_LOCAL,
  OP_SET_UPVALUE,
  OP_SUBTRACT,
  OP_TRUE,
} op_code;

typedef struct {
  int count;
  int capacity;
  int* lines;
} lines_t;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  lines_t lines;
  value_array_t constants;
} chunk_t;

void init_chunk(chunk_t* chunk);
void free_chunk(chunk_t* chunk);
void write_chunk(chunk_t* chunk, uint8_t byte, int line);
int add_constant(chunk_t* chunk, value_t value);
int get_line(chunk_t* chunk, int offset);
void write_constant(chunk_t* chunk, value_t value, int line);
void print_encoded_lines(lines_t* lines);

#endif
