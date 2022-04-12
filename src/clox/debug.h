#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassemble_chunk(chunk* chunk, const char* name);
int disassemble_instruction(chunk* chunk, int offset);

#endif
