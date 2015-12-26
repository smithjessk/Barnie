CXX = clang++

CXX_FLAGS = -std=c++11

LLVM_CC_FLAGS = `llvm-config-3.6 --cxxflags`
LLVM_LINK_FLAGS = `llvm-config-3.6 --ldflags`

TESTS = ast_tests.cc

.PHONY: tests

all: compiler tests

compiler:
	mkdir -p bin

tests:
	for test in $(TESTS) ; do \
		mkdir -p bin/; \
		$(CXX) $(CXX_FLAGS) $(LLVM_CC_FLAGS) $(LLVM_LINK_FLAGS) -o bin/$$test tests/$$test; \
	done