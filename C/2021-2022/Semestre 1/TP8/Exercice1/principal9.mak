DEBUG=yes
CC=gcc
ifeq ($(DEBUG),yes)
    CFLAGS=-W -Wall -ansi -pedantic -g
    LDFLAGS=
else
    CFLAGS=-W -Wall -ansi -pedantic
    LDFLAGS=
endif
EXEC=principal
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(EXEC)

principal : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean mrproper
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
