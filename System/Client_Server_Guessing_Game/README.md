# Client Server Guessing Game

### Clint.py style check
```
./clint.py *.c
```
```
Done processing guess_client.c
Done processing guess_server.c
Total errors found: 0
```

### Sample output
```
./guess_client
```
```
Connected to guess server.

Server: Welcome! I've chosen a number between 1 and 50. Guess it!
Client: 15
Server: Too high.
Client: 16
Server: Too high.
Client: hhh
Server: I don't recognize that number.
Please guess a number between 1 and 50.
Client: 12
Server: Too low.
Client: gggg
Server: I don't recognize that number.
Please guess a number between 1 and 50.
Client: 1
Server: Too low.
Client: -1
Server: I don't recognize that number.
Please guess a number between 1 and 50.
Client: 14
Server: You guessed my secret number!
It only took you 5 guesses, plus something I didn't understand.
```

```
./guess_server
```
```
===answer: 14===
Waiting for connection...
Client connected: client_fd=4
Waiting for connection...
Client connected: client_fd=5
Waiting for connection...
Client connected: client_fd=6
Waiting for connection...
Client connected: client_fd=7
Waiting for connection...
Client connected: client_fd=8
Waiting for connection...
Client connected: client_fd=9
Waiting for connection...
Client connected: client_fd=10
Waiting for connection...
Client connected: client_fd=11
Waiting for connection...
Client connected: client_fd=12
```


### Valgrind memory check
```
valgrind ./guess_client
```
```
==957== HEAP SUMMARY:
==957==     in use at exit: 0 bytes in 0 blocks
==957==   total heap usage: 3 allocs, 3 frees, 1,640 bytes allocated
==957== 
==957== All heap blocks were freed -- no leaks are possible
==957== 
==957== For counts of detected and suppressed errors, rerun with: -v
==957== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

```
valgrind ./guess_server
```
```
==950== HEAP SUMMARY:
==950==     in use at exit: 0 bytes in 0 blocks
==950==   total heap usage: 2 allocs, 2 frees, 1,088 bytes allocated
==950== 
==950== All heap blocks were freed -- no leaks are possible
==950== 
==950== For counts of detected and suppressed errors, rerun with: -v
==950== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```