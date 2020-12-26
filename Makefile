CC=gcc
CFLAGS=-g -O2 -Wall

tamarack: src/*.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	rm -rf tamarack
