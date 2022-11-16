# # Makefile for snail_eater.c

# gcc and clang to do not compile usleep() or nanosleep() the way I like. Not even cc, which is odd, bc cc should be what make uses by default. Will have to figure out other work around. Using make for now.
CC = cc
SRC = src
CFILES = $(SRC)/snail_eater.c $(SRC)/func.c
OBJ = obj
OBJS = $(OBJ)/snail_eater.o $(OBJ)/func.o
BIN = snail_eater

all:$(BIN)

$(OBJ)/%.o:$(SRC)/%.c
	$(CC) -c $^ -o $@

$(BIN):$(OBJS)
	$(CC) -o $@ $^

# make $(BIN)

run:
	@./$(BIN)
clean:
	rm -rf $(BIN)
	rm -rf *.o $(OBJ)/*
	rm -rf *.exe
	rm -rf a.out
