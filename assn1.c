#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// 개발 환경 : Dev C++ 
// 컴파일러 환경에서 -std = c99 추가해야 정상적인 실행이 됩니다. (Dev c++는 VS와 다르게 기본이 C89여서 loop가 되지 않음) 
int print_menu(); //초기 메뉴 화면을 출력하는 함수 
void game_info(); //게임에 대한 설명을 출력하는 함수
void game_start(); //게임 시작 함수 
void print_drink(int round, int user_pos, int user_jan, int com_jan); //user와 com의 잔 수를 출력하는 함수 
void print_map(); // 보드판 출력 함수 
char set_position(int user_pos, int pos); // 유저 말 위치 표시 함수 
void play_juru(int user_pos, int* u_jan, int* c_jan); // 각 칸에 따른 진행을 시키는 함수 
void normal(int* u_jan, int* c_jan); // 일반 칸 실행 함수 
void chance(int* u_jan, int* c_jan); //찬스 칸 실행 함수 
void mission(int* u_jan, int* c_jan); //미션 잔 실행 함수 
void baera(int* u_jan, int* c_jan); //베스킨라벤스31 게임 실행 함수 
void samyukgu(int* u_jan, int* c_jan); //369 게임 실행 함수 

int main() {
		int menu_num; //시작화면 메뉴 번호를 받을 변수 
	int again; // -1을 받을 시 시작화면으로 되돌아오기 위한 변수 
	
while(1){ //무한반복 
	print_menu(); //시작 설명 출력 
	scanf("%d", &menu_num);
	
	switch(menu_num){
		
		case 1: //게임 설명 선택의 경우 
			system("cls");
		game_info(); //게임 설명문 출력 
		scanf("%d", &again);
		if(again==(-1)){
		system("cls");
		}
			break;
			
		case 2:
			system("cls"); //게임 시작 선택의 경우 
			game_start();
			scanf("%d", &again);
			if(again==(-1)){ //게임 종료 후 -1 입력시 시작화면 
			system("cls");	
			break;
		}
		case 3: //게임 종료 선택의 경우 
			printf("프로그램을 종료합니다...");
			exit(0); //프로그램 종료 
			break;
		
		default:
		system("cls");
}
	}
}



int print_menu(){	
	printf(" [주루마블] \n");
	printf("================================== \n");
	printf("	1. 게임 설명 \n");
	printf("	2. 게임 시작 \n");
	printf("	3. 게임 종료 \n");
	printf("================================== \n");
	printf("입력: ");
	}


void game_info() {
	printf("========== 주루마불 게임 설명========== \n");
	printf("1. USER 는 매턴 주사위를 던진다 주사위를 던질 때 주사위의 눈은 플레이어가 결정한다.\n");
	printf("2. COMPUTER 는 주사위를 던지지 않으며 매턴 1 잔의 술을 마신다.\n");
	printf("3. 3. USER 와 COMPUTER 의 주량은 소주 2 병 14 잔 이며 14 잔을 먼저 마신 쪽이 패배한다.\n");
	printf("4. 보드 칸은 5 가지 칸으로 이루어져있으며 USER 는 각 칸의 요구사항을 만족시켜야한다.\n");
	printf("========================================= \n");
	printf("메인 메뉴로 돌아가기(-1): ");

}

void game_start(){
	int choice; //주사위를 돌릴지, 게임을 포기할 지 값을 받는 변수 
	int jusawi; //주사위 값을 받는 변수 
	int user_jan=0; //user의 마신 잔 수(시작=0잔)를 받는 변수 
	int com_jan=0; //com의 마신 잔 수(시작 = 0잔)를 받는 변수 
	int round=0; //라운드 수를 받는 변수 
	int position=0; //user 말의 위치를 받을 변수 
	printf("[주루마블 게임]\n");
	printf("=================\n");
	print_map(0); //초기 판 출력 
	print_drink(0, 0, 0, 0); //초기 잔 수 출력 
	
	
	while(user_jan<14 && com_jan<14){ //user와 com의 잔 수가 14가 되기 전까지 계속 반복 
		printf("주사위를 굴리겠습니까? (0-굴림, -1-게임포기): ");
		scanf("%d", &choice);
	if(choice==0){ //choice 값이 0일씨 1~6 사이 값 랜덤으로 jusawi값 설정 
		srand(time(NULL));
		jusawi = rand() % 6 + 1;
	}
	else if(choice==-1){ // choice 값이 -1 일시 화면 지우고 break를 통해 초기로 돌아감 
		system("cls");
		break;
	}
	
	else if(choice>=1 && choice <=6){ //디버깅을 위해, 1~6값 입력시 그 값이 jusawi에 들어가도록 설정 
		jusawi = choice;
	}
	else{ //그 외의 이상 값의 경우 재입력 요구 
		printf("다시 입력하세요\n");
		scanf("%d", &choice);
	}
	system("cls");
	round++; //라운드 수 1 추가 

	position = (position+jusawi)%12; //말의 위치 = (기존 말의 위치 값+주사위 값)을 12로 나눈 나머지 
	printf("================\n");
	printf("▶▶▶ ROUND %d ▶▶▶▶▶▶▶▶▶▶▶▶\n", round); //라운드 값 출력 
	printf("================\n");
	printf("[USER's Turn']\n");
	printf("-------------------\n");
	printf("주사위 눈: %d\n", jusawi); //주사위 값 출력 
	print_map(position); //변한 말의 위치 출력 
	
	play_juru(position, &user_jan, &com_jan); //말의 위치에 맞는 행동 실행 

	print_drink(round, position, user_jan, com_jan); //행동 후 변화한 잔 수 출력 
	printf("\n");
	
}
 	if(user_jan>=14){ //user의 술잔이 14를 넘어 갈 시(com 승리) com 승리 문구 출력 
 		printf("*결과 COMPUTER가 승리하였습니다. \n");
		printf("메인 메뉴로 돌아가기(-1): "); //아무 값 입력받을시 main 문의 while(1)로 인해 메인메뉴로 돌아감.(-1 이외 입력 생각 안함) 
		}
	if(com_jan>=14){ //com의 술잔이 14를 넘어갈 시 (user 승리) user 승리 문구 출력 
		printf("*결과 USER가 승리하였습니다.\n");
		printf("메인 메뉴로 돌아가기(-1): "); //아무 값 입력받을시 main 문의 while(1)로 인해 메인메뉴로 돌아감.(-1 이외 입력 생각 안함)
	}
		 
	}

void print_map(int user_pos){ //각 칸에 set_position 함수를 통해 말 위치 출력 
	printf("+-------+-------+-------+-------+\n");
	printf("|미션 %c |찬스 %c |일반 %c |휴식 %c |\n", set_position(user_pos,9), set_position(user_pos, 8), set_position(user_pos, 7), set_position(user_pos, 6));
	printf("+-------+-------+-------+-------+\n");
	printf("|일반 %c |       |       |일반 %c |\n", set_position(user_pos, 10), set_position(user_pos,5));
	printf("+-------+-------+-------+-------+\n");
	printf("|일반 %c |       |       |일반 %c |\n", set_position(user_pos, 11), set_position(user_pos, 4));
	printf("+-------+-------+-------+-------+\n");
	printf("|시작 %c |일반 %c |찬스 %c |미션 %c |\n", set_position(user_pos, 0), set_position(user_pos, 1), set_position(user_pos, 2), set_position(user_pos, 3));
	printf("+-------+-------+-------+-------+\n");

}
void print_drink(int round, int user_pos, int user_jan, int com_jan){
	printf("=========================\n");
	printf("[USER - %d] (%d / 14)\n", user_pos, user_jan); //user 위치와 잔 수 출력 
	for(int i=0; i<user_jan; i++){  //반복문을 통해 유저 잔 수만큼  ■를, (14- 유저 잔 수)만큼  □ 를 출력 
		printf("■");
	}
	for(int j=0; j<(14-user_jan); j++){
		printf("□");
	}

	printf("\n");
	printf("[COMP - 0] (%d / 14)\n", com_jan); //com 잔 수 출력 

	for(int k=0; k<com_jan; k++){ //반복문을 통해 com 잔 수만큼  ■를, (14- com 잔  수)만큼  □ 를 출력
		printf("■");
	}
	for(int l=0; l<(14-com_jan); l++){  
		printf("□");
	}
	printf("\n");
	printf("=========================\n");
	
}
char set_position(int user_pos, int pos){ // 유저 위치와 각 칸에 할당된 위치 번호와 같을 시 0 출력, 다를 시 공백출력 
	if (user_pos==pos){
		return '0';
	}
	else{
		return ' ';
	}
}

void play_juru(int user_pos, int* u_jan, int* c_jan){ //각 칸에 따른 실행 
	switch(user_pos){
		case 0: //시작 칸 : 유저 잔 수 안변함, 컴퓨터 잔 수 1 증가 
			printf("시작 칸에 도착하였습니다.\n");
			printf("이번 턴은 아무것도 하지 않습니다.\n");
			printf("[COMPUTER's Turn']\n");
			printf("-------------------\n");
			printf("COMPUTER가 1잔 마시게 되었습니다.\n");
			*c_jan+=1;
				if(*c_jan>=14){ //컴퓨터 잔 수가 14이상일 시 14로 변환하고 게임 종료 
					*c_jan=14;
				printf("게임이 종료되었습니다.\n");
				}
			break;
		case 1: //일반 칸 함수 실행 
			 normal(u_jan, c_jan);
			
			break;
		case 2: //찬스 칸 함수 실행 
			chance(u_jan, c_jan);
			break;
		case 3: //미션 칸 함수 실행 
			mission(u_jan, c_jan);
			break;
		case 4: //일반 칸 함수 실행 
			normal(u_jan, c_jan);

			break;
		case 5: //일반 칸 함수 실행 
			normal(u_jan, c_jan);

			break;
		case 6: // 휴식 칸 실행, 유저 잔 수 변화 없음, com 잔수 1 증가 
			printf("휴식 칸에 도착하였습니다.\n");
			printf("이번 턴은 아무것도 하지 않습니다.\n");
			printf("[COMPUTER's Turn']\n");
			printf("-------------------\n");
			printf("COMPUTER가 1잔 마시게 되었습니다.\n");
			*c_jan+=1;
				if(*c_jan>=14){ //com 잔이 14 이상일 시 14로 변환하고 게임 종료 
					*c_jan=14;
				printf("게임이 종료되었습니다.\n");
				}
			break;
		case 7: //일반 칸 함수 실행 
			normal(u_jan, c_jan);

			break;
		case 8: //찬스 칸 함수 실행 
			chance(u_jan, c_jan);
			break;
		case 9: //미션 칸 함수 실행 
			mission(u_jan, c_jan);
			break;
		case 10: //일반 칸 함수 실행 
			normal(u_jan, c_jan);
			break;
		case 11: //일반 칸 함수 실행 
			normal(u_jan, c_jan);
			break;

	}
		
}
void normal(int* u_jan, int* c_jan){ //일반 칸 문구 출력, 유저 잔 수 1 증가, 컴퓨터 잔 수 1 증가 
	printf("일반 칸에 도착하였습니다.\n");
	printf("USER가 1잔 마시게 됩니다.\n");
	*u_jan+=1;
	if(*u_jan>=14){ //유저 잔 수가 14 이상일 시, 잔 수를 14로 변환하고 게임 종료 
		*u_jan=14;
		printf("게임이 종료되었습니다.\n");
	}
	else{
	printf("[COMPUTER's Turn']\n");
	printf("-------------------\n");
	printf("COMPUTER가 1잔 마시게 되었습니다.\n");
	*c_jan+=1;
	if(*c_jan>=14){ // com 잔 수가 14 이상일 시, 잔 수를 14로 변환하고 게임 종료 
		*c_jan=14;
		printf("게임이 종료되었습니다.\n");
	}
}

}
void chance(int* u_jan, int* c_jan){ //찬스 칸 문구 출력 
	printf("찬스 칸에 도착하였습니다. \n");
	int chancerand; 
	chancerand = rand() % 2; //세잔 더! 와 여명 808을 랜덤으로 뽑기 위해 chancerand 변수 선언, rand()를 통해 0과 1을 랜덤으로 받게 함. 0일 시 세잔 더!, 1일 시 여명 808 실행. 
	switch(chancerand){
		case 0:
			printf("'세잔 더!' 카드를 뽑았습니다.\n");
			printf("USER가 3잔 더 마시게 되었습니다.\n"); //유저 3잔 추가 
			*u_jan+=3;
				if(*u_jan>=14){ // 유저 잔 수가 14 이상일 시 14로 변환하고 게임 종료 
					*u_jan=14;
				printf("게임이 종료되었습니다.\n");
				}
			break;
		case 1:
			printf("'여명 808' 카드를 뽑았습니다.\n");
			printf("USER가 -2잔 마시게 되었습니다.\n"); 
			if(*u_jan <=1){ //유저 잔 수가 0, 1 일 시, 0잔으로 변환 
				*u_jan = 0;
			}
			else{	//유저 잔 수 2잔 감소 
			*u_jan-=2;
			}
			
	}
	if(*c_jan<14&&*u_jan<14){ //유저 잔과 컴퓨터 잔이 모두 14잔 아래일 때, 컴퓨터 잔 수 1잔 증가 

	printf("[COMPUTER's Turn']\n");
	printf("-------------------\n");
	printf("COMPUTER가 1잔 마시게 되었습니다.\n");
	*c_jan+=1;
		if(*c_jan>=14){ //컴퓨터 잔 수가 14 이상이 되었을 시, 14로 변환하고 게임 종료 
			*c_jan=14;
		printf("게임이 종료되었습니다.\n");
		}
	}
}
void mission(int* u_jan, int*c_jan){ //베스킨라벤스 게임과 369게임을 무작위로 실행하기 위해 missionrand 변수 선언, rand()를 통해 0과 1을 랜덤으로 받게 함. 0일 시 베스킨라벤스, 1일 시 369 게임 실행. 
	printf("미션 칸에 도착하였습니다.\n");
	int missionrand;
	missionrand = rand()%2;
	switch(missionrand){
		case 0:
			baera(u_jan, c_jan);
			break;
		case 1:
			samyukgu(u_jan, c_jan);
			break;
	}
}
void baera(int* u_jan, int* c_jan){ //베스킨라벤스 게임 
	int startrand = rand()%2; //com이 먼저 시작할 지, user가 먼저 시작할 지 선택하기 위해 랜덤으로 startrand 값을 받음. 0일 시 유저 먼저, 1일 시 com 먼저 시작. 
	int num=0; //유저가 입력한 값과 com이 입력한 값의 합. num이 31 이상이 될 시 게임 종료 
	int usercount; //유저가 입력한 수 
	int compcount; //com가 출력할 수 
	printf("베스킨라빈스 게임이 선택되었습니다.\n");
	printf("----------------\n");
	printf("★★★★★ 베스킨라빈스 게임 ★★★★★\n");
	printf("---------------\n");
	if(startrand==0){ 	//USER먼저 
		while(1){
			printf("USER>>");  
			scanf("%d", &usercount);
			while(usercount>3||usercount<1){ //유저가 입력한 값이 1,2,3이 아닐 시 wrong input을 출력하고 다시 입력받게 함 
				printf("WRONG INPUT!\n");
				printf("USER>>");
				scanf("%d", &usercount);
			}
			
			for(int i=0; i<usercount; i++){ //for 문을 통해 입력받은 수 만큼의 수 출력 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
				
			}
			printf("\n");
			if(num>=31) //num이 31이 넘어 갈 시, com 승리 
			{
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n"); //user  4잔 추가 
				*u_jan +=4;
						if(*u_jan>=14){ //유저 잔 수가 14 이상일 시 user 잔 수를 14로 변환하고 게임 종료 
							*u_jan=14;
							printf("게임이 종료되었습니다.\n");
							break; 
							}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}
			 compcount= rand()%3+1; //compcount 값이 1~3 사이 랜덤으로 나오도록 함 
			printf("COMP>>%d\n", compcount);
			for(int i = 0; i<compcount; i++){ //compcount 값 만큼 숫자 출력 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
			}
			printf("\n");
			if(num>=31){ //num이 31 이상일 시, user 승리 
			printf("-------------\n");
			printf("USER가 승리하였습니다.\n");
			printf("COMPUTER가 4잔 마시게 되었습니다.\n");  
			*c_jan+=4; //com 잔 수 4 증가 
						if(*c_jan>=14){  //com 잔 수가 14 이상일 시, com 잔 수를 14로 변환하고, 게임 종료 
							*c_jan=14;
							printf("게임이 종료되었습니다.\n");
							break; 
							}			
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER가 0잔 마시게 되었습니다. \n");
			break;
			}
		}
	}
	else{ 	//comp먼저 
		while(1){
			compcount = rand()%3+1;
			printf("COMP>>%d\n", compcount);
			for(int i = 0; i<compcount; i++){
				num++;
				if(num<=31){
					printf("%d ", num); //compcount 값 만큼 수 출력 
				}
				
			}
			printf("\n");
			if(num>=31){ //num이 31 이상일 시 user 승리 
			printf("-------------\n");
			printf("USER가 승리하였습니다.\n");
			printf("COMPUTER가 4잔 마시게 되었습니다.\n");
			*c_jan+=4;
				if(*c_jan>=14){ //com 잔 수 증가 시 com 잔 수 14로 변환하고 게임 종료 
					*c_jan=14;
				printf("게임이 종료되었습니다.\n");
				break; 
				}
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER가 0잔 마시게 되었습니다. \n");
			break;
			}
			
			printf("USER>>");  
			scanf("%d", &usercount);
			while(usercount>3||usercount<1){ //유저가 입력한 값이 1,2,3이 아닐 시 wrong input을 출력하고 다시 입력받게 함 
				printf("WRONG INPUT!\n");
				printf("USER>>");
				scanf("%d", &usercount);
			}
			for(int i=0; i<usercount; i++){ //usercount 값 만큼 숫자 출력 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
				
			}
			printf("\n");
			if(num>=31) //num 값이 31 이상일 시 com 승리 ,user 4잔 추가 
			{
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n");
				*u_jan +=4;
				if(*u_jan>=14){ //user  잔 수가 14 이상일 시 14로 변환 후  게임 종료 
					*u_jan=14;
					printf("게임이 종료되었습니다.\n");
					break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}

		}
	}
		
	}
void samyukgu(int* u_jan, int* c_jan){ // 369 게임 
	printf("369 게임이 선택되었습니다.\n");
	printf("----------------\n");
	printf("★★★★★ 369 게임 ★★★★★\n");
	printf("---------------\n");
	int startrand; // user, com 중 랜덤으로 먼저 시작하게 하기 위해 startrand 변수 선언 
	int correct; //user의 입력 값 
	int i,j,h;  
	startrand = rand()%2; //startrand값이 0, 1 중 랜덤으로 정해지게 함. 
	if (startrand==0){		 //com 먼저 시 작 
	for(i=1; i<20; i++){
		if(i%10==3||i%10==6||i%10==9){ //3, 6, 9, 13, 16, 19 일시 com은 0 출력 
			printf("COMP>>0\n");
		}
		else{ //아닌 경우 제 값 출력 
		printf("COMP>>%d\n", i);
		}
		i+=1; //i 1 증가 
		printf("USER>>");
		scanf("%d",&correct); //user 값 입력 
		if(i%10==3||i%10==6||i%10==9){ //3, 6, 9, 13, 16, 19 일 시  0이 입력되어야 함. 아닐 시 com 승리, user 잔수 4 증가. 
			if(correct!=0){

				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n");
				*u_jan +=4;
					if(*u_jan>=14){ //user  잔 수 14 이상일 시, 14로 변환 후 게임 종료 
						*u_jan=14;
					printf("게임이 종료되었습니다.\n");
					break; 
					}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}
		}
		else{
			if(correct!=i){ //correct 와 i 가 다를 시 com 승리, user 잔 수 4 증가.  
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n");
				*u_jan +=4;
				if(*u_jan>=14){ //user 잔 수가 14 이상일 시 14로 변환 후 게임 종료 
					*u_jan=14;
				printf("게임이 종료되었습니다.\n");
				break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}
		}

	if(i==20){ //for 문에서 i=20까지만 실행됨. 이후 마지막 21을 com이 출력해줘야함 

	printf("COMP>>21\n");
	printf("-------------\n");
	printf("USER가 승리하였습니다.\n");
	printf("COMPUTER가 4잔 마시게 되었습니다.\n");
	*c_jan+=4;
	if(*c_jan>=14){ //com 잔 수 4 추가, com 잔 수가 14 이상일 시 14로 변환하고 게임 종료 
		*c_jan=14;
	printf("게임이 종료되었습니다.\n");
	}
	if(*c_jan<14){
	printf("[COMPUTER's Turn']\n");
	printf("----------------\n");
	printf("COMPUTER가 0잔 마시게 되었습니다. \n");
	}
	}
	}
	}
	
	else{				//유저 먼저 시작 
	
	for(int j=1; j<21; j++){ //com 먼저 시작하는 경우와 같은 과정으로 코드 진행 
		printf("USER>>");
		scanf("%d",&correct);
		 if(j%10==3||j%10==6||j%10==9){
			if(correct==0){
				j+=1;
				printf("COMP>>%d\n", j);
			}
			else{
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n");
				*u_jan +=4;
				if(*u_jan>=14){
					*u_jan=14;
					printf("게임이 종료되었습니다.\n");
					break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}
			}	
		else{	
				
				if(correct==j){
				j+=1;
					if(j%10==3||j%10==6||j%10==9){
					printf("COMP>>0\n");
					}
					else{
					printf("COMP>>%d\n", j);
				}
				}
			
				else{
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n");
				*u_jan +=4;
					if(*u_jan>=14){
						*u_jan=14;
						printf("게임이 종료되었습니다.\n");
						break; 
					}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");
				break;
			}
		}
		if(j==20){ //마지막 입력이 21이 맞을 경우 user 승리, 아닐경우 com 승리 
		printf("USER>>");
		scanf("%d", &h);
			if (h==21){
			printf("-------------\n");
			printf("USER가 승리하였습니다.\n");
			printf("COMPUTER가 4잔 마시게 되었습니다.\n"); //com 4잔 추가, 14잔 이상일 시 14잔으로 변환하고 게임 종료 
			*c_jan+=4;
				if(*c_jan>=14){
					*c_jan=14;
					printf("게임이 종료되었습니다.\n");
					break; 
				}
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER가 0잔 마시게 되었습니다. \n");
			}
			else{
				printf("----------------\n");
				printf("COMPUTER가 승리하였습니다.\n");
				printf("USER가 4잔 마시게 되었습니다. \n"); //user 4잔 추가, 14잔 이상일 시 14잔으로 변환하고 게임 종료 
				*u_jan +=4;
						if(*u_jan>=14){ 
							*u_jan=14;
							printf("게임이 종료되었습니다.\n");
							break; 
							}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER가 0잔 마시게 되었습니다.\n");	
			}
	}
}
}
}
