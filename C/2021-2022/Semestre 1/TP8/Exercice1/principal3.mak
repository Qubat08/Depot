CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=principal

all: $(EXEC)

principal : main.o fct1.o fct2.o fcts.o 
	@echo creation  : 
	$(CC) -o principal main.o fct1.o fct2.o fcts.o $(LDFLAGS)
	@echo ------------------------------- 

fct1.o : fct1.c fct1.h 
	@echo creation de fct1.o : 
	$(CC) -o fct1.o -c fct1.c $(CFLAGS)
	@echo ------------------------------- 

fct2.o : fct2.c fct2.h fcts.h 
	@echo creation de fct2.o : 
	$(CC) -o fct2.o -c fct2.c $(CFLAGS)
	@echo ------------------------------- 

fcts.o: fcts.c fcts.h 
	@echo creation de fcts.o : 
	$(CC) -o fcts.o -c fcts.c $(CFLAGS)
	@echo -------------------------------

main.o : main.c fct1.h fct2.h fcts.h 
	@echo creation de main.o :  
	$(CC) -o main.o -c main.c $(CFLAGS)
	@echo ------------------------------- 
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf $(EXEC)
