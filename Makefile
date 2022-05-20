clox:
	cc -o $(BIN) \
	./src/clox/main.c \
	./src/clox/chunk.c \
	./src/clox/memory.c \
	./src/clox/debug.c \
	./src/clox/value.c \
	./src/clox/compiler.c \
	./src/clox/scanner.c \
	./src/clox/object.c \
	./src/clox/table.c \
	./src/clox/vm.c \
	$(FLAGS) $(DEBUG)

clox-debug:
	make DEBUG=-DDEBUG clox

run: clox
	$(BIN)

run-debug: clox-debug
	$(BIN)

scratch: clox
	$(BIN) scratch.lox

scratch-debug: clox-debug
	$(BIN) scratch.lox

test:
	cc -o $(TEST) \
	./src/test/test.c \
	./src/test/op-codes.c \
	./src/test/line-encoding.c \
	./src/test/scanning.c \
	./src/test/compiling.c \
	./src/test/munit/munit.c \
	./src/clox/chunk.c \
	./src/clox/vm.c \
	./src/clox/table.c \
	./src/clox/object.c \
	./src/clox/value.c \
	./src/clox/memory.c \
	./src/clox/compiler.c \
	./src/clox/scanner.c \
	./src/clox/debug.c \
	$(FLAGS) -DTESTING

runtests:
	clear; make test && $(TEST) --fatal-failures --show-stderr; printf "\n"

testwatch:
	watchexec --restart --watch src --exts c,h --signal SIGINT make runtests

clean:
	rm -rf ./.build
	mkdir ./.build

# helpers

BIN := ./.build/clox
TEST := ./.build/test
FLAGS := -Wall -Wextra -g -Werror -Wno-unused-variable -Wno-unused-parameter -pedantic -Wno-unused-function -std=c11
.SILENT: test runtests testwatch clox run scratch scratch-debug run-debug clox-debug clean
.PHONY: runtests testwatch clox-debug clox clean
