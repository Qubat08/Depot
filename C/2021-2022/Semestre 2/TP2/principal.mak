all: main

main : main.o Element.o ListeCh.o  
	@echo creation  : 
	gcc -o principal main.o Element.o ListeCh.o 
	@echo ------------------------------- 

Element.o : Element.c Element.h 
	@echo creation de Element.o : 
	gcc -o Element.o -c Element.c  
	@echo ------------------------------- 

ListeCh.o : ListeCh.c ListeCh.h Cellule.h 
	@echo creation de ListeCh.o : 
	gcc -o ListeCh.o -c ListeCh.c  
	@echo ------------------------------- 

main.o : main.c Element.h Cellule.h ListeCh.h 
	@echo creation de main.o :  
	gcc -o main.o -c main.c  
	@echo ------------------------------- 
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main