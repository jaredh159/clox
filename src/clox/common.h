#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_TRACE_EXECUTION

#define EXIT(code)                               \
  fprintf(stderr, "\x1b[31m" #code "\x1b[0m\n"); \
  exit((code))

typedef enum {
  ERR_OUT_OF_MEMORY = 1,
  ERR_GET_LINE,
} error_t;

#endif
