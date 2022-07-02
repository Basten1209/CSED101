#include <stdio.h>

#define SIZE 10

int Seqsearch(int arr[], int size, int n);

int main(){
	int a[SIZE];
	int num;
	int pos;
	
	printf("Input 10 integer values: ");
	for (int i=0; i<SIZE; i++){
		scanf("%d", &a[i]);
	}
	printf("Entered number is	: ");
	for (int j=0; j<SIZE; j++){

	printf("%d ", a[j]);
	}
	printf("\n");
	printf("Input an integer that you want to find : ");
	scanf("%d", &num);
	pos = Seqsearch(a, SIZE, num);
	if(pos == -1){
		printf("Not Found!\n");
	}
	else{
		printf("The index of %d is %d", num, pos);
	}
	return 0;

}

int Seqsearch(int arr[], int size, int n){
	for (int k=0; k<size; k++){
		if(arr[k] == n){
			return k+1;
		}
	}
	return -1;
}
