#include <stdio.h>

void partial_print(int* arr_start, int size);
int partial_sum(int* arr_start, int* arr_end);

int main()
{
	int a[10];
	int start, end;
	int* p = a;

	printf("Enter 10 elements of array: ");
	scanf("%d %d %d %d %d %d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7], &a[8], &a[9]);
	printf("Numbers that you enter are: ");
	partial_print(p, 10);
	printf("\n");
	printf("Enter the starting and ending index: ");
	scanf("%d %d", &start, &end);
	printf("Sum from array[%d] to array[%d] is %d\n", start, end, partial_sum(p+start, p+end));
	printf("Partial array output: ");
	partial_print(p+start, end-start+1);
}

void partial_print(int* arr_start, int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		printf("%d ", *arr_start+i);
	}
	return;
}

int partial_sum(int* arr_start, int* arr_end)
{
	int i;
	int sum = 0;
	for (i=0; i<=(*arr_end-*arr_start); i++)
	{
		sum += (*arr_start+i);
	}

	return sum;
}
