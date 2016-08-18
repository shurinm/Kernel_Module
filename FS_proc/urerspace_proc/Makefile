CC = gcc
CFLAGS = -Wall

all: user_space

user: user_space.o
		$(CC) $(CFLAGS) user_space.c -o user_space

clean:
		rm -rf user_space *.o

run:
		./user_space
