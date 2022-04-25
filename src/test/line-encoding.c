#include "test.h"

static void* setup(const param_t params[], void* user_data);
static void tear_down(void* fixture);

static result_t single_line(const param_t params[], void* fixture) {
  chunk_t* chunk = fixture;
  write_chunk(chunk, OP_RETURN, 1);
  assert_int(chunk->lines.capacity, ==, 8);
  assert_int(chunk->lines.lines[0], ==, 1);
  // should fill all cacacity with zeros so lines can be skipped
  for (int i = 1; i < 8; i++) {
    assert_int(chunk->lines.lines[i], ==, 0);
  }
  return MUNIT_OK;
}

static result_t skipping_lines(const param_t params[], void* fixture) {
  chunk_t* chunk = fixture;
  write_chunk(chunk, OP_RETURN, 3);
  write_chunk(chunk, OP_RETURN, 5);
  assert_int(chunk->lines.lines[2], ==, 1);
  assert_int(get_line(chunk, 0), ==, 3);
  assert_int(get_line(chunk, 1), ==, 5);
  return MUNIT_OK;
}

static result_t repro_example(const param_t params[], void* fixture) {
  chunk_t* chunk = fixture;
  int constant = add_constant(chunk, 1.2);
  write_chunk(chunk, OP_CONSTANT, 123);
  assert_int(get_line(chunk, 0), ==, 123);
  write_chunk(chunk, constant, 123);
  assert_int(get_line(chunk, 1), ==, 123);
  write_chunk(chunk, OP_RETURN, 123);
  assert_int(get_line(chunk, 2), ==, 123);
  return MUNIT_OK;
}

// plumbing

static test_t tests[] = {
  TEST("/single-line", single_line),
  TEST("/skipping-lines", skipping_lines),
  TEST("/repro-example", repro_example),
  TESTS_END,
};

SUITE("/line-encoding", line_encoding_suite, tests);

static void* setup(const param_t params[], void* user_data) {
  chunk_t* chunk = malloc(sizeof(chunk_t));
  init_chunk(chunk);
  return chunk;
}

static void tear_down(void* fixture) {
  free(fixture);
}
