CXX = clang++

CXX_FLAGS = -std=c++11

LLVM_FLAGS = -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS 

LLVM_CC_FLAGS = `llvm-config--cxxflags`
LLVM_LINK_FLAGS = `llvm-config --ldflags`

TESTS = ast_tests.cc

.PHONY: tests

all: compiler tests

compiler:
	mkdir -p bin

tests:
	for test in $(TESTS) ; do \
		mkdir -p bin/; \
		$(CXX) $(LLVM_FLAGS) $(CXX_FLAGS) $(LLVM_CC_FLAGS) $(LLVM_LINK_FLAGS) -o bin/$$test tests/$$test; \
	done