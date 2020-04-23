#  Multithreading

### BUILD A MULTITHREADED INDEXER

### Large Data Test

#### Better with 20 threads
```
=======OG Parse with 1 thread=========
Took 969.747018 seconds to execute. 
639209 entries in the index.
======================================
```
```
=======MT Parse with 1 thread=========
Took 917.052109 seconds to execute. 
639209 entries in the index.
======================================
```
```
=======MT Parse with 5 threads========
Took 922.134473 seconds to execute. 
639209 entries in the index.
======================================
```
```
=======MT Parse with 10 threads=======
Took 947.782671 seconds to execute. 
639209 entries in the index.
======================================
```
```
=======MT Parse with 20 threads=======
Took 874.872057 seconds to execute. 
639209 entries in the index.
======================================
```

### Sample Test

#### Better with 1 thread
```
=======OG Parse 2 with 1 thread========
Took 0.056624 seconds to execute. 
=======MT Parse 2 with 1 threads=======
Took 0.060860 seconds to execute. 
=======MT Parse 2 with 2 threads=======
Took 0.041956 seconds to execute. 
```

#### Better with 1 thread
```
=======OG Parse 3 with 1 thread========
Took 0.011234 seconds to execute. 
=======MT Parse 3 with 1 thread========
Took 0.010140 seconds to execute. 
=======MT Parse 3 with 2 threads=======
Took 0.010463 seconds to execute. 
=======MT Parse 3 with 3 threads=======
Took 0.045725 seconds to execute. 
```

#### Better with 2 threads 
```
=======OG Parse 4 with 1 thread========
Took 0.014668 seconds to execute. 
=======MT Parse 4 with 1 thread========
Took 0.013226 seconds to execute. 
=======MT Parse 4 with 2 threads=======
Took 0.013702 seconds to execute. 
=======MT Parse 4 with 3 thread========
Took 0.013791 seconds to execute. 
=======MT Parse 4 with 4 threads=======
Took 0.046238 seconds to execute. 
```

#### Better with 3 threads 
```
=======OG Parse 7 with 1 thread========
Took 0.001335 seconds to execute. 
=======MT Parse 7 with 1 thread========
Took 0.001098 seconds to execute. 
=======MT Parse 7 with 2 threads=======
Took 0.000875 seconds to execute. 
=======MT Parse 7 with 3 threads=======
Took 0.000836 seconds to execute. 
=======MT Parse 7 with 4 threads=======
Took 0.000989 seconds to execute. 
=======MT Parse 7 with 5 threads=======
Took 0.001075 seconds to execute. 
=======MT Parse 7 with 6 threads=======
Took 0.001042 seconds to execute. 
=======MT Parse 7 with 7 threads=======
Took 0.001226 seconds to execute. 
```

### 10 files process

#### Better with 1 thread
```
./benchmarker data_tiny/
```
```
Crawled 10 files.
Created DocIdMap
```
```
=======OG Parse with 1 thread=========
Took 0.002134 seconds to execute. 
204 entries in the index.
======================================
```
```
=======MT Parse with 1 thread=========
Took 0.001176 seconds to execute. 
204 entries in the index.
======================================
```
```
=======MT Parse with 5 threads========
Took 0.001624 seconds to execute. 
204 entries in the index.
======================================
```
```
=======MT Parse with 10 threads=======
Took 0.001684 seconds to execute. 
204 entries in the index.
======================================
```
```
=======MT Parse with 20 threads=======
Took 0.001927 seconds to execute. 
204 entries in the index.
======================================
```

### 24 files process

#### Better with 10 threads 
```
./benchmarker data_small/
```
```
Crawled 24 files.
Created DocIdMap
```
```
=======OG Parse with 1 thread=========
Took 0.205544 seconds to execute. 
20062 entries in the index.
======================================
```
```
=======MT Parse with 1 thread=========
Took 0.203541 seconds to execute. 
20062 entries in the index.
======================================
```
```
=======MT Parse with 5 threads========
Took 0.179137 seconds to execute. 
20062 entries in the index.
======================================
```
```
=======MT Parse with 10 threads=======
Took 0.174703 seconds to execute. 
20062 entries in the index.
======================================
```
```
=======MT Parse with 20 threads=======
Took 0.192872 seconds to execute. 
20062 entries in the index.
======================================
```

### Clint.py style check
```
./clint.py DirectoryParser_MT.c
```
```
Done processing DirectoryParser_MT.c
Total errors found: 0
```

### Valgrind memory check
```
valgrind ./test_suite 
```
```
==29851== 
==29851== HEAP SUMMARY:
==29851==     in use at exit: 0 bytes in 0 blocks
==29851==   total heap usage: 26,553 allocs, 26,553 frees, 1,234,114 bytes allocated
==29851== 
==29851== All heap blocks were freed -- no leaks are possible
==29851== 
==29851== For counts of detected and suppressed errors, rerun with: -v
==29851== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```