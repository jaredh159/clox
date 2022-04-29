#include "test.h"

static void* setup(const param_t params[], void* user_data);
static void tear_down(void* fixture);

static void assert_token(
  token_t token, token_type_t type, const char* lexeme, int line) {
  assert_int(token.type, ==, type);
  char token_lexeme[token.length];
  token_lexeme[token.length] = '\0';
  strncpy(token_lexeme, token.start, token.length);
  assert_string_equal(token_lexeme, lexeme);
  assert_int(token.line, ==, line);
}

static result_t simple_tokens(const param_t params[], void* fixture) {
  init_scanner("( ) { } ; , . - + / * ! != < <= > \n>=");
  assert_token(scan_token(), TOKEN_LEFT_PAREN, "(", 1);
  assert_token(scan_token(), TOKEN_RIGHT_PAREN, ")", 1);
  assert_token(scan_token(), TOKEN_LEFT_BRACE, "{", 1);
  assert_token(scan_token(), TOKEN_RIGHT_BRACE, "}", 1);
  assert_token(scan_token(), TOKEN_SEMICOLON, ";", 1);
  assert_token(scan_token(), TOKEN_COMMA, ",", 1);
  assert_token(scan_token(), TOKEN_DOT, ".", 1);
  assert_token(scan_token(), TOKEN_MINUS, "-", 1);
  assert_token(scan_token(), TOKEN_PLUS, "+", 1);
  assert_token(scan_token(), TOKEN_SLASH, "/", 1);
  assert_token(scan_token(), TOKEN_STAR, "*", 1);
  assert_token(scan_token(), TOKEN_BANG, "!", 1);
  assert_token(scan_token(), TOKEN_BANG_EQUAL, "!=", 1);
  assert_token(scan_token(), TOKEN_LESS, "<", 1);
  assert_token(scan_token(), TOKEN_LESS_EQUAL, "<=", 1);
  assert_token(scan_token(), TOKEN_GREATER, ">", 1);
  assert_token(scan_token(), TOKEN_GREATER_EQUAL, ">=", 2);
  assert_token(scan_token(), TOKEN_EOF, "", 2);
  return MUNIT_OK;
}

static result_t comments(const param_t params[], void* fixture) {
  init_scanner("+ // foo bar baz\n-");
  assert_token(scan_token(), TOKEN_PLUS, "+", 1);
  assert_token(scan_token(), TOKEN_MINUS, "-", 2);
  assert_token(scan_token(), TOKEN_EOF, "", 2);
  return MUNIT_OK;
}

static result_t strings(const param_t params[], void* fixture) {
  init_scanner("\"foobar\" \"error - not terminated");
  assert_token(scan_token(), TOKEN_STRING, "\"foobar\"", 1);
  assert_token(scan_token(), TOKEN_ERROR, "Unterminated string.", 1);
  assert_token(scan_token(), TOKEN_EOF, "", 1);
  return MUNIT_OK;
}

static result_t numbers(const param_t params[], void* fixture) {
  init_scanner("123 345.67");
  assert_token(scan_token(), TOKEN_NUMBER, "123", 1);
  assert_token(scan_token(), TOKEN_NUMBER, "345.67", 1);
  assert_token(scan_token(), TOKEN_EOF, "", 1);
  return MUNIT_OK;
}

static result_t keywords(const param_t params[], void* fixture) {
  init_scanner(
    "and class else if nil or print return "
    "super var while false for fun this true");
  assert_token(scan_token(), TOKEN_AND, "and", 1);
  assert_token(scan_token(), TOKEN_CLASS, "class", 1);
  assert_token(scan_token(), TOKEN_ELSE, "else", 1);
  assert_token(scan_token(), TOKEN_IF, "if", 1);
  assert_token(scan_token(), TOKEN_NIL, "nil", 1);
  assert_token(scan_token(), TOKEN_OR, "or", 1);
  assert_token(scan_token(), TOKEN_PRINT, "print", 1);
  assert_token(scan_token(), TOKEN_RETURN, "return", 1);
  assert_token(scan_token(), TOKEN_SUPER, "super", 1);
  assert_token(scan_token(), TOKEN_VAR, "var", 1);
  assert_token(scan_token(), TOKEN_WHILE, "while", 1);
  assert_token(scan_token(), TOKEN_FALSE, "false", 1);
  assert_token(scan_token(), TOKEN_FOR, "for", 1);
  assert_token(scan_token(), TOKEN_FUN, "fun", 1);
  assert_token(scan_token(), TOKEN_THIS, "this", 1);
  assert_token(scan_token(), TOKEN_TRUE, "true", 1);
  assert_token(scan_token(), TOKEN_EOF, "", 1);
  return MUNIT_OK;
}

// plumbing

static test_t tests[] = {
  TEST("/simple-tokens", simple_tokens),
  TEST("/comments", comments),
  TEST("/strings", strings),
  TEST("/numbers", numbers),
  TEST("/keywords", keywords),
  TESTS_END,
};

SUITE("/scanning", scanning_suite, tests);

static void* setup(const param_t params[], void* user_data) {
  return NULL;
}

static void tear_down(void* fixture) {
}
