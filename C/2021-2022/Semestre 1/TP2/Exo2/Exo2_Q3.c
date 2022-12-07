#include <stdio.h>
int main(){
double u; double f;
printf("Saisir consommation: \n");
scanf("%lf",&u);
if (u<=50){
	f = 0.50*u;
	f = f + f*20/100;
	printf("Facture: %.2lf \n",f);
	
} else if (u>50 && u<=150){
	f = 0.75*u;
	f = f + f*20/100;
	printf("Facture: %.2lf\n",f);
	
} else if (u>150 && u<=250){
	f = 1.20*u;
	f = f + f*20/100;
	printf("Facture: %.2lf\n",f);
	
} else if (u>250){
	f = 1.50*u;
	f = f + f*20/100;
	printf("Facture: %.2lf\n",f);
}

return 0;
}
