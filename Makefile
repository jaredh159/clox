FLAGS = -Wall -Wextra -Werror -pedantic -std=c11

clox:
	cc -o ./.build/clox ./src/clox/main.c ./src/clox/chunk.c ./src/clox/memory.c ./src/clox/debug.c
