CXX = clang++

CXX_FLAGS = -std=c++11

LLVM_CC_FLAGS = `llvm-config --cxxflags`
LLVM_LINK_FLAGS = `llvm-config --ldflags`

TESTS = ast_tests.cc codegen_tests.cc

.PHONY: tests

all: compiler tests

compiler:
	mkdir -p bin

tests:
	for test in $(TESTS) ; do \
		mkdir -p bin/; \
		$(CXX) $(CXX_FLAGS) -o bin/$$test tests/$$test; \
	done