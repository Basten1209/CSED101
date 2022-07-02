#include <stdio.h>
#define MAX_SIZE 20

void print_matrix(int arr[MAX_SIZE][MAX_SIZE], int size);
int main()
{
	int size;
	int a[MAX_SIZE][MAX_SIZE];
	
	printf(" Enter the size of square : ");
	scanf("%d", &size);
	print_matrix(a, size);
	
	return 0;
	
}

void print_matrix(int arr[MAX_SIZE][MAX_SIZE], int size){
	
	int r, c, i, j;
	for(r=0; r<size; r++){
		for(c=0; c<size; c++){
			if(c+r<(size-1)){
				arr[r][c] = 1;
			}
			else if(c+r==(size-1)){
				arr[r][c] = 0;
			}
			else if(c+r>(size-1)){
				arr[r][c] = -1;
			}
		}
	}
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf(" %2d", arr[i][j]);
		}
		printf("\n");
	}
	
}
