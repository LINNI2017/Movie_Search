all: mt_search

mt_search: mt_search.c
	gcc -pthread -o mt_search mt_search.c

run: mt_search
	./mt_search inputs/input1.txt 3 3 11

run_input_2: mt_search
	./mt_search inputs/input2.txt 3 3 26

run_input_3: mt_search
	./mt_search inputs/input3.txt 3 3 138

run_input_4: mt_search
	./mt_search inputs/input4.txt 3 3 3069

run_valgrind: mt_search
	valgrind --leak-check=full ./mt_search inputs/input1.txt 3 3 11

run_valgrind_2: mt_search
	valgrind --leak-check=full ./mt_search inputs/input2.txt 3 3 26

run_valgrind_3: mt_search
	valgrind --leak-check=full ./mt_search inputs/input3.txt 3 3 138

run_valgrind_4: mt_search
	valgrind --leak-check=full ./mt_search inputs/input4.txt 3 3 3069

clean:
	rm mt_search
