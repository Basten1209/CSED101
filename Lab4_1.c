#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void triangle(int a, int b, float *perimeter, float *area);
void print(float perimeter, float area);

int main()
{
	int a, b;
	float per;
	float are;
	
	printf("Enter two integer sides: ");
	scanf("%d %d", &a, &b);
	
	triangle(a, b, &per, &are);
	print(per, are);
	
	return 0;
	
}

void triangle(int a, int b, float *perimeter, float *area) {
	float c;
	c=sqrt(a*a+b*b);
	*perimeter=a+b+c;
	*area=a*b/2;
	
}

void print(float perimeter, float area) {

	printf("\nPerimeter: %f", perimeter);
	printf("\nArea     : %f", area);


}
