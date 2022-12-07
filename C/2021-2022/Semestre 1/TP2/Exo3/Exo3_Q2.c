#include <stdio.h>
int main (){
int a;
printf("Saisir un chiffre\n");
scanf("%d",&a);

switch (a){
	case 0:
		printf("zero\n");
		break;
	case 1:
		printf("un\n");
		break;
	case 2:
		printf("deux\n");
		break;
	case 3:
		printf("trois\n");
		break;
	case 4:
		printf("quatre\n");
		break;
	case 5:
		printf("cinq\n");
		break;
	case 6:
		printf("six\n");
		break;
	case 7:
		printf("sept\n");
		break;
	case 8:
		printf("huit\n");
		break;
	case 9:
		printf("neuf\n");
		break;
	default:
		printf("Ce n'est pas un chiffre\n");
		break;
}
return 0;
}
