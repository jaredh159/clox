#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
  OP_RETURN,
} op_code;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
} chunk;

void init_chunk(chunk* chunk);
void free_chunk(chunk* chunk);
void write_chunk(chunk* chunk, uint8_t byte);

#endif
