#define DEBUG_PRINT_VM_RETURN
#define DEBUG_PRINT_CODE
#define DEBUG_TRACE_EXECUTION

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char* read_file(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(ERR_IO);
  }

  fseek(file, 0L, SEEK_END);
  size_t file_size = ftell(file);
  rewind(file);

  char* buffer = malloc(file_size + 1);
  if (buffer == NULL) {
    EXIT(ERR_OUT_OF_MEMORY);
  }

  size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
  if (bytes_read < file_size) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(ERR_IO);
  }

  buffer[bytes_read] = '\0';
  fclose(file);
  return buffer;
}

static void run_file(const char* path) {
  char* source = read_file(path);
  interpret_result_t result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR)
    EXIT(ERR_COMPILE);
  if (result == INTERPRET_RUNTIME_ERROR)
    EXIT(ERR_RUNTIME);
}

int main(int argc, const char* argv[]) {
  init_vm();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(ERR_USAGE);
  }
  free_vm();
  return 0;
}
