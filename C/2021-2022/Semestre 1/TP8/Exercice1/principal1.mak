principal : main.o fct1.o fct2.o fcts.o 
	@echo creation  : 
	gcc -o principal main.o fct1.o fct2.o fcts.o 
	@echo ------------------------------- 

fct1.o : fct1.c fct1.h 
	@echo creation de fct1.o : 
	gcc -o fct1.o -c fct1.c 
	@echo ------------------------------- 

fct2.o : fct2.c fct2.h fcts.h 
	@echo creation de fct2.o : 
	gcc -o fct2.o -c fct2.c 
	@echo ------------------------------- 

fcts.o: fcts.c fcts.h 
	@echo creation de fcts.o : 
	gcc -o fcts.o -c fcts.c 
	@echo -------------------------------

main.o : main.c fct1.h fct2.h fcts.h 
	@echo creation de main.o :  
	gcc -o main.o -c main.c 
	@echo ------------------------------- 