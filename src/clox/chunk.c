#include "chunk.h"
#include <stdlib.h>
#include "memory.h"

void init_chunk(chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
}

void write_chunk(chunk* chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int old_capacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_capacity);
    chunk->code =
      GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
  }

  chunk->code[chunk->count++] = byte;
}

void free_chunk(chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  init_chunk(chunk);
}
