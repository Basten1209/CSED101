#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#define SIZE 6
#define _CRT_SECURE_NO_WARNINGS
void swap(int *a, int *b); //�迭 ���� 2�� ��ġ �ٲٱ� 
void print_board(int *score, int arr[SIZE][SIZE]); //���� ����Ʈ, ���ھ� ���� �Լ� 
int check_position(int a, int b, int p, int q); // 3��ġ�� �ش��ϴ��� Ȯ���ϴ� �Լ� 
void main()
{
int boardarr[SIZE][SIZE]; //�ʱ� ���� ���� 

int score = 0; //���� ���� 

int turns = 5; // �� �� ���� 
	char gamestart; //���� �Է½� ���� ���� - ���� ���� ���� ���� 
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assignment 2\n");
	printf("\n");
	printf("[[ Match-3 Game ]]\n");
	printf("\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");

	gamestart = _getch();
	if (gamestart == 13) { //���� �Է� ���� �� ���� ���� - �� �ܴ� �߸��� �Է� ��� �� ���α׷� ���� 
		system("cls");
	}
	else {
		printf("�߸��� �Է��Դϴ�.\n");
		exit(1);
	}

FILE *f; //���� ���� 
f = fopen("board.txt", "r+"); //txt ���Ϸ� ���� �о���� 
for (int i = 0; i < SIZE; i++){
	for (int j = 0; j < SIZE; j++){
		fscanf(f, "%d", &boardarr[i][j]);
		}
	}
fclose(f);

while(turns!=0){ //�� ���� 0 �� �� �� ���� �ݺ����� 
	print_board(&score, boardarr);
	int a1, a2;
	int b1, b2;
	int check;
	printf("===========\n\n");
	printf("* Remaining turns: %d\n", turns);
	printf("Swap...\n");
	printf("Block 1:"); //������ �� �� �ޱ� 
	scanf("%d %d", &a1, &a2);
	printf("Block 2:");
	scanf("%d %d", &b1, &b2);
	check = check_position(a1,a2,b1,b2); //���� ���� ������ ������ ������ Ȯ�� 
	while(check != 1){ //���� ������ ��� = check = 1�� ���. 2�� ���� �Է��� �߸� �� ���̹Ƿ� �ٽ� �Է��� �޴´� 
		if(check == 2){
			system("cls");
			print_board(&score, boardarr);
			printf("============\n\n");
			printf("*** �߸��� �Է�! ***\n");
			printf("* Remaining turns: %d\n", turns);
			printf("Swap...\n");
			printf("Block 1:");
			scanf("%d %d", &a1, &a2);
			printf("Block 2:");
			scanf("%d %d", &b1, &b2);
			check = check_position(a1,a2,b1,b2);
			}
	}
	swap(&boardarr[a1][a2], &boardarr[b1][b2]); //�ΰ� ��ġ ���� 
	
	system("cls");
	turns= turns-1; //�� �ϳ� �Ҹ� 

}
	print_board(&score, boardarr); //������ ȭ�� ��� 
	printf("=============\n\n"); 
	
	printf("**You've earned %d points!", score); //���� ���ھ� ��� 
	exit(0); //���� 
}




void print_board(int *score, int arr[SIZE][SIZE]){
	int checksum=0; //3��ġ�� �ش��ϴ� ���� �ִ��� Ȯ���ϱ� ���� ���� ���� 
do
{	
	int checkarr[SIZE][SIZE] = {
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0}
	}; //checkarr = 0 -> 3��ġ ���� x, checkarr = 1 -> 3 ��ġ ���� O 
	for(int i=0; i<SIZE; i++){ //���ι������� 3 ��ġ Ȯ�� 
		for(int j=1; j<SIZE-1; j++){
			if(arr[i][j]==arr[i][j-1]&&arr[i][j]==arr[i][j+1]){
				checkarr[i][j-1] = 1;
				checkarr[i][j] = 1;
				checkarr[i][j+1] = 1;
			}
		}
	}
	for(int i=1; i<SIZE-1; i++){ //���� �������� 3��ġ Ȯ�� 
		for(int j=0; j<SIZE; j++){
			if(arr[i][j]==arr[i-1][j]&&arr[i][j]==arr[i+1][j]){
				checkarr[i-1][j] = 1;
				checkarr[i][j] = 1;
				checkarr[i+1][j] = 1;
			}
		}
	}
	checksum = 0; //checksum 0���� ����(���� �ݺ��� �� ������ ����) 
	for(int i=0; i<SIZE; i++){
		for (int j=0; j<SIZE; j++){
		checksum+=checkarr[i][j]; //checkarr�� �� ��ġ�� (0�̸� 3��ġ ����Ǵ� ĭ x, �� �ܿ��� 3��ġ ����Ǵ� ĭ ���� 
		}
	}
	system("cls");
	printf("Score : %d\n", *score); //score ��� 
	for (int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(checkarr[i][j]==0){
			printf("%d ", arr[i][j]);
		}
			else if(checkarr[i][j]==1){ //checkarr[i][j]�� ��츸 �Ӱ� ��� 
			printf("\033[1;31m");
			printf("%d ", arr[i][j]);
			printf("\033[0m");
			}
		}
			printf("| %d \n", i);		
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5 \n");
	Sleep(1000);

		for(int i=0; i<SIZE; i++){ //checkarr[i][j]�� boardarr[i][j] �� �� = score 
			for(int j=0; j<SIZE; j++){
				*score+=arr[i][j]*checkarr[i][j];
			}
		}
		
	system("cls");
	printf("Score : %d\n", *score); //3��ġ Ȯ�� �� score ��� 
	for(int i=0; i<SIZE; i++){ // checkarr[i][j]=1�� ��� ��ĭ ��� 
		for(int j=0; j<SIZE; j++){
			if(checkarr[i][j]==0){
				printf("%d ", arr[i][j]);
			}
			else if(checkarr[i][j]==1){
				printf("  ");
			}	
		}
			printf("| %d \n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5 \n");
	Sleep(1000);
	
	system("cls");
	printf("Score : %d\n", *score); //score ��� 
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(checkarr[i][j]==0){
				printf("%d ", arr[i][j]);
			}
			else if(checkarr[i][j]==1){ //checkarr[i][j]�� 1�� ��� �������� ���� �� �ҷ����� 
			arr[i][j] = rand()%5+1;
				printf("%d ", arr[i][j]);
			}	
		}
			printf("| %d \n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5 \n");
	Sleep(1000);

}while(checksum!=0); //3��ġ�� �ش��ϴ� ĭ�� ���� �� ���� �ݺ� 
}
void swap(int *a, int *b){ //�� �� �ٲٱ� �Լ� 
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int check_position(int a, int b, int p, int q){ //�� ������ 1~5 ���̰�, �� Ȥ�� �� �� �ϳ��� �����ϰ�, �ٸ� �ϳ��� ���̳��� ���� ������ �� ĭ��.
												//num = 1�̸� ���� ������ �� ĭ, 2�� ���� �Ұ����� �� ĭ 
	int num=0;
	if((a==p && abs(b-q)==1)){
		num=1;
	}
	else if((b==q && abs(a-p)==1)){
		num=1;
	}
	else{
		num=2;
	}
	if(a<0 || a>5){
		num=2;
	}
	else if(b<0||b>5){
		num=2;
	}
	else if(p<0||p>5){
		num=2;
	}
	else if(q<0||q>5){
		num=2;
	}

	return num; //num ��ȯ 
}

