#include <stdio.h>

int main()
{
	
	double r;
	double pi=3.141592;
	
	printf("�������� �Է��Ͻÿ�: ");
	scanf("%lf", &r);
	
	double a = 2*pi*r;
	double b = pi*r*r; 
	printf("\n�� �ѷ�: %lf", a);
	printf("\n�� ����: %lf", b);
	
	return 0;
	
}
