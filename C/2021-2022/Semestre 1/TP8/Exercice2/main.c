#include <stdio.h> 
#include <stdlib.h> 
 
int conversion(char *s) { 
   int somme, i; 
   /* Algorithme de Horner */ 
   somme = 0; 
   i = 0; 
   while (s[i] != '\0') { 
     somme = 10 * somme + s[i] - '0' ; 
     i++; 
   } 
   return somme; 
} 
 
int main(int argc, char *argv[]) { 
 
  int i; 
  int valeur, somme=0; 
 
  for (i=1; i<=argc; i++) { 
   valeur = conversion(argv[i]); 
   somme = somme + valeur; 
   printf("Argv %d, valeur %d\n", i, 
valeur); 
  } 
  printf("Somme : %d\n", somme); 
  return 0; 
}