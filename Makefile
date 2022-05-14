FLAGS = -Wall -Wextra -g -Werror -Wno-unused-variable -Wno-unused-parameter -pedantic -Wno-unused-function -std=c11

.SILENT: test runtests testwatch clox run

clox:
	cc -o ./.build/clox \
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
	$(FLAGS)

run:
	make && ./.build/clox

scratch:
	make && ./.build/clox scratch.lox

test:
	cc -o ./.build/test \
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
	$(FLAGS)

runtests:
	clear; make test && ./.build/test --fatal-failures --show-stderr; printf "\n"

testwatch:
	watchexec --restart --watch src --exts c,h --signal SIGINT make runtests
