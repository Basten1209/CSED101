#include <stdio.h>

int add(int x, int y);
float average(int x, int y);
void printResults(int x, int y, int sum, float average);

int main()
{
	int x, y;
	printf("Enter two integers: ");
	scanf("%d %d", &x, &y);
	int s = add(x,y);
	float a = average(x,y);
	printResults(x,y,s,a);
	
	return 0;
}

int add(int x, int y){
	
	return x+y;
}

float average(int x, int y){

	return (x+y)*0.5;
}

void printResults(int x, int y, int sum, float average) {
	
	printf("\nThe sum of %d and %d is %d", x, y, sum);
	printf("\nThe average of numbers is %.1f\n", average);
	
}

