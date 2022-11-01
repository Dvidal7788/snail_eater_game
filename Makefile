# # Makefile for snail_eater.c

# gcc and clang to do not compile usleep() or nanosleep() the way I like. Will have to figure out other work around. Using make for now.
# CC = make
# OBJ = snail_eater

all:
	make snail_eater
run:
	./snail_eater
clean:
	rm snail_eater