#include "complex.h" 
 
int main(void) 
 { 
  complex  n1, n2, res, n3; 
 
 double res1=0;

  saisir(&n1);
  saisir(&n2);

  affichage_complex(n1);
  affichage_complex(n2);


  res = produit_C(n1,n2);
  // produit(&n1,n2);

  // printf("produit par indice: ");
  // affichage_complex(n1);
  printf("produit par valeur : ");
  affichage_complex(res);
  

  n3 = Conjugue_C(n2);
  printf("Conjugue de n2: ");
  affichage_complex(n3);

  printf("Quotient: \n");
  n3 = Quotient_C(n1,n2);
  affichage_complex(n3);

  res1= Module_C(n1);
  printf("\nModule %.2lf",res1);

  return 0; 
 }