# Multithreaded Searching

```
Create a program that will use multiple threads to search for a target value 
in an array of ints, which are read in from a file. 
```


### Clint.py style check
```
./clint.py *.c *.h
```
```
Done processing mt_search.c
Done processing mt_search.h
Total errors found: 0
```

### Sample output
```
make run
```
```
./mt_search inputs/input1.txt 3 3 11
```
```
Start program...

3 threads spawned
3 threads joined

Summary:
target is found at line: 4
target is found at line: 11
target is found at line: 8

End program
```

```
make run_input_2
```
```
./mt_search inputs/input2.txt 3 3 26
```
```
Start program...

3 threads spawned
3 threads joined

Summary:
target is found at line: 11
target is found at line: 12
target is found at line: 13
target is found at line: 14
target is found at line: 15

End program
```

### Valgrind memory check
```
make run_valgrind
```
```
valgrind --leak-check=full ./mt_search inputs/input1.txt 3 3 11
```
```
==10161== 
==10161== HEAP SUMMARY:
==10161==     in use at exit: 0 bytes in 0 blocks
==10161==   total heap usage: 8 allocs, 8 frees, 6,576 bytes allocated
==10161== 
==10161== All heap blocks were freed -- no leaks are possible
==10161== 
==10161== For counts of detected and suppressed errors, rerun with: -v
==10161== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
make run_valgrind_2
```
```
valgrind --leak-check=full ./mt_search inputs/input2.txt 3 3 26
```
```
==10166== 
==10166== HEAP SUMMARY:
==10166==     in use at exit: 0 bytes in 0 blocks
==10166==   total heap usage: 8 allocs, 8 frees, 6,696 bytes allocated
==10166== 
==10166== All heap blocks were freed -- no leaks are possible
==10166== 
==10166== For counts of detected and suppressed errors, rerun with: -v
==10166== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
make run_valgrind_3
```
```
valgrind --leak-check=full ./mt_search inputs/input3.txt 3 3 138
```
```
==10143== 
==10143== HEAP SUMMARY:
==10143==     in use at exit: 0 bytes in 0 blocks
==10143==   total heap usage: 8 allocs, 8 frees, 31,040 bytes allocated
==10143== 
==10143== All heap blocks were freed -- no leaks are possible
==10143== 
==10143== For counts of detected and suppressed errors, rerun with: -v
==10143== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


* ```nums10000.txt``` is a sample data file that contains 10,000 numbers in the range 0 - 999.
* ```example_mt_program``` is a folder that contains some example threading code. It creates 8 threads and shows the difference between using a semaphore for synchronization and not.

To generate your own number file, you can run:

```shuf -i 0-999 -n 100 > nums.txt```

Where in this example, 100 numbers are being generated (between 0 and 999) and output into a file called ```num.txt```

