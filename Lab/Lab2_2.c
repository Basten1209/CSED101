#include <stdio.h>

int main()
{
	
	double r;
	double pi=3.141592;
	
	printf("반지름을 입력하시오: ");
	scanf("%lf", &r);
	
	double a = 2*pi*r;
	double b = pi*r*r; 
	printf("\n원 둘레: %lf", a);
	printf("\n원 넓이: %lf", b);
	
	return 0;
	
}
