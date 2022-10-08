CC = gcc
CFLAGS = -O3 -pthread -lm
RM = rm -f

EXECUTABLES = main

DEPENDENCIES = brute.c sequential.c parallel.c utils.c quickselect.c queue.c

all: $(EXECUTABLES)

main:  main.c $(DEPENDENCIES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(EXECUTABLES)