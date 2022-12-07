#include <stdio.h>
int main(){

int a;
printf("Saisir valeur entre 1 et 12\n");
scanf("%d",&a);

switch (a){
	case 1:
		printf("Janvier, 31\n");
		break;
	case 2:
		printf("Fevrier, 28-29\n");
		break;
	case 3:
		printf("Mars, 31\n");
		break;
	case 4:
		printf("Avril, 30\n");
		break;
	case 5:
		printf("Mai, 31\n");
		break;
	case 6:
		printf("Juin, 30\n");
		break;
	case 7:
		printf("Juillet, 31\n");
		break;
	case 8:
		printf("Aout, 31\n");
		break;
	case 9:
		printf("Septembre, 30\n");
		break;
	case 10:
		printf("Octobre, 31\n");
		break;
	case 11:
		printf("Novembre, 30\n");
		break;
	case 12:
		printf("Decembre, 31\n");
		break;
	default:
		printf("Valeur non valide\n");
		break;
	}
		
return 0;
}
