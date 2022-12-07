CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=principal
SRC = fct1.c fct2.c fcts.c main.c
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
