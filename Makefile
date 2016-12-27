CC = gcc
CFLAGS = -finstrument-functions -g -O0
LIBS = -lunwind

all:
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
