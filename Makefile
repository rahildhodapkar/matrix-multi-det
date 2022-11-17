all: matrix
matrix: matrix.c
	gcc -g -Wall -Werror -fsanitize=address -std=c11 matrix.c -o matrix
clean:
	rm -rf matrix
