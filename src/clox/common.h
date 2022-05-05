#ifndef clox_common_h
#define clox_common_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG_PRINT_VM_RETURN
// #define DEBUG_PRINT_CODE
// #define DEBUG_TRACE_EXECUTION

#define EXIT(code)                               \
  fprintf(stderr, "\x1b[31m" #code "\x1b[0m\n"); \
  exit((code))

typedef enum {
  ERR_OUT_OF_MEMORY = 1,
  ERR_GET_LINE,
  ERR_COMPILE,
  ERR_RUNTIME,
  ERR_USAGE = 64,
  ERR_IO = 74,
} error_t;

#endif
