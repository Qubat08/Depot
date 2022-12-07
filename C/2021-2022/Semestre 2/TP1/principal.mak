principal : main.o  pileCh.o element.o  
	@echo creation  : 
	gcc -o principal main.o pileCh.o element.o 
	@echo ------------------------------- 

element.o : element.c element.h 
	@echo creation de element.o : 
	gcc -o element.o -c element.c 
	@echo ------------------------------- 

PileCh.o: pileCh.c pileCh.h 
	@echo creation de PileCh.o : 
	gcc -o pileCh.o -c pileCh.c 
	@echo -------------------------------

main.o : main.c element.h cellule.h pileCh.h 
	@echo creation de main.o :  
	gcc -o main.o -c main.c 
	@echo ------------------------------- 
clean:
	rm -rf *.o
mrproper: clean
	rm -rf main