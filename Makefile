CC=gcc
CFLAGS=-g -O2 -Wall

tamarack: src/tamarack.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm -rf tamarack
