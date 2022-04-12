#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double value_t;

typedef struct {
  int capacity;
  int count;
  value_t* values;
} value_array_t;

void print_value(value_t value);
void init_value_array(value_array_t* values);
void free_value_array(value_array_t* values);
void write_value_array(value_array_t* values, value_t value);

#endif
