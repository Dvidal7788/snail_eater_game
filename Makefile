# # Makefile for snail_eater.c

# gcc and clang to do not compile usleep() or nanosleep() the way I like. Not even cc, which is odd, bc cc should be what make uses by default. Will have to figure out other work around. Using make for now.
PROGRAM = snail_eater_game
DATE = $(shell date +%F)

TAR = $(PROGRAM)_$(DATE)
CC = cc
BIN = bin

SRC = src
OBJ = obj
INCDIRS = . ./include

DEPFLAGS = -MP -MD
CFLAGS = -Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)
# CFLAGS = -Wall -Wextra -g -L./include -lcsv_reader.a $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)

CFILES = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(CFILES))
DEPFILES = $(patsubst $(SRC)/%.c,$(OBJ)/%.d, $(CFILES))


.PHONY: all
all:$(BIN)

$(OBJ)/%.o:$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):$(OBJS)
	$(CC) -o $@ $^


dist:
	tar -czvf $(TAR).tgz *
	@echo $(TAR).tgz created successfully :\)

.PHONY: run
run:
	@./$(BIN)


.PHONY: clean
clean:
	rm -f $(BIN)
	rm -rf *.o $(OBJ)/*.o
	rm -f *.exe
	rm -f a.out

-include $(DEPFILES)