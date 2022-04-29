#ifndef clox_test_h
#define clox_test_h

#define MUNIT_ENABLE_ASSERT_ALIASES

#include <stdio.h>
#include <stdlib.h>
#include "../clox/chunk.h"
#include "../clox/common.h"
#include "../clox/compiler.h"
#include "../clox/debug.h"
#include "../clox/memory.h"
#include "../clox/scanner.h"
#include "../clox/value.h"
#include "munit/munit.h"

typedef MunitTestFunc test_fn_t;
typedef MunitTest test_t;
typedef MunitSuite suite_t;
typedef MunitParameter param_t;
typedef MunitResult result_t;

#define TESTS_END \
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define test_case(name) \
  result_t name(const param_t params[], void* user_data_or_fixture)

#define TEST(test_name, fn)                                                    \
  {                                                                            \
    .name = (test_name), .test = (fn), .setup = setup, .tear_down = tear_down, \
    .options = MUNIT_TEST_OPTION_NONE, .parameters = NULL,                     \
  }

#define SUITE(suite_slug, suite_name, tests_name) \
  const suite_t suite_name = {                    \
    .prefix = (suite_slug),                       \
    .tests = (tests_name),                        \
    .suites = NULL,                               \
    .iterations = 1,                              \
    .options = MUNIT_SUITE_OPTION_NONE,           \
  }

#endif
