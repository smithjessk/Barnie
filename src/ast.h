#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/Value.h>

namespace barnie {

// Base class for all AST nodes
struct expr_ast {
 public:
  virtual ~expr_ast() {}
  virtual llvm::Value *codegen() = 0;
};

using expr_ptr = std::unique_ptr<expr_ast>;

struct number_expr_ast : public expr_ast {
  double value;

  number_expr_ast(double v) : value(v) {}
  virtual llvm::Value *codegen();
};

struct text_expr_ast : public expr_ast {
  std::string text;

  text_expr_ast(const std::string &s) : text(s) {}
  virtual llvm::Value *codegen();
};

struct variable_expr_ast : public expr_ast {
  std::string type;
  std::string name;

  variable_expr_ast(std::string t, std::string n) : type(t), name(n) {}
  virtual llvm::Value *codegen();
};

struct binary_expr_ast : public expr_ast {
  char op;
  expr_ptr lhs, rhs;

  binary_expr_ast(expr_ptr l, char o, expr_ptr r) 
    : lhs(std::move(l)), op(o), rhs(std::move(r)) {}
  virtual llvm::Value *codegen();
};

struct call_expr_ast : public expr_ast {
  std::string name;
  std::vector<expr_ptr> args;

  call_expr_ast(const std::string &n, std::vector<expr_ptr> a)
   : name(n), args(std::move(a)) {}
  virtual llvm::Value *codegen();
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