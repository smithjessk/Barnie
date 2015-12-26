#include <assert.h>

#include "../src/ast.h"

void number_ast_test() {
  auto number = new barnie::number_expr_ast(5);
  assert(number->value == 5);
  std::printf("Passed number_ast_test\n");
}

int main() {
  number_ast_test();
  std::printf("Passed all tests\n");
  return 0;
}