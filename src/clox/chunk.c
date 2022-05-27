#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "memory.h"
#include "vm.h"

static void init_lines(lines_t* array);
static void encode_line(lines_t* array, int line);
static void free_lines(lines_t* array);

void init_chunk(chunk_t* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  init_lines(&chunk->lines);
  init_value_array(&chunk->constants);
}

void write_chunk(chunk_t* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int old_cap = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_cap);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_cap, chunk->capacity);
  }

  encode_line(&chunk->lines, line);

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

void free_chunk(chunk_t* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  free_lines(&chunk->lines);
  free_value_array(&chunk->constants);
  init_chunk(chunk);
}

void write_constant(chunk_t* chunk, value_t value, int line) {
  write_value_array(&chunk->constants, value);
  int index = chunk->constants.count - 1;
  if (index > 255) {
    write_chunk(chunk, OP_CONSTANT_LONG, line);
    write_chunk(chunk, (index >> 16) & 0xff, line);
    write_chunk(chunk, (index >> 8) & 0xff, line);
    write_chunk(chunk, index & 0xff, line);
  } else {
    write_chunk(chunk, OP_CONSTANT, line);
    write_chunk(chunk, index, line);
  }
}

int add_constant(chunk_t* chunk, value_t value) {
  push(value);
  write_value_array(&chunk->constants, value);
  pop();
  return chunk->constants.count - 1;
}

int get_line(chunk_t* chunk, int offset) {
  int total_offsets = 0;
  for (int i = 0; i < chunk->lines.count; i++) {
    total_offsets += chunk->lines.lines[i];
    if (offset < total_offsets) {
      return i + 1;
    }
  }
  EXIT(ERR_GET_LINE);
}

static void init_lines(lines_t* array) {
  array->lines = NULL;
  array->capacity = 0;
  array->count = 0;
}

void print_encoded_lines(lines_t* lines) {
  printf("\n\ncount: %d\ncapacity: %d\n", lines->count, lines->capacity);
  for (int i = 0; i < lines->count; i++) {
    printf("index: %d, line: %d, num_offsets: %d\n", i, i + 1, lines->lines[i]);
  }
  printf("\n");
}

static void encode_line(lines_t* array, int line) {
  if (array->capacity < line) {
    int old_cap = array->capacity;
    array->capacity = GROW_CAPACITY(old_cap);
    array->lines = GROW_ARRAY(int, array->lines, old_cap, array->capacity);
    for (int i = old_cap; i < array->capacity; i++) {
      array->lines[i] = 0;
    }
    if (array->capacity < line) {
      encode_line(array, line);
      return;
    }
  }

  array->count = line;
  array->lines[line - 1]++;
}

static void free_lines(lines_t* array) {
  FREE_ARRAY(int, array->lines, array->capacity);
  init_lines(array);
}
