#include "chunk.h"
#include "common.h"
#include "debug.h"

int main() {
  chunk_t chunk;
  init_chunk(&chunk);

  int i;
  for (i = 0; i < 258; i++) {
    write_constant(&chunk, i, i / 2 + 1);
  }

  write_chunk(&chunk, OP_RETURN, i / 2 + 2);

  disassemble_chunk(&chunk, "test chunk");
  free_chunk(&chunk);
  return 0;
}
