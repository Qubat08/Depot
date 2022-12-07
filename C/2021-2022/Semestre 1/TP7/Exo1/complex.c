#include "complex.h" 
#include "math.h" 
 
complex lecture_complex(){ 
 complex tmp; 
 
 printf("Donner la partie réelle:");
 scanf("%f",&tmp.reel); 
 printf("donner la partie imaginaire:");
 scanf("%f",&tmp.imag); 
 return (tmp);
} 
 
void affichage_complex(complex c){ 
 printf("%.2f + %.2fi\n",c.reel,c.imag);
} 
 
complex addition_C(complex c1,complex c2){ 
  complex tmp;

  tmp.reel = c1.reel + c2.reel; 
  tmp.imag = c1.imag + c2.imag; 

  return (tmp);
} 
void saisir(complex *pc){
  printf("Saisir la partie réelle: \n");
  scanf("%f",&pc->reel);
  printf("Saisir la partie imaginaire: \n");
  scanf("%f",&pc->imag);
}

void ajout (complex *pc1, complex c2){
  pc1->reel += c2.reel;
  pc1->imag += c2.imag;
}

complex produit_C (complex c1, complex c2){
  complex tmp;

  tmp.reel = c1.reel * c2.reel - c1.imag*c2.imag;
  tmp.imag = c1.reel*c2.imag +c1.imag * c2.reel ;

  return (tmp);
}

void produit (complex *pc1, complex c2){
  pc1->reel = pc1->reel*c2.reel - pc1->imag*c2.imag;
  pc1->imag = pc1->reel*c2.imag +pc1->imag*c2.reel;
}

complex Conjugue_C(complex c){
  c.imag = -c.imag;
  return (c);
}

complex Quotient_C(complex c1, complex c2){
  complex res,num;
  complex conj;
  float denum;


  conj = Conjugue_C(c2);
  num = produit_C(c1,conj);
  // printf("NUM!!!!\n");
  affichage_complex(num);

  denum = c2.reel*c2.reel+c2.imag*c2.imag;
  // printf("DENUM!!!! %f \n",denum);

  res.reel = (num.reel) / denum;
  res.imag = (num.imag)/ denum;
 


  return (res);
}

double Module_C(complex c){
  double temp =0;
  printf("=================");
  affichage_complex(c);
  temp = sqrt(c.reel*c.reel + c.imag*c.imag);
  
  return temp;
}

double Argument_C(complex c){

}
complex Rac2C(complex z){

}