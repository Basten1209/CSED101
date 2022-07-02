#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#define SIZE 6
#define _CRT_SECURE_NO_WARNINGS
void swap(int *a, int *b); //배열 문자 2개 위치 바꾸기 
void print_board(int *score, int arr[SIZE][SIZE]); //보드 프린트, 스코어 갱신 함수 
int check_position(int a, int b, int p, int q); // 3매치에 해당하는지 확인하는 함수 
void main()
{
int boardarr[SIZE][SIZE]; //초기 보드 선언 

int score = 0; //점수 선언 

int turns = 5; // 턴 수 선언 
	char gamestart; //엔터 입력시 게임 시작 - 엔터 받을 변수 선언 
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101\n");
	printf("Assignment 2\n");
	printf("\n");
	printf("[[ Match-3 Game ]]\n");
	printf("\n");
	printf("Press [Enter] to start\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=\n");

	gamestart = _getch();
	if (gamestart == 13) { //엔터 입력 받을 시 게임 시작 - 그 외는 잘못된 입력 출력 뒤 프로그램 종료 
		system("cls");
	}
	else {
		printf("잘못된 입력입니다.\n");
		exit(1);
	}

FILE *f; //파일 선언 
f = fopen("board.txt", "r+"); //txt 파일로 부터 읽어오기 
for (int i = 0; i < SIZE; i++){
	for (int j = 0; j < SIZE; j++){
		fscanf(f, "%d", &boardarr[i][j]);
		}
	}
fclose(f);

while(turns!=0){ //턴 수가 0 이 될 때 까지 반복시작 
	print_board(&score, boardarr);
	int a1, a2;
	int b1, b2;
	int check;
	printf("===========\n\n");
	printf("* Remaining turns: %d\n", turns);
	printf("Swap...\n");
	printf("Block 1:"); //변경할 두 블럭 받기 
	scanf("%d %d", &a1, &a2);
	printf("Block 2:");
	scanf("%d %d", &b1, &b2);
	check = check_position(a1,a2,b1,b2); //블럭이 변경 가능한 인접한 것인지 확인 
	while(check != 1){ //변경 가능한 경우 = check = 1인 경우. 2인 경우는 입력이 잘못 된 것이므로 다시 입력을 받는다 
		if(check == 2){
			system("cls");
			print_board(&score, boardarr);
			printf("============\n\n");
			printf("*** 잘못된 입력! ***\n");
			printf("* Remaining turns: %d\n", turns);
			printf("Swap...\n");
			printf("Block 1:");
			scanf("%d %d", &a1, &a2);
			printf("Block 2:");
			scanf("%d %d", &b1, &b2);
			check = check_position(a1,a2,b1,b2);
			}
	}
	swap(&boardarr[a1][a2], &boardarr[b1][b2]); //두개 위치 변경 
	
	system("cls");
	turns= turns-1; //턴 하나 소모 

}
	print_board(&score, boardarr); //마지막 화면 출력 
	printf("=============\n\n"); 
	
	printf("**You've earned %d points!", score); //최종 스코어 출력 
	exit(0); //종료 
}




void print_board(int *score, int arr[SIZE][SIZE]){
	int checksum=0; //3매치에 해당하는 수가 있는지 확인하기 위한 변수 선언 
do
{	
	int checkarr[SIZE][SIZE] = {
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0}
	}; //checkarr = 0 -> 3매치 적용 x, checkarr = 1 -> 3 매치 적용 O 
	for(int i=0; i<SIZE; i++){ //가로방향으로 3 매치 확인 
		for(int j=1; j<SIZE-1; j++){
			if(arr[i][j]==arr[i][j-1]&&arr[i][j]==arr[i][j+1]){
				checkarr[i][j-1] = 1;
				checkarr[i][j] = 1;
				checkarr[i][j+1] = 1;
			}
		}
	}
	for(int i=1; i<SIZE-1; i++){ //세로 반향으로 3매치 확인 
		for(int j=0; j<SIZE; j++){
			if(arr[i][j]==arr[i-1][j]&&arr[i][j]==arr[i+1][j]){
				checkarr[i-1][j] = 1;
				checkarr[i][j] = 1;
				checkarr[i+1][j] = 1;
			}
		}
	}
	checksum = 0; //checksum 0으로 갱신(이전 반복때 수 날리기 위함) 
	for(int i=0; i<SIZE; i++){
		for (int j=0; j<SIZE; j++){
		checksum+=checkarr[i][j]; //checkarr의 값 합치기 (0이면 3매치 적용되는 칸 x, 그 외에는 3매치 적용되는 칸 있음 
		}
	}
	system("cls");
	printf("Score : %d\n", *score); //score 출력 
	for (int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(checkarr[i][j]==0){
			printf("%d ", arr[i][j]);
		}
			else if(checkarr[i][j]==1){ //checkarr[i][j]인 경우만 붉게 출력 
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

		for(int i=0; i<SIZE; i++){ //checkarr[i][j]와 boardarr[i][j] 의 곱 = score 
			for(int j=0; j<SIZE; j++){
				*score+=arr[i][j]*checkarr[i][j];
			}
		}
		
	system("cls");
	printf("Score : %d\n", *score); //3매치 확인 후 score 출력 
	for(int i=0; i<SIZE; i++){ // checkarr[i][j]=1인 경우 빈칸 출력 
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
	printf("Score : %d\n", *score); //score 출력 
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(checkarr[i][j]==0){
				printf("%d ", arr[i][j]);
			}
			else if(checkarr[i][j]==1){ //checkarr[i][j]가 1인 경우 랜덤으로 새로 값 불러오기 
			arr[i][j] = rand()%5+1;
				printf("%d ", arr[i][j]);
			}	
		}
			printf("| %d \n", i);
	}
	printf("------------+\n");
	printf("0 1 2 3 4 5 \n");
	Sleep(1000);

}while(checksum!=0); //3매치에 해당하는 칸이 없을 때 까지 반복 
}
void swap(int *a, int *b){ //두 수 바꾸기 함수 
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int check_position(int a, int b, int p, int q){ //각 변수가 1~5 사이고, 행 혹은 열 중 하나가 동일하고, 다른 하나가 차이나면 변경 가능한 두 칸임.
												//num = 1이면 변경 가능한 두 칸, 2면 변경 불가능한 두 칸 
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

	return num; //num 반환 
}

