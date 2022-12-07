#include <stdio.h>
int main (){
char a;

printf("Quelle est la bonne façon de déclarer une variable entière en langage C: \n");
printf(" a. Entier x; \n b. Int x; \n c. integer x; \n d. int x; \n e; Long x;\n");
printf("Choisissez votre lettre de réponse: ");

scanf("%c",&a);

switch (a){
	case 'd':
		printf("Bonne réponse\n");
		break;
	default:
		printf("Mauvaise réponse\n");
		break;
	}

return 0;
}
