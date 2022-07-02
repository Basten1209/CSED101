#include<stdio.h>
#define MAX 6

void bubble_sort(int a[], int size);
void swap(int* x, int* y);
void print_array(int a[], int size);
void input_array(int a[], int size);

int main()
{
    int ary[MAX];

    printf("Input integer numbers to be sorted: ");
    input_array(ary, MAX);

    printf(" Unsorted: ");
    print_array(ary, MAX);

    printf("----------------------------------\n");
    bubble_sort(ary, MAX);
    printf("----------------------------------\n");

    printf("   Sorted: ");
    print_array(ary, MAX);

    return 0;
}

//---------- 함수 정의  ----------//
void input_array(int a[], int size)
{
	for(int i=0; i<size; i++){
	scanf("%d", &a[i]);
	}	
}

void print_array(int a[], int size)
{
	for(int i=0; i<size; i++){
		printf(" %3d", a[i]);
	}
	printf("\n");
}
void swap(int* x, int* y){
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
void bubble_sort(int a[], int size){
	for(int i=0; i<size-1; i++){
		for(int j=0; j<size-1; j++){
			if(a[j]>a[j+1]){
				swap(&a[j], &a[j+1]);
			}
		}
		printf("[step %3d]", i+1);
		print_array(a, size);
		printf("\n");
	}
}


