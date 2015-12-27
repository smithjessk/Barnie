#ifndef CODEGEN_H
#define CODEGEN_H

#include <memory>
#include <map>
#include <string>
#include <sstream>

#include "ast.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/ErrorHandling.h>

namespace barnie {
  static std::unique_ptr<llvm::Module> *module;
  static llvm::IRBuilder<> builder(llvm::getGlobalContext());
  static std::map<std::string, llvm::Value *> named_values;

  llvm::Value *error_v(const std::string str) {
    llvm::report_fatal_error(str, true);
    return nullptr;
  }

  llvm::Value *number_expr_ast::codegen() {
    return llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat(value));
  }

  llvm::Value *text_expr_ast::codegen() {
    return llvm::ConstantDataSequential::get(llvm::getGlobalContext(), 
      llvm::StringRef(text));
  }

  llvm::Value *variable_expr_ast::codegen() {
    llvm::Value *v = named_values[name];
    if (!v) return error_v("Unknown variable name " + name);
    return v;
  }

  llvm::Value *binary_expr_ast::codegen() {
    llvm::Value *l = lhs->codegen();
    llvm::Value *r = rhs->codegen();
    if (!l) return error_v("No LHS expression for binary operation");
    if (!r) return error_v("No RHS expression for binary operation");

    switch (op) {
      case '+':
        return builder.CreateFAdd(l, r, "addtmp");
      case '-':
        return builder.CreateFSub(l, r, "subtmp");
      case '*':
        return builder.CreateFMul(l, r, "multmp");
      case '/':
        return builder.CreateFDiv(l, r, "divtmp");
      default:
        std::stringstream ss;
        ss << "Invalid binary operator: ";
        ss << op;
        std::string error_msg;
        ss >> error_msg;
        return error_v(error_msg);
    }
  }

  llvm::Value *call_expr_ast::codegen() {
    llvm::Function *function = module->getFunction(name);
    if (!function) return error_v("No function named " + name);

    if (function->arg_size() != args.size()) {
      return error_v("Incorrect number of arguments passed");
    }

    std::vector<llvm::Value *> args_vec;
    for (size_t i = 0; i != args.size(); ++i) {
      args_vec.push_back(args[i]->codegen());
      if (!args_vec.back()) {
        return nullptr;
      }
    }

    return builder.CreateCall(function, args_vec, "calltmp");
  }
} // namespace barnie

#endif // CODEGEN_H