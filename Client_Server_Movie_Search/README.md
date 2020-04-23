# Client Server Movie Search Engine

### Clint.py style check
```
./clint.py *.c
```
```
Done processing MultiServer.c
Done processing QueryClient.c
Done processing QueryServer.c
Total errors found: 0
```

### Sample output
```
./queryclient 127.0.0.1 1500
```
```
Connected to movie server.

Enter a term to search for, or q to quit: seattle
input was: seattle


Connected to movie server.

Receiving 7 results
tt3245458|tvEpisode|Seattle Seahawks: Road to 2008|Seattle Seahawks: Road to 2008|0|2008|-|23|-

tt3247806|tvEpisode|St. Louis Cardinals vs. Seattle Seahawks|St. Louis Cardinals vs. Seattle Seahawks|0|1976|-|-|Sport

tt3277988|tvEpisode|Seattle|Seattle|0|2013|-|42|Reality-TV

tt3281748|tvEpisode|Seattle Seahawks vs. Los Angeles Raiders|Seattle Seahawks vs. Los Angeles Raiders|0|1992|-|-|Sport

tt3281716|tvEpisode|Seattle Seahawks vs. Dallas Cowboys|Seattle Seahawks vs. Dallas Cowboys|0|1980|-|-|Sport

tt3281696|tvEpisode|Denver Broncos vs. Seattle Seahawks|Denver Broncos vs. Seattle Seahawks|0|1997|-|-|Sport

tt3211900|tvEpisode|Wasted in Seattle|Wasted in Seattle|0|2013|-|44|Crime,Documentary

Got 7 bytes. resp: GOODBYE
Enter a term to search for, or q to quit: q
input was: q
Thanks for playing!
```

```
./queryserver -f data_small/ -p 1500
```
```
Waiting for connection...
Client connected: client_fd=4
checking goodbye...GOODBYE
Client connection closed.
Waiting for connection...
Client connected: client_fd=4
checking goodbye...seattle
I expected a GOODBYE. Instead received: -seattle- 
Getting docs for movieset term: "seattle"
num_responses: 7
Destroying search result iter
Client connection closed.
Waiting for connection...
^CExit signal sent. Cleaning up...
```

### Valgrind memory check
```
valgrind ./queryclient 127.0.0.1 1500
```
``` 
==24992== 
==24992== HEAP SUMMARY:
==24992==     in use at exit: 0 bytes in 0 blocks
==24992==   total heap usage: 5 allocs, 5 frees, 2,240 bytes allocated
==24992== 
==24992== All heap blocks were freed -- no leaks are possible
==24992== 
==24992== For counts of detected and suppressed errors, rerun with: -v
==24992== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind ./queryserver -f data_small/ -p 1500
```
```
==24970== 
==24970== HEAP SUMMARY:
==24970==     in use at exit: 0 bytes in 0 blocks
==24970==   total heap usage: 1,140,531 allocs, 1,140,531 frees, 49,811,794 bytes allocated
==24970== 
==24970== All heap blocks were freed -- no leaks are possible
==24970== 
==24970== For counts of detected and suppressed errors, rerun with: -v
==24970== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


```
valgrind ./multiserver -f data_small/ -p 1500 -d
```

```
==24869== 
==24869== HEAP SUMMARY:
==24869==     in use at exit: 0 bytes in 0 blocks
==24869==   total heap usage: 1,140,531 allocs, 1,140,531 frees, 49,811,794 bytes allocated
==24869== 
==24869== All heap blocks were freed -- no leaks are possible
==24869== 
==24869== For counts of detected and suppressed errors, rerun with: -v
==24869== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==24866== 
==24866== HEAP SUMMARY:
==24866==     in use at exit: 0 bytes in 0 blocks
==24866==   total heap usage: 1,140,490 allocs, 1,140,490 frees, 49,778,802 bytes allocated
==24866== 
==24866== All heap blocks were freed -- no leaks are possible
==24866== 
==24866== For counts of detected and suppressed errors, rerun with: -v
==24866== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==24868== 
==24868== HEAP SUMMARY:
==24868==     in use at exit: 0 bytes in 0 blocks
==24868==   total heap usage: 1,140,490 allocs, 1,140,490 frees, 49,778,802 bytes allocated
==24868== 
==24868== All heap blocks were freed -- no leaks are possible
==24868== 
==24868== For counts of detected and suppressed errors, rerun with: -v
==24868== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==24865== 
==24865== HEAP SUMMARY:
==24865==     in use at exit: 0 bytes in 0 blocks
==24865==   total heap usage: 1,140,490 allocs, 1,140,490 frees, 49,778,802 bytes allocated
==24865== 
==24865== All heap blocks were freed -- no leaks are possible
==24865== 
==24865== For counts of detected and suppressed errors, rerun with: -v
==24865== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==24854== 
==24854== HEAP SUMMARY:
==24854==     in use at exit: 0 bytes in 0 blocks
==24854==   total heap usage: 1,140,449 allocs, 1,140,449 frees, 49,745,810 bytes allocated
==24854== 
==24854== All heap blocks were freed -- no leaks are possible
==24854== 
==24854== For counts of detected and suppressed errors, rerun with: -v
==24854== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```