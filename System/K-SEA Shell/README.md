# Mini Shell

### My Command
- pwd 
	- `> pwd`
	- `print out the current working directory`
	- utilize `getcwd` in `unistd.h`
- history 
	- `> history`
	- `print out the history commands, max history storage is 40`
	- creates a global array and stores history in the while loop of `main`
	- print out the histories, iterate through all histories in the array.

### Clint.py style check
```
./clint.py *.c
```
```
k-sea-shell.c:118:  Consider using strtok_r(...) instead of strtok(...) for improved thread safety.  [runtime/threadsafe_fn] [2]
k-sea-shell.c:120:  Consider using strtok_r(...) instead of strtok(...) for improved thread safety.  [runtime/threadsafe_fn] [2]
Done processing k-sea-shell.c
Total errors found: 2
```
- strtok_r: I use strtok instead of strtok_r since I didn't malloc any array in this assignment, everything is in the stack memory.


### Sample output
```
./k-sea-shell 
```
```
k-sea-shell> pwd
current working directory: /home/linni/linni_CS5006/a10/a10-official
k-sea-shell> cd ..
you're going to ..
k-sea-shell> pwd
current working directory: /home/linni/linni_CS5006/a10
k-sea-shell> cd ..
you're going to ..
k-sea-shell> pwd 
current working directory: /home/linni/linni_CS5006
k-sea-shell> cd ..
you're going to ..
k-sea-shell> pwd
current working directory: /home/linni
k-sea-shell> history
history 1: pwd
history 2: cd ..
history 3: pwd
history 4: cd ..
history 5: pwd
history 6: cd ..
history 7: pwd
history 8: history
k-sea-shell> help
Usage:
> cd [directory]
> help
> exit
> pwd
> history
k-sea-shell> exit
k-sea-shell terminated
```

### Valgrind memory check
```
valgrind ./k-sea-shell
```
```
==6901== Memcheck, a memory error detector
==6901== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6901== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==6901== Command: ./k-sea-shell
==6901== 
```
```
k-sea-shell> pwd
current working directory: /home/linni/linni_CS5006/a10/a10-official
==6902== 
==6902== HEAP SUMMARY:
==6902==     in use at exit: 0 bytes in 0 blocks
==6902==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6902== 
==6902== All heap blocks were freed -- no leaks are possible
==6902== 
==6902== For counts of detected and suppressed errors, rerun with: -v
==6902== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
k-sea-shell> cd ..
you're going to ..
k-sea-shell> pwd
current working directory: /home/linni/linni_CS5006/a10
==6903== 
==6903== HEAP SUMMARY:
==6903==     in use at exit: 0 bytes in 0 blocks
==6903==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6903== 
==6903== All heap blocks were freed -- no leaks are possible
==6903== 
==6903== For counts of detected and suppressed errors, rerun with: -v
==6903== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
k-sea-shell> cd ..
you're going to ..
k-sea-shell> pwd
current working directory: /home/linni/linni_CS5006
==6904== 
==6904== HEAP SUMMARY:
==6904==     in use at exit: 0 bytes in 0 blocks
==6904==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6904== 
==6904== All heap blocks were freed -- no leaks are possible
==6904== 
==6904== For counts of detected and suppressed errors, rerun with: -v
==6904== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
k-sea-shell> history
history 1: pwd
history 2: cd ..
history 3: pwd
history 4: cd ..
history 5: pwd
history 6: history
==6905== 
==6905== HEAP SUMMARY:
==6905==     in use at exit: 0 bytes in 0 blocks
==6905==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6905== 
==6905== All heap blocks were freed -- no leaks are possible
==6905== 
==6905== For counts of detected and suppressed errors, rerun with: -v
==6905== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
k-sea-shell> help
Usage:
> cd [directory]
> help
> exit
> pwd
> history
==6906== 
==6906== HEAP SUMMARY:
==6906==     in use at exit: 0 bytes in 0 blocks
==6906==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6906== 
==6906== All heap blocks were freed -- no leaks are possible
==6906== 
==6906== For counts of detected and suppressed errors, rerun with: -v
==6906== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
```
k-sea-shell> exit
k-sea-shell terminated
==6907== 
==6907== HEAP SUMMARY:
==6907==     in use at exit: 0 bytes in 0 blocks
==6907==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6907== 
==6907== All heap blocks were freed -- no leaks are possible
==6907== 
==6907== For counts of detected and suppressed errors, rerun with: -v
==6907== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==6901== 
==6901== HEAP SUMMARY:
==6901==     in use at exit: 0 bytes in 0 blocks
==6901==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==6901== 
==6901== All heap blocks were freed -- no leaks are possible
==6901== 
==6901== For counts of detected and suppressed errors, rerun with: -v
==6901== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
