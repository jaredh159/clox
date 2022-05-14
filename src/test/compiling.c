#include "test.h"

static void* setup(const param_t params[], void* user_data);
static void tear_down(void* fixture);

extern VM vm;

void assert_clox_number(const char* source, double number);
void assert_clox_bool(const char* source, bool boolean);
void assert_clox_nil(const char* source);
void assert_clox_string(const char* source, const char* expected);

static result_t arithmetic_expressions(const param_t params[], void* fixture) {
  assert_clox_number("2 + 2;", 4);
  assert_clox_number("1 + 2 * 3;", 7);
  assert_clox_number("(-1 + 2) * 3 - -4;", 7);
  assert_clox_number("-2;", -2);
  assert_clox_number("--2;", 2);
  return MUNIT_OK;
}

static result_t literals(const param_t params[], void* fixture) {
  assert_clox_nil("nil;");
  assert_clox_bool("true;", true);
  assert_clox_bool("false;", false);
  return MUNIT_OK;
}

static result_t negation(const param_t params[], void* fixture) {
  assert_clox_bool("!true;", false);
  assert_clox_bool("!!true;", true);
  assert_clox_bool("!false;", true);
  assert_clox_bool("!!false;", false);
  assert_clox_bool("!0;", false);
  assert_clox_bool("!nil;", true);
  return MUNIT_OK;
}

static result_t equality(const param_t params[], void* fixture) {
  assert_clox_bool("true == true;", true);
  assert_clox_bool("false == false;", true);
  assert_clox_bool("false != true;", true);
  assert_clox_bool("false != false;", false);
  assert_clox_bool("1 != 2;", true);
  assert_clox_bool("nil == nil;", true);
  assert_clox_bool("\"foo\" == \"foo\";", true);
  assert_clox_bool("\"foo\" == \"bar\";", false);
  return MUNIT_OK;
}

static result_t comparison(const param_t params[], void* fixture) {
  assert_clox_bool("3 < 4;", true);
  assert_clox_bool("3 <= 4;", true);
  assert_clox_bool("3 <= 3;", true);
  assert_clox_bool("3 <= 2;", false);
  assert_clox_bool("4 > 3;", true);
  assert_clox_bool("4 >= 3;", true);
  assert_clox_bool("4 >= 4;", true);
  assert_clox_bool("4 >= 6;", false);
  return MUNIT_OK;
}

static result_t strings(const param_t params[], void* fixture) {
  assert_clox_string("\"foobar\";", "foobar");
  assert_clox_string("\"foo\" + \"baz\";", "foobaz");
  assert_clox_string("var x = \"foobar\"; x;", "foobar");
  return MUNIT_OK;
}

static result_t global_variables(const param_t params[], void* fixture) {
  assert_clox_string("var x = \"foobar\"; x;", "foobar");
  assert_clox_number("var three = 3; var four = 4; three * four;", 12);
  return MUNIT_OK;
}

static result_t local_variables(const param_t params[], void* fixture) {
  assert_clox_number("var g; { var l = 3; g = l; } g;", 3);
  assert_clox_number(
    "var g; { var shadow = 3; { var shadow = 4; g = shadow; } } g;", 4);
  assert_clox_number(
    "var g; { var shadow = 3; { var shadow = 4; } g = shadow; } g;", 3);
  return MUNIT_OK;
}

// plumbing

static test_t compiling_tests[] = {
  TEST("/arithmetic-exprs", arithmetic_expressions),
  TEST("/literals", literals),
  TEST("/negation", negation),
  TEST("/equality", equality),
  TEST("/comparison", comparison),
  TEST("/strings", strings),
  TEST("/global-variables", global_variables),
  TEST("/local-variables", local_variables),
  TESTS_END,
};

SUITE("/compiling", compiling_suite, compiling_tests);

static void* setup(const param_t params[], void* user_data) {
  init_vm();
  return NULL;
}

static void tear_down(void* fixture) {
  free_vm();
}

void assert_clox_number(const char* source, double number) {
  interpret(source);
  value_t top = vm.stack_top[0];
  assert_int(top.type, ==, VAL_NUMBER);
  assert_double(AS_NUMBER(top), ==, number);
}

void assert_clox_bool(const char* source, bool boolean) {
  interpret(source);
  value_t top = vm.stack_top[0];
  assert_int(top.type, ==, VAL_BOOL);
  if (boolean) {
    assert_true(AS_BOOL(top));
  } else {
    assert_false(AS_BOOL(top));
  }
}

void assert_clox_nil(const char* source) {
  interpret(source);
  value_t top = vm.stack_top[0];
  assert_int(top.type, ==, VAL_NIL);
}

void assert_clox_string(const char* source, const char* expected) {
  interpret(source);
  value_t top = vm.stack_top[0];
  assert_int(top.type, ==, VAL_OBJ);
  assert_string_equal(AS_CSTRING(top), expected);
}
