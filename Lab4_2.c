#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void randData(int *a, int *b, int*c);
float arithmeticMean(int a, int b);
float geometicMean(int a, int b);
float harmonicMean(int a, int b);

int main()
{
	int a1, a2, a3;
	int b1, b2, b3;
	
	srand(time(NULL));
	randData(&a1, &a2, &a3);
	randData(&b1, &b2, &b3);
	
	printf("arithmeticMean(%d, %d) => %.2f \n", a1, b1, arithmeticMean(a1, b1));
	printf("  geometicMean(%d, %d) => %.2f \n", a2, b2, geometicMean(a2, b2));
	printf("  harmonicMean(%d, %d) => %.2f \n", a3, b3, harmonicMean(a3, b3));

	return 0;
}

void randData(int *a, int *b, int*c) {
	int range = (80-5)+1;
	*a=rand() %range+5;
	*b=rand() %range+5;
	*c=rand() %range+5;
}

float arithmeticMean(int a, int b) {
	 float temp1;
	 temp1 = (a+b)*0.5;
	 return temp1;
}
float geometicMean(int a, int b) {
	float temp2;
	temp2 = sqrt(a*b);
	return temp2;
}
float harmonicMean(int a, int b) {
   float num1, num2;
   num1 = a;
   num2 = b;
   float temp3;
   temp3 = (2 * num1 * num2) / (num1 + num2);
   return temp3;
}
