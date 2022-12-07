#include <stdio.h>
int main()
{
	int a,b,res;
	char c;
	scanf("%d%c%d",&a,&c,&b);
	if (c == '+'){
		res = a+b;
		printf("%d \n",res);
	}
	else if (c == '-'){
		res = a-b;
		printf("%d \n",res);
	}
	else if (c == '*'){
		res = a*b;
		printf("%d \n",res);
	}
	else if (c == '/'){
		res = a/b;
		printf("%d \n",res);
	}
		
	else {
		printf("Opérande non correct");
	}	

	

return 0;
}

