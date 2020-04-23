all: server client

# define the commands we'll use for compilation and library building
OBJS = libSystem.a

# define useful flags to cc/ld/etc.
CFLAGS = -g -Wall -I. -Iheaders -L. -lSystem -lpthread

server: guess_server.c $(OBJS)
	gcc  -o guess_server guess_server.c $(OBJS) $(CFLAGS)

runserver:
	./guess_server

valserver:
	valgrind ./guess_server

client: guess_client.c $(OBJS)
	gcc -o guess_client guess_client.c $(OBJS) $(CFLAGS)

runclient:
	./guess_client

valclient:
	valgrind ./guess_client

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: FORCE
	/bin/rm -f *.o *~ server client

FORCE:
