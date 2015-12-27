#include <assert.h>

#include "../src/codegen.h"

void number_ast_test() {
  auto number = new barnie::number_expr_ast(5);
  assert(number->value == 5);
  std::printf("Passed number_ast_test\n");
}

void text_ast_test() {
  auto text = new barnie::text_expr_ast("test");
  assert(text->text == "test");
  std::printf("Passed text_expr_ast");
}

int main() {
  number_ast_test();
  text_ast_test();
  std::printf("Passed all tests\n");
  return 0;
}