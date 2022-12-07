#include <stdio.h>
int main(){
double x,y;
printf("Saisir coordonées\n");
scanf("%lf %lf",&x,&y);
if (x > 0 && y>0){
	printf("Cadran + +\n");
}else if (x<0 && y>0){
	printf("Cadran - +\n");
}else if (x>0 && y<0){
	printf("Cadran + -\n");
}else if (x<0 && y<0){
	printf("Cadran - -\n");
}else{
	printf("Origine\n");
}

return 0;
}
