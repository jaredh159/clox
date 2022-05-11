#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_ADD,
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_DEFINE_GLOBAL,
  OP_DIVIDE,
  OP_EQUAL,
  OP_FALSE,
  OP_GET_GLOBAL,
  OP_GREATER,
  OP_LESS,
  OP_MULTIPLY,
  OP_NEGATE,
  OP_NIL,
  OP_NOT,
  OP_POP,
  OP_PRINT,
  OP_RETURN,
  OP_SET_GLOBAL,
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
