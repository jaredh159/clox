#include "test.h"

extern suite_t line_encoding_suite;
extern suite_t op_code_suite;
extern suite_t scanning_suite;

suite_t suites[3];

suite_t main_suite = {
  .prefix = "clox",
  .tests = NULL,
  .suites = NULL,
  .iterations = 1,
  .options = MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char* argv[]) {
  suites[0] = line_encoding_suite;
  suites[1] = op_code_suite;
  suites[2] = scanning_suite;
  main_suite.suites = suites;
  return munit_suite_main(&main_suite, NULL, argc, argv);
}
