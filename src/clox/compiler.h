#ifndef clox_compiler_h
#define clox_compiler_h

#include "object.h"
#include "vm.h"

obj_function_t* compile(const char* source);
void mark_compiler_roots();

#endif
