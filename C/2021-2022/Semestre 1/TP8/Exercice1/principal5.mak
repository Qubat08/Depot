CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=principal

all: $(EXEC)

principal : main.o fct1.o fct2.o fcts.o 
	@echo creation  : 
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo ------------------------------- 
	

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
