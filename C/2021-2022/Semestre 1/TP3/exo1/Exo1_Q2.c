#include <stdio.h>
#include <float.h>

int main (){
printf("FLOAT MIN = %.1f \n", FLT_MIN);
printf("FLOAT MAX = %.1f \n", FLT_MAX);
printf("DOUBLE MIN = %.1lf \n",DBL_MIN);
printf("DOUBLE MAX = %.1lf \n",DBL_MAX);
printf("LONG DOUBLE MIN = %.1Lf \n",LDBL_MIN);
printf("LONG DOUBLE MAX = %.1Lf \n",LDBL_MAX);
printf("TRUE FLOAT MIN = %.1f \n",FLT_TRUE_MIN);
printf("TRUE DOUBLE MIN = %.1lf \n", DBL_TRUE_MIN); 
printf("TRUE LONG DOUBLE MIN = %.1Lf \n", LDBL_TRUE_MIN);
printf("FLOAT DIG = %d \n", FLT_DIG);
printf("DOUBLE DIG = %d \n", DBL_DIG);
printf("LONG DOUBLE DIG = %d \n", LDBL_DIG);
return 0;
}
