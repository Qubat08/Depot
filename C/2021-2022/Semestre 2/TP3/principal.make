all: main

main : main.o LR.o  
	@echo creation  : 
	gcc -o principal main.o LR.o
	@echo ------------------------------- 

LR.o : LR.c LR.h 
	@echo creation de Element.o : 
	gcc -o LR.o -c LR.c  
	@echo ------------------------------- 


main.o : main.c LR.h
	@echo creation de main.o :  
	gcc -o main.o -c main.c  
	@echo ------------------------------- 
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main