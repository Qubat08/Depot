all: main

main : main.o LR.o TH.o 
	@echo creation  : 
	gcc -o principal main.o LR.o TH.o
	@echo ------------------------------- 

LR.o : LR.c LR.h 
	@echo creation de LR.o : 
	gcc -o LR.o -c LR.c  
	@echo ------------------------------- 
	
TH.o : TH.c TH.h
	@echo creation de TH.o :
	gcc -o TH.o -c TH.c
	@echo -------------------------------

main.o : main.c LR.h TH.h
	@echo creation de main.o :  
	gcc -o main.o -c main.c  
	@echo ------------------------------- 
		
clean:
	rm -rf *.o
mrproper: clean
	rm -rf principal