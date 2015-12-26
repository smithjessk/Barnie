#ifndef AST_H
#define AST_H

#include <vector>
#include <string>
#include <memory>

namespace barnie {

// Base class for all AST nodes
struct expr_ast {
 public:
  virtual ~expr_ast() {}
};

using expr_ptr = std::unique_ptr<expr_ast>;

struct number_expr_ast : public expr_ast {
  double value;

  number_expr_ast(double v) : value(v) {}
};

struct text_expr_ast : public expr_ast {
  std::string text;

  text_expr_ast(const std::string &s) : text(s) {}
};

struct variable_expr_ast : public expr_ast {
  std::string name;

  variable_expr_ast(std::string n) : name(n) {}
};

struct binary_expr_ast : public expr_ast {
  char op;
  expr_ptr lhs, rhs;

  binary_expr_ast(expr_ptr l, char o, expr_ptr r) 
  : lhs(std::move(l)), op(o), rhs(std::move(r)) {}
};

struct call_expr_ast : public expr_ast {
  std::string callee;
  std::vector<expr_ptr> args;

  call_expr_ast(const std::string &c, std::vector<expr_ptr> a)
   : callee(c), args(std::move(a)) {}
};

// Function name, argument names, and argument types 
struct prototype_ast {
  std::string name;
  std::vector<std::string> args;
  std::vector<std::string> types;

  prototype_ast(const std::string &n, std::vector<std::string> a, 
    std::vector<std::string> t)
    : name(n), args(a), types(t) {}
};

struct function_ast {
  std::unique_ptr<prototype_ast> prototype;
  expr_ptr body;

  function_ast(std::unique_ptr<prototype_ast> p, expr_ptr b)
    : prototype(std::move(p)), body(std::move(b)) {}
};

} // namespace barnie

#endif // AST_H