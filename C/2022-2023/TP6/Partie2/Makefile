CC = gcc
EXEC = prog 
SRC= $(wildcard *.c) $(wildcard */*.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o : %.c 
	$(CC) -o $@ -c $<

clear :
	rm -f $(EXEC) $(OBJ)