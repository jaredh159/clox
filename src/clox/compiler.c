#include "compiler.h"
#include "common.h"
#include "scanner.h"

void compile(const char* source) {
  init_scanner(source);
  int line = -1;
  for (;;) {
    token_t token = scan_token();
    if (token.line != line) {
      // printf("")
    }
  }
}
