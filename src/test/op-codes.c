#include "test.h"

static void* setup(const param_t params[], void* user_data);
static void tear_down(void* fixture);

static result_t op_long(const param_t params[], void* fixture) {
  chunk_t* chunk = fixture;
  for (int i = 0; i < 256; i++) {
    write_constant(chunk, NUMBER_VAL(i), 1);
  }

  // last non-long op code
  assert_int(chunk->code[chunk->count - 2], ==, OP_CONSTANT);
  assert_int(chunk->code[chunk->count - 1], ==, 255);

  // should be long opcode
  int count_before_long = chunk->count;
  write_constant(chunk, NUMBER_VAL(1), 2);
  assert_int(chunk->count, ==, count_before_long + 4);
  assert_int(chunk->code[chunk->count - 4], ==, OP_CONSTANT_LONG);
  // 0x0 0x1 0x0 is 256 when reassembled
  assert_int(chunk->code[chunk->count - 3], ==, 0x0);
  assert_int(chunk->code[chunk->count - 2], ==, 0x1);
  assert_int(chunk->code[chunk->count - 1], ==, 0x0);

  return MUNIT_OK;
}

// plumbing

static test_t op_codes_tests[] = {
  TEST("/OP_CONSTANT_LONG", op_long),
  TESTS_END,
};

SUITE("/op-codes", op_code_suite, op_codes_tests);

static void* setup(const param_t params[], void* user_data) {
  chunk_t* chunk = malloc(sizeof(chunk_t));
  init_chunk(chunk);
  return chunk;
}

static void tear_down(void* fixture) {
  free(fixture);
}
