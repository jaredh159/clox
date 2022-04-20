#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_RETURN,
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
