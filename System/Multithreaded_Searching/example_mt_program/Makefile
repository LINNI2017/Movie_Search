all: example

example: example.c
	gcc -pthread -o example example.c

run: example
	./example

run_valgrind: example
	valgrind --leak-check=full ./example

clean:
	rm example
