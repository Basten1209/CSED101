#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// ���� ȯ�� : Dev C++ 
// �����Ϸ� ȯ�濡�� -std = c99 �߰��ؾ� �������� ������ �˴ϴ�. (Dev c++�� VS�� �ٸ��� �⺻�� C89���� loop�� ���� ����) 
int print_menu(); //�ʱ� �޴� ȭ���� ����ϴ� �Լ� 
void game_info(); //���ӿ� ���� ������ ����ϴ� �Լ�
void game_start(); //���� ���� �Լ� 
void print_drink(int round, int user_pos, int user_jan, int com_jan); //user�� com�� �� ���� ����ϴ� �Լ� 
void print_map(); // ������ ��� �Լ� 
char set_position(int user_pos, int pos); // ���� �� ��ġ ǥ�� �Լ� 
void play_juru(int user_pos, int* u_jan, int* c_jan); // �� ĭ�� ���� ������ ��Ű�� �Լ� 
void normal(int* u_jan, int* c_jan); // �Ϲ� ĭ ���� �Լ� 
void chance(int* u_jan, int* c_jan); //���� ĭ ���� �Լ� 
void mission(int* u_jan, int* c_jan); //�̼� �� ���� �Լ� 
void baera(int* u_jan, int* c_jan); //����Ų�󺥽�31 ���� ���� �Լ� 
void samyukgu(int* u_jan, int* c_jan); //369 ���� ���� �Լ� 

int main() {
		int menu_num; //����ȭ�� �޴� ��ȣ�� ���� ���� 
	int again; // -1�� ���� �� ����ȭ������ �ǵ��ƿ��� ���� ���� 
	
while(1){ //���ѹݺ� 
	print_menu(); //���� ���� ��� 
	scanf("%d", &menu_num);
	
	switch(menu_num){
		
		case 1: //���� ���� ������ ��� 
			system("cls");
		game_info(); //���� ���� ��� 
		scanf("%d", &again);
		if(again==(-1)){
		system("cls");
		}
			break;
			
		case 2:
			system("cls"); //���� ���� ������ ��� 
			game_start();
			scanf("%d", &again);
			if(again==(-1)){ //���� ���� �� -1 �Է½� ����ȭ�� 
			system("cls");	
			break;
		}
		case 3: //���� ���� ������ ��� 
			printf("���α׷��� �����մϴ�...");
			exit(0); //���α׷� ���� 
			break;
		
		default:
		system("cls");
}
	}
}



int print_menu(){	
	printf(" [�ַ縶��] \n");
	printf("================================== \n");
	printf("	1. ���� ���� \n");
	printf("	2. ���� ���� \n");
	printf("	3. ���� ���� \n");
	printf("================================== \n");
	printf("�Է�: ");
	}


void game_info() {
	printf("========== �ַ縶�� ���� ����========== \n");
	printf("1. USER �� ���� �ֻ����� ������ �ֻ����� ���� �� �ֻ����� ���� �÷��̾ �����Ѵ�.\n");
	printf("2. COMPUTER �� �ֻ����� ������ ������ ���� 1 ���� ���� ���Ŵ�.\n");
	printf("3. 3. USER �� COMPUTER �� �ַ��� ���� 2 �� 14 �� �̸� 14 ���� ���� ���� ���� �й��Ѵ�.\n");
	printf("4. ���� ĭ�� 5 ���� ĭ���� �̷���������� USER �� �� ĭ�� �䱸������ �������Ѿ��Ѵ�.\n");
	printf("========================================= \n");
	printf("���� �޴��� ���ư���(-1): ");

}

void game_start(){
	int choice; //�ֻ����� ������, ������ ������ �� ���� �޴� ���� 
	int jusawi; //�ֻ��� ���� �޴� ���� 
	int user_jan=0; //user�� ���� �� ��(����=0��)�� �޴� ���� 
	int com_jan=0; //com�� ���� �� ��(���� = 0��)�� �޴� ���� 
	int round=0; //���� ���� �޴� ���� 
	int position=0; //user ���� ��ġ�� ���� ���� 
	printf("[�ַ縶�� ����]\n");
	printf("=================\n");
	print_map(0); //�ʱ� �� ��� 
	print_drink(0, 0, 0, 0); //�ʱ� �� �� ��� 
	
	
	while(user_jan<14 && com_jan<14){ //user�� com�� �� ���� 14�� �Ǳ� ������ ��� �ݺ� 
		printf("�ֻ����� �����ڽ��ϱ�? (0-����, -1-��������): ");
		scanf("%d", &choice);
	if(choice==0){ //choice ���� 0�Ͼ� 1~6 ���� �� �������� jusawi�� ���� 
		srand(time(NULL));
		jusawi = rand() % 6 + 1;
	}
	else if(choice==-1){ // choice ���� -1 �Ͻ� ȭ�� ����� break�� ���� �ʱ�� ���ư� 
		system("cls");
		break;
	}
	
	else if(choice>=1 && choice <=6){ //������� ����, 1~6�� �Է½� �� ���� jusawi�� ������ ���� 
		jusawi = choice;
	}
	else{ //�� ���� �̻� ���� ��� ���Է� �䱸 
		printf("�ٽ� �Է��ϼ���\n");
		scanf("%d", &choice);
	}
	system("cls");
	round++; //���� �� 1 �߰� 

	position = (position+jusawi)%12; //���� ��ġ = (���� ���� ��ġ ��+�ֻ��� ��)�� 12�� ���� ������ 
	printf("================\n");
	printf("������ ROUND %d ������������������������\n", round); //���� �� ��� 
	printf("================\n");
	printf("[USER's Turn']\n");
	printf("-------------------\n");
	printf("�ֻ��� ��: %d\n", jusawi); //�ֻ��� �� ��� 
	print_map(position); //���� ���� ��ġ ��� 
	
	play_juru(position, &user_jan, &com_jan); //���� ��ġ�� �´� �ൿ ���� 

	print_drink(round, position, user_jan, com_jan); //�ൿ �� ��ȭ�� �� �� ��� 
	printf("\n");
	
}
 	if(user_jan>=14){ //user�� ������ 14�� �Ѿ� �� ��(com �¸�) com �¸� ���� ��� 
 		printf("*��� COMPUTER�� �¸��Ͽ����ϴ�. \n");
		printf("���� �޴��� ���ư���(-1): "); //�ƹ� �� �Է¹����� main ���� while(1)�� ���� ���θ޴��� ���ư�.(-1 �̿� �Է� ���� ����) 
		}
	if(com_jan>=14){ //com�� ������ 14�� �Ѿ �� (user �¸�) user �¸� ���� ��� 
		printf("*��� USER�� �¸��Ͽ����ϴ�.\n");
		printf("���� �޴��� ���ư���(-1): "); //�ƹ� �� �Է¹����� main ���� while(1)�� ���� ���θ޴��� ���ư�.(-1 �̿� �Է� ���� ����)
	}
		 
	}

void print_map(int user_pos){ //�� ĭ�� set_position �Լ��� ���� �� ��ġ ��� 
	printf("+-------+-------+-------+-------+\n");
	printf("|�̼� %c |���� %c |�Ϲ� %c |�޽� %c |\n", set_position(user_pos,9), set_position(user_pos, 8), set_position(user_pos, 7), set_position(user_pos, 6));
	printf("+-------+-------+-------+-------+\n");
	printf("|�Ϲ� %c |       |       |�Ϲ� %c |\n", set_position(user_pos, 10), set_position(user_pos,5));
	printf("+-------+-------+-------+-------+\n");
	printf("|�Ϲ� %c |       |       |�Ϲ� %c |\n", set_position(user_pos, 11), set_position(user_pos, 4));
	printf("+-------+-------+-------+-------+\n");
	printf("|���� %c |�Ϲ� %c |���� %c |�̼� %c |\n", set_position(user_pos, 0), set_position(user_pos, 1), set_position(user_pos, 2), set_position(user_pos, 3));
	printf("+-------+-------+-------+-------+\n");

}
void print_drink(int round, int user_pos, int user_jan, int com_jan){
	printf("=========================\n");
	printf("[USER - %d] (%d / 14)\n", user_pos, user_jan); //user ��ġ�� �� �� ��� 
	for(int i=0; i<user_jan; i++){  //�ݺ����� ���� ���� �� ����ŭ  �Ḧ, (14- ���� �� ��)��ŭ  �� �� ��� 
		printf("��");
	}
	for(int j=0; j<(14-user_jan); j++){
		printf("��");
	}

	printf("\n");
	printf("[COMP - 0] (%d / 14)\n", com_jan); //com �� �� ��� 

	for(int k=0; k<com_jan; k++){ //�ݺ����� ���� com �� ����ŭ  �Ḧ, (14- com ��  ��)��ŭ  �� �� ���
		printf("��");
	}
	for(int l=0; l<(14-com_jan); l++){  
		printf("��");
	}
	printf("\n");
	printf("=========================\n");
	
}
char set_position(int user_pos, int pos){ // ���� ��ġ�� �� ĭ�� �Ҵ�� ��ġ ��ȣ�� ���� �� 0 ���, �ٸ� �� ������� 
	if (user_pos==pos){
		return '0';
	}
	else{
		return ' ';
	}
}

void play_juru(int user_pos, int* u_jan, int* c_jan){ //�� ĭ�� ���� ���� 
	switch(user_pos){
		case 0: //���� ĭ : ���� �� �� �Ⱥ���, ��ǻ�� �� �� 1 ���� 
			printf("���� ĭ�� �����Ͽ����ϴ�.\n");
			printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
			printf("[COMPUTER's Turn']\n");
			printf("-------------------\n");
			printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n");
			*c_jan+=1;
				if(*c_jan>=14){ //��ǻ�� �� ���� 14�̻��� �� 14�� ��ȯ�ϰ� ���� ���� 
					*c_jan=14;
				printf("������ ����Ǿ����ϴ�.\n");
				}
			break;
		case 1: //�Ϲ� ĭ �Լ� ���� 
			 normal(u_jan, c_jan);
			
			break;
		case 2: //���� ĭ �Լ� ���� 
			chance(u_jan, c_jan);
			break;
		case 3: //�̼� ĭ �Լ� ���� 
			mission(u_jan, c_jan);
			break;
		case 4: //�Ϲ� ĭ �Լ� ���� 
			normal(u_jan, c_jan);

			break;
		case 5: //�Ϲ� ĭ �Լ� ���� 
			normal(u_jan, c_jan);

			break;
		case 6: // �޽� ĭ ����, ���� �� �� ��ȭ ����, com �ܼ� 1 ���� 
			printf("�޽� ĭ�� �����Ͽ����ϴ�.\n");
			printf("�̹� ���� �ƹ��͵� ���� �ʽ��ϴ�.\n");
			printf("[COMPUTER's Turn']\n");
			printf("-------------------\n");
			printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n");
			*c_jan+=1;
				if(*c_jan>=14){ //com ���� 14 �̻��� �� 14�� ��ȯ�ϰ� ���� ���� 
					*c_jan=14;
				printf("������ ����Ǿ����ϴ�.\n");
				}
			break;
		case 7: //�Ϲ� ĭ �Լ� ���� 
			normal(u_jan, c_jan);

			break;
		case 8: //���� ĭ �Լ� ���� 
			chance(u_jan, c_jan);
			break;
		case 9: //�̼� ĭ �Լ� ���� 
			mission(u_jan, c_jan);
			break;
		case 10: //�Ϲ� ĭ �Լ� ���� 
			normal(u_jan, c_jan);
			break;
		case 11: //�Ϲ� ĭ �Լ� ���� 
			normal(u_jan, c_jan);
			break;

	}
		
}
void normal(int* u_jan, int* c_jan){ //�Ϲ� ĭ ���� ���, ���� �� �� 1 ����, ��ǻ�� �� �� 1 ���� 
	printf("�Ϲ� ĭ�� �����Ͽ����ϴ�.\n");
	printf("USER�� 1�� ���ð� �˴ϴ�.\n");
	*u_jan+=1;
	if(*u_jan>=14){ //���� �� ���� 14 �̻��� ��, �� ���� 14�� ��ȯ�ϰ� ���� ���� 
		*u_jan=14;
		printf("������ ����Ǿ����ϴ�.\n");
	}
	else{
	printf("[COMPUTER's Turn']\n");
	printf("-------------------\n");
	printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n");
	*c_jan+=1;
	if(*c_jan>=14){ // com �� ���� 14 �̻��� ��, �� ���� 14�� ��ȯ�ϰ� ���� ���� 
		*c_jan=14;
		printf("������ ����Ǿ����ϴ�.\n");
	}
}

}
void chance(int* u_jan, int* c_jan){ //���� ĭ ���� ��� 
	printf("���� ĭ�� �����Ͽ����ϴ�. \n");
	int chancerand; 
	chancerand = rand() % 2; //���� ��! �� ���� 808�� �������� �̱� ���� chancerand ���� ����, rand()�� ���� 0�� 1�� �������� �ް� ��. 0�� �� ���� ��!, 1�� �� ���� 808 ����. 
	switch(chancerand){
		case 0:
			printf("'���� ��!' ī�带 �̾ҽ��ϴ�.\n");
			printf("USER�� 3�� �� ���ð� �Ǿ����ϴ�.\n"); //���� 3�� �߰� 
			*u_jan+=3;
				if(*u_jan>=14){ // ���� �� ���� 14 �̻��� �� 14�� ��ȯ�ϰ� ���� ���� 
					*u_jan=14;
				printf("������ ����Ǿ����ϴ�.\n");
				}
			break;
		case 1:
			printf("'���� 808' ī�带 �̾ҽ��ϴ�.\n");
			printf("USER�� -2�� ���ð� �Ǿ����ϴ�.\n"); 
			if(*u_jan <=1){ //���� �� ���� 0, 1 �� ��, 0������ ��ȯ 
				*u_jan = 0;
			}
			else{	//���� �� �� 2�� ���� 
			*u_jan-=2;
			}
			
	}
	if(*c_jan<14&&*u_jan<14){ //���� �ܰ� ��ǻ�� ���� ��� 14�� �Ʒ��� ��, ��ǻ�� �� �� 1�� ���� 

	printf("[COMPUTER's Turn']\n");
	printf("-------------------\n");
	printf("COMPUTER�� 1�� ���ð� �Ǿ����ϴ�.\n");
	*c_jan+=1;
		if(*c_jan>=14){ //��ǻ�� �� ���� 14 �̻��� �Ǿ��� ��, 14�� ��ȯ�ϰ� ���� ���� 
			*c_jan=14;
		printf("������ ����Ǿ����ϴ�.\n");
		}
	}
}
void mission(int* u_jan, int*c_jan){ //����Ų�󺥽� ���Ӱ� 369������ �������� �����ϱ� ���� missionrand ���� ����, rand()�� ���� 0�� 1�� �������� �ް� ��. 0�� �� ����Ų�󺥽�, 1�� �� 369 ���� ����. 
	printf("�̼� ĭ�� �����Ͽ����ϴ�.\n");
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
void baera(int* u_jan, int* c_jan){ //����Ų�󺥽� ���� 
	int startrand = rand()%2; //com�� ���� ������ ��, user�� ���� ������ �� �����ϱ� ���� �������� startrand ���� ����. 0�� �� ���� ����, 1�� �� com ���� ����. 
	int num=0; //������ �Է��� ���� com�� �Է��� ���� ��. num�� 31 �̻��� �� �� ���� ���� 
	int usercount; //������ �Է��� �� 
	int compcount; //com�� ����� �� 
	printf("����Ų��� ������ ���õǾ����ϴ�.\n");
	printf("----------------\n");
	printf("�ڡڡڡڡ� ����Ų��� ���� �ڡڡڡڡ�\n");
	printf("---------------\n");
	if(startrand==0){ 	//USER���� 
		while(1){
			printf("USER>>");  
			scanf("%d", &usercount);
			while(usercount>3||usercount<1){ //������ �Է��� ���� 1,2,3�� �ƴ� �� wrong input�� ����ϰ� �ٽ� �Է¹ް� �� 
				printf("WRONG INPUT!\n");
				printf("USER>>");
				scanf("%d", &usercount);
			}
			
			for(int i=0; i<usercount; i++){ //for ���� ���� �Է¹��� �� ��ŭ�� �� ��� 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
				
			}
			printf("\n");
			if(num>=31) //num�� 31�� �Ѿ� �� ��, com �¸� 
			{
				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n"); //user  4�� �߰� 
				*u_jan +=4;
						if(*u_jan>=14){ //���� �� ���� 14 �̻��� �� user �� ���� 14�� ��ȯ�ϰ� ���� ���� 
							*u_jan=14;
							printf("������ ����Ǿ����ϴ�.\n");
							break; 
							}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
				break;
			}
			 compcount= rand()%3+1; //compcount ���� 1~3 ���� �������� �������� �� 
			printf("COMP>>%d\n", compcount);
			for(int i = 0; i<compcount; i++){ //compcount �� ��ŭ ���� ��� 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
			}
			printf("\n");
			if(num>=31){ //num�� 31 �̻��� ��, user �¸� 
			printf("-------------\n");
			printf("USER�� �¸��Ͽ����ϴ�.\n");
			printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");  
			*c_jan+=4; //com �� �� 4 ���� 
						if(*c_jan>=14){  //com �� ���� 14 �̻��� ��, com �� ���� 14�� ��ȯ�ϰ�, ���� ���� 
							*c_jan=14;
							printf("������ ����Ǿ����ϴ�.\n");
							break; 
							}			
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�. \n");
			break;
			}
		}
	}
	else{ 	//comp���� 
		while(1){
			compcount = rand()%3+1;
			printf("COMP>>%d\n", compcount);
			for(int i = 0; i<compcount; i++){
				num++;
				if(num<=31){
					printf("%d ", num); //compcount �� ��ŭ �� ��� 
				}
				
			}
			printf("\n");
			if(num>=31){ //num�� 31 �̻��� �� user �¸� 
			printf("-------------\n");
			printf("USER�� �¸��Ͽ����ϴ�.\n");
			printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
			*c_jan+=4;
				if(*c_jan>=14){ //com �� �� ���� �� com �� �� 14�� ��ȯ�ϰ� ���� ���� 
					*c_jan=14;
				printf("������ ����Ǿ����ϴ�.\n");
				break; 
				}
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�. \n");
			break;
			}
			
			printf("USER>>");  
			scanf("%d", &usercount);
			while(usercount>3||usercount<1){ //������ �Է��� ���� 1,2,3�� �ƴ� �� wrong input�� ����ϰ� �ٽ� �Է¹ް� �� 
				printf("WRONG INPUT!\n");
				printf("USER>>");
				scanf("%d", &usercount);
			}
			for(int i=0; i<usercount; i++){ //usercount �� ��ŭ ���� ��� 
				num++;
				if(num<=31){
					printf("%d ", num);
				}
				
			}
			printf("\n");
			if(num>=31) //num ���� 31 �̻��� �� com �¸� ,user 4�� �߰� 
			{
				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n");
				*u_jan +=4;
				if(*u_jan>=14){ //user  �� ���� 14 �̻��� �� 14�� ��ȯ ��  ���� ���� 
					*u_jan=14;
					printf("������ ����Ǿ����ϴ�.\n");
					break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
				break;
			}

		}
	}
		
	}
void samyukgu(int* u_jan, int* c_jan){ // 369 ���� 
	printf("369 ������ ���õǾ����ϴ�.\n");
	printf("----------------\n");
	printf("�ڡڡڡڡ� 369 ���� �ڡڡڡڡ�\n");
	printf("---------------\n");
	int startrand; // user, com �� �������� ���� �����ϰ� �ϱ� ���� startrand ���� ���� 
	int correct; //user�� �Է� �� 
	int i,j,h;  
	startrand = rand()%2; //startrand���� 0, 1 �� �������� �������� ��. 
	if (startrand==0){		 //com ���� �� �� 
	for(i=1; i<20; i++){
		if(i%10==3||i%10==6||i%10==9){ //3, 6, 9, 13, 16, 19 �Ͻ� com�� 0 ��� 
			printf("COMP>>0\n");
		}
		else{ //�ƴ� ��� �� �� ��� 
		printf("COMP>>%d\n", i);
		}
		i+=1; //i 1 ���� 
		printf("USER>>");
		scanf("%d",&correct); //user �� �Է� 
		if(i%10==3||i%10==6||i%10==9){ //3, 6, 9, 13, 16, 19 �� ��  0�� �ԷµǾ�� ��. �ƴ� �� com �¸�, user �ܼ� 4 ����. 
			if(correct!=0){

				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n");
				*u_jan +=4;
					if(*u_jan>=14){ //user  �� �� 14 �̻��� ��, 14�� ��ȯ �� ���� ���� 
						*u_jan=14;
					printf("������ ����Ǿ����ϴ�.\n");
					break; 
					}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
				break;
			}
		}
		else{
			if(correct!=i){ //correct �� i �� �ٸ� �� com �¸�, user �� �� 4 ����.  
				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n");
				*u_jan +=4;
				if(*u_jan>=14){ //user �� ���� 14 �̻��� �� 14�� ��ȯ �� ���� ���� 
					*u_jan=14;
				printf("������ ����Ǿ����ϴ�.\n");
				break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
				break;
			}
		}

	if(i==20){ //for ������ i=20������ �����. ���� ������ 21�� com�� ���������� 

	printf("COMP>>21\n");
	printf("-------------\n");
	printf("USER�� �¸��Ͽ����ϴ�.\n");
	printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n");
	*c_jan+=4;
	if(*c_jan>=14){ //com �� �� 4 �߰�, com �� ���� 14 �̻��� �� 14�� ��ȯ�ϰ� ���� ���� 
		*c_jan=14;
	printf("������ ����Ǿ����ϴ�.\n");
	}
	if(*c_jan<14){
	printf("[COMPUTER's Turn']\n");
	printf("----------------\n");
	printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�. \n");
	}
	}
	}
	}
	
	else{				//���� ���� ���� 
	
	for(int j=1; j<21; j++){ //com ���� �����ϴ� ���� ���� �������� �ڵ� ���� 
		printf("USER>>");
		scanf("%d",&correct);
		 if(j%10==3||j%10==6||j%10==9){
			if(correct==0){
				j+=1;
				printf("COMP>>%d\n", j);
			}
			else{
				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n");
				*u_jan +=4;
				if(*u_jan>=14){
					*u_jan=14;
					printf("������ ����Ǿ����ϴ�.\n");
					break; 
				}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
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
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n");
				*u_jan +=4;
					if(*u_jan>=14){
						*u_jan=14;
						printf("������ ����Ǿ����ϴ�.\n");
						break; 
					}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");
				break;
			}
		}
		if(j==20){ //������ �Է��� 21�� ���� ��� user �¸�, �ƴҰ�� com �¸� 
		printf("USER>>");
		scanf("%d", &h);
			if (h==21){
			printf("-------------\n");
			printf("USER�� �¸��Ͽ����ϴ�.\n");
			printf("COMPUTER�� 4�� ���ð� �Ǿ����ϴ�.\n"); //com 4�� �߰�, 14�� �̻��� �� 14������ ��ȯ�ϰ� ���� ���� 
			*c_jan+=4;
				if(*c_jan>=14){
					*c_jan=14;
					printf("������ ����Ǿ����ϴ�.\n");
					break; 
				}
			printf("[COMPUTER's Turn']\n");
			printf("----------------\n");
			printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�. \n");
			}
			else{
				printf("----------------\n");
				printf("COMPUTER�� �¸��Ͽ����ϴ�.\n");
				printf("USER�� 4�� ���ð� �Ǿ����ϴ�. \n"); //user 4�� �߰�, 14�� �̻��� �� 14������ ��ȯ�ϰ� ���� ���� 
				*u_jan +=4;
						if(*u_jan>=14){ 
							*u_jan=14;
							printf("������ ����Ǿ����ϴ�.\n");
							break; 
							}
				printf("[COMPUTER's Turn']\n");
				printf("------------------\n");
				printf("COMPUTER�� 0�� ���ð� �Ǿ����ϴ�.\n");	
			}
	}
}
}
}
