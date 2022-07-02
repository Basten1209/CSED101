//ASSN4
//�й� 20210661 �̸� ������ ����ȯ�� : Visual Studio 2022

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct User { //���� ����ü
	char name[21];
	char email[41];
	struct User* next;
}USER;

typedef struct Participant{ //������ ����ü
	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;
}PARTICIPANT;

typedef struct Conference{ //ȸ�� ����ü
	char roomname[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participants;
}CONFERENCE;

USER* arrange(USER* head, char* name); //��ġ ���� �Լ�
void user_list(USER* u); //user list ��� �Լ�
void user_add(USER* u); // user add ��� �Լ�
void user_delete(USER* u); //user delete ��� �Լ�
void conf_info(CONFERENCE* c); // conf info ��� �Լ�
void conf_join(CONFERENCE* c, USER* u); //conf join ��� �Լ�
void conf_hangup(CONFERENCE* c); //conf hangup ��� �Լ�
void conf_toggle_camera(CONFERENCE* c); //conf toggle camera ��� �Լ�
void conf_toggle_mic(CONFERENCE* c); //conf toggle mic ��� �Լ�
int main(){

	char command[20];
	CONFERENCE* conf = (CONFERENCE*)malloc(sizeof(CONFERENCE)); //conf ���� �� �ʱⰪ ����
	conf->maxParticipant = 0;
	conf->numParticipant = 0;
	conf->participants = NULL;
	strcpy(conf->roomname,"temproomname");

	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT)); 
	part->camera = 0;
	part->microphone = 0;
	part->next = NULL;
	part->user = NULL;

	FILE* infile; //���� ����ü infile ����

	char filename[31]; //���ϸ� �Է¹ޱ� ���� �迭 ����
	printf("���� ����Ʈ ���� �̸��� �Է����ּ���. >>");
	scanf("%s", filename);  // ���ϸ� �Է¹ޱ�
	
	while(!(infile = fopen(filename, "r"))){ //���ϸ� �ش��ϴ� ������ ���� ��� �ٽ� �Է¹���
		printf("��ȿ���� ���� �Է��Դϴ�. ���� ����Ʈ ���� �̸��� �Է����ּ���. >>");
		scanf("%s", filename);
		getchar();
		}
	
	USER* head, * curuser, * prev; //USER ����ü 3�� ����(���� ��迭�� ����)
	char tempname[21], tempemail[41]; //�ӽ÷� �̸�, �̸����� ���� �迭
	char rname[21]; //ȸ�Ǹ��� ���� �迭
	int maxp; //�ִ� �ο��� ���� �迭
	int count = 0; //������ �ο� ���� ���� �迭
	head = NULL;
	prev = NULL;
	while(!feof(infile)){  //���� ���� ������ ������ �ݺ��ϸ� ������ �̸�, �̸��� �б�

 
        fscanf(infile, "%s\t%s\n", &tempname, &tempemail);
		curuser = (USER*)malloc(sizeof(USER));
		strcpy(curuser->name, tempname);
		strcpy(curuser->email, tempemail);
		
		if (!head) {
			head = curuser;
			curuser->next = NULL;
		}
		else {
			prev = arrange(head, tempname); //head�� �̸��� ���Ͽ� ���� ����
			if (!prev) {
				curuser->next = head;
				head = curuser;
			}
			else {
				curuser->next = prev->next;
				prev->next = curuser;
			}
		}
		count++; //1�� �������� count 1�� �߰�
	}
	curuser = head;
	printf("[INFO] user.txt���� �� %d ���� ������ �ҷ��Խ��ϴ�.\n", count);

	printf("ȸ�ǽ� �̸��� �Է����ּ���. >>"); //ȸ�ǽ� �̸� �Է¹���
	scanf("%s", rname);
	strcpy(conf->roomname, rname);
	printf("�ִ� ����� ���� �Է����ּ���. >>"); //�ִ� �ο� �Է¹���
	scanf("%d", &maxp);
	conf->maxParticipant = maxp;
	conf->numParticipant = 0; //���� ȸ�ǽ� �ο� 0������ �ʱ� ����
	printf("[INFO] %s ȸ�ǽ��� �����Ǿ����ϴ�! \n", conf->roomname);
	getchar();
	while(1){

		printf("��ɾ �Է����ּ���. >>"); //��ɾ� �Է¹���. �� ��ɾ �´� �Լ� ����
		scanf("%[^\n]s", &command);
		
		if(strcmp(command, "user list")==0){
			user_list(curuser);
		}
		else if(strcmp(command, "user add")==0){
			user_add(curuser);
		}
		else if(strcmp(command, "user delete")==0){
			user_delete(curuser);
		}
		else if(strcmp(command, "conf info")==0){
			conf_info(conf);
		}
		else if(strcmp(command, "conf join")==0){
			conf_join(conf, curuser);
		}
		else if(strcmp(command, "conf hangup")==0){
			conf_hangup(conf);
		}
		else if(strcmp(command, "conf toggle camera")==0){
			conf_toggle_camera(conf);
		}
		else if(strcmp(command, "conf toggle mic")==0){
			conf_toggle_mic(conf);
		}
		else if(strcmp(command, "quit")==0){ //��ɾ quit�� ��� ������ ����ϰ� exit()�� ���α׷� ��������.
			printf("[INFO]  ȸ�ǰ� ����Ǿ����ϴ�. \n");
			exit(0);
		}
		else { //������ �Է��� �ƴ� ��� �ٽ� ��ɾ� �Է¹���
			printf("��ȿ���� ���� �Է��Դϴ�. ");
		}
		getchar();
	}
}
void user_list(USER* u){ 
int i = 0;

	printf("\n===============================================================\n");
	printf("                  �̸�                                   �̸���\n");
	printf("---------------------------------------------------------------\n");
while(u) { //u�� null�� �ƴҶ� ���� �ݺ�
	i++;
	printf("%d %20s %40s\n", i, u->name, u->email);
	u = u->next; //���� ����� �о��
}

	printf("===============================================================\n");
	
}

void user_add(USER* u) {
	USER* new, * temp, * front; //USER ����ü 3�� ����(���� �迭�� ����)
	char* name[21];
	char* email[21];
	new = malloc(sizeof(USER));
	front = u; //front�� u ����

	printf("�߰��� ������ �̸��� �Է����ּ���. >>"); //�̸��� �̸����� �޾� new�� ����
	scanf("%s", name);
	strcpy(new->name, name);
	getchar();
	printf("�߰��� ������ �̸����� �Է����ּ���. >>");
	scanf("%s", email);

	strcpy(new->email, email);
	temp = new; //new�� ����� ���� temp�� �ӽ÷� ����

	while (front != NULL) { //front�� NULL�� �ƴ� ��� �ݺ�
		if (strcmp(name, front->name) < 0) //front->name�� name�� ���Ͽ� ������� �迭
			break;
		temp = front;
		front = front->next;
	}
	if (temp == new) {
		new->next = front;
	}
	else {
		new->next = temp->next;
			temp->next = new;
			front = u;
	}
	printf("[INFO] %s, %s ������ �߰��Ǿ����ϴ�.\n", name, email); //���� �߰� ���� ���
}
void user_delete(USER* u){
	char name[21];
	char yorn;
	USER* dump; //���� ����ü dump ����
	dump = malloc(sizeof(USER)); //�����Ҵ�
	printf("������ ������ �̸��� �Է����ּ���. >>");
	scanf("%s", name); //������ ���� �̸� �ޱ�

	while (u) { //u�� NULL�� �ƴ� �� ���� �ݺ�

		if (u->next == NULL) { //�ݺ��ߴµ� name�� ��ġ�ϴ� ������ ���� ���
			printf("[INFO] �ش� ������ �������� �ʽ��ϴ�! \n");
			break;
		}

		if (strcmp(u->next->name, name) == 0) { // name�� ��ġ�ϴ� ���� �߰�
			getchar();
			printf("%s, %s ������ �����Ͻðڽ��ϱ�? (y/n) >>", u->next->name, u->next->email);
			scanf("%c", &yorn);
			if (yorn == 'y') { //y�� �Է� ���� ���
				printf("[INFO] %s, %s ������ �����Ͽ����ϴ�.\n", u->next->name, u->next->email);
				dump = u->next; //dump�� u->next�� ����Ű�� ��
				 u->next = dump->next; //dump->next�� u->next�� ����Ű�� �����ν� ���� ����
				free(dump); //�Ҵ� ����
				break;
			}
			else if (yorn == 'n') { //n�̸� �ݺ��� Ż��, �Լ� ����
				break;
			}
		}
		else {
			u = u->next;
		}
	}

}
void conf_info(CONFERENCE* c){
	int i = 0; //��ȣ�� ǥ���ϱ� ���� ����
	PARTICIPANT* curr = c->participants; //������ ����Ʈ curr ����
	printf("\n");
	printf("ȸ�ǽ� �̸� : %s \n", c->roomname);
	printf("�ִ� ����� ��: %d \n", c->maxParticipant);
	printf("������ ��� : \n");
	printf("\n===================================================================================\n");
	printf("                  �̸�                                   �̸���    ī�޶�    ����ũ\n");
	printf("-------------------------------------------------------------------------------------\n");
	while (curr) { //curr�� null�� �ƴҶ� ���� �ݺ�
		i++;
		char* yesorno1 = (char*)malloc(sizeof(char)); //1�̸� ON, 0�̸� OFF
		char* yesorno2 = (char*)malloc(sizeof(char)); //1�̸� ON, 0�̸� OFF
		if (curr->camera == 1) {
			strcpy(yesorno1, "ON");
		}
		else if(curr->camera == 0) {
			strcpy(yesorno1, "OFF");
		}

		if (curr->microphone == 1) {
			strcpy(yesorno2, "ON");
		}
		else if(curr->microphone == 0) {
			strcpy(yesorno2, "OFF");
		}
		printf("%d %20s %40s         %4s         %4s \n", i, curr->user->name, curr->user->email, yesorno1, yesorno2);
		curr = curr->next; //���� ȸ�ǽ� �����ڷ� �Ѿ��
	}

	printf("===================================================================================\n");
}
void conf_join(CONFERENCE* c, USER* u){
	if (c->numParticipant == c->maxParticipant) { //�ִ� �ο���ŭ �̹� �������� ���
		printf("[INFO] ȸ�ǿ� �ִ� �ο� %d ���� �����ϰ� �ֽ��ϴ�!\n", c->maxParticipant);
		return;
	}

	char* name = (char*)malloc(sizeof(char));
	char camyn;
	char micyn;

	printf("�߰��� ������ �̸��� �Է����ּ���. >>"); //���� �̸� �Է¹���
	scanf("%s", name);

	USER* temp = u; //u�� temp�� ����
		
	while (temp) { //temp�� null�� �ƴҶ����� �ϳ��� �о�� �ݺ�, �̸� ���Ͽ� Ȯ��
		if (strcmp(temp->name, name) == 0)
			break;
		temp = temp->next;
	}

	if (temp == NULL) { //���� �̸��� ���� ��� ���� ���� return
		printf("[INFO] �ش� ������ �������� �ʽ��ϴ�!\n");
		return;
	}
	PARTICIPANT* curpart = c->participants; //������ ����ü curpart ����
	while (curpart) { //curpart�� null�� �ƴҶ� ���� �ݺ��� ����
		if (strcmp(curpart->user->name, name) == 0) { //�̹� ������ �̸��� �����ڰ� �����ϴ� ��� ���� ���� return
			printf("[INFO] %s ��(��) ȸ�ǿ� �̹� �����߽��ϴ�!\n", name);
			return;
		}
		curpart = curpart->next;
	}

	curpart = c->participants; //c->participants�� ���� curpart�� ����

	if (curpart) { //curpart�� null�� �ƴ� ���, curpart�� �������� ����Ű���� �ݺ�
		while (curpart->next) {
			curpart = curpart->next;
		}
	}
	
	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));  //������ �ְ�ü part ���� �� �����Ҵ�
	part->user = temp;
	part->next = NULL;
	getchar();
			printf("ī�޶� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >>"); //y�ΰ�� 1, �ƴѰ�� 0
			scanf("%c", &camyn);
			getchar();
			if(camyn=='y'){
				part->camera = 1;
			}
			else{
				part->camera = 0;
			}

			printf("����ũ�� �� ���·� �����Ͻðڽ��ϱ�? (y/n) >>");//y�ΰ�� 1, �ƴѰ�� 0
			scanf("%c", &micyn);
			if (micyn == 'y'){
				part->microphone = 1;
			}
			else{
				part->microphone = 0;
			}

			if (curpart) { //curpart�� �������� ����Ű�� ��
				curpart->next = part;
			}
			else {
				c->participants = part;
			}
			printf("[INFO] %s ��(��) �����߽��ϴ�!\n", name);
			c->numParticipant++; //�ο��� 1 �߰�

}
void conf_hangup(CONFERENCE* c) {

	if (c->numParticipant == 0) { //�����ڰ� ���°��
		printf("[INFO] ȸ�� �����ڰ� �����ϴ�!\n");
		return;
	}
	char name[21];
	char yorn;
	PARTICIPANT* curr = c->participants; //������ ����ü curr ����
	printf("������ ������ �̸��� �Է����ּ���. >>");
	scanf("%s", name);



	if (strcmp(curr->user->name, name) == 0) { //ù ��� �����ڰ� �������
		getchar();
		printf("������ ȸ�ǿ��� �������ðڽ��ϱ�? (y/n) >>");
		scanf("%c", &yorn);
		if (yorn == 'y') {
			c->participants = curr->next; //���� ��尡 c->participants �� ������ �Ͽ� ù ��� ����
			free(curr);
			printf("[INFO] %s ������ ȸ�ǿ��� �����½��ϴ�.\n", name);
			c->numParticipant--; //�ο��� 1 ����
			return;
		}
		else return;
	}

	while (curr->next) { //��带 ã���� ���� �ϳ��� �о�� �ݺ�
		if (strcmp(curr->user->name, name) == 0) {
			printf("������ ȸ�ǿ��� �������ðڽ��ϱ�? (y/n) >>");
			getchar();
			scanf("%c", &yorn);
			if (yorn == 'y') {
				PARTICIPANT* temp = curr->next; //curr->next�� temp�� ����
				curr->next = temp->next; //temp->next�� curr->next�� ���������ν� ��� ����
				free(temp);
				printf("[INFO] %s ��(��) ȸ�ǿ��� �������ϴ�!\n", name);
				c->numParticipant--; //�ο��� 1 ����
				return;
			}
			else return;
		}
		curr = curr->next;
	}
	printf("[INFO] �Է��� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n"); //�ݺ������� curr->next==NULL���� �� ��� �̸��� ���ٴ� ���̹Ƿ� ���� ���
}
void conf_toggle_camera(CONFERENCE* c){
	char name[21];
	printf("ī�޶� ���¸� ������ ������ �̸��� �Է����ּ���. >>");
	scanf("%s", &name);
	PARTICIPANT* curr = c->participants;

	while (curr) { //curr�� null�� �ƴϸ� ����Ͽ� �� ĭ�� �и� ������ �̸��� �ִ��� Ȯ��
		if (strcmp(curr->user->name, name) == 0) {
			if (curr->camera == 1) {//ī�޶� 1�� ��� 0���� ����
				curr->camera = 0;
				printf("[INFO] %s �� ī�޶� ON->OFF �Ǿ����ϴ�!\n", name);
				return;
			}
			else if (curr->camera == 0) {//ī�޶� 0�� ��� 1���� ����
				curr->camera = 1;
				printf("[INFO] %s �� ī�޶� OFF->ON �Ǿ����ϴ�!\n", name);
				return;
			}
		}
		curr = curr->next;
	}

	printf("[INFO] �ش� ������ ȸ�ǿ� �����ϴ�!\n");
}
void conf_toggle_mic(CONFERENCE* c){
	char name[21];
	printf("����ũ ���¸� ������ ������ �̸��� �Է����ּ���. >>");
	scanf("%s", &name);
	PARTICIPANT* curr = c->participants;
	while (curr) {	// curr�� null�� �ƴϸ� ����Ͽ� �� ĭ�� �и� ������ �̸��� �ִ��� Ȯ��
		if (strcmp(curr->user->name, name) == 0) {
			if (curr->microphone== 1) {//����ũ�� 1�� ��� 0���� ����
				curr->microphone = 0;
				printf("[INFO] %s �� ����ũ�� ON->OFF �Ǿ����ϴ�!\n", name);
				return;
			}
			else if (curr->microphone == 0) {//����ũ�� 0�� ��� 1���� ����
				curr->microphone = 1;
				printf("{INFO] %s �� ����ũ�� OFF->ON �Ǿ����ϴ�!\n", name);
				return;
			}
		}
		curr = curr->next;
	}

	printf("[INFO] �ش� ������ ȸ�ǿ� �������� �ʽ��ϴ�!\n"); //curr�� null���� �� �� ���� ���� �̸��� �����Ƿ� ���� ���
}
USER* arrange(USER* head, char* name) {
	USER* temp, *bef; //USER ����ü 2�� ����
	int check = 0;
	
	temp = (USER*)malloc(sizeof(USER)); //�����Ҵ�
	
	bef = NULL;
	temp = head; //temp�� head ����

	while(1){
		check = strcmp(name, temp->name); //�Է¹��� �̸��� temp->name�� �ƽ�Ű�ڵ尪 ��
		
		if(check>0) { //check�� 0���� ū ��� : name�� �� ŭ
			bef = temp;
			temp = temp->next;
			if(temp==NULL)
				return bef;
			}
			else if(check<=0){ //check�� 0 �����ΰ�� : �����ϰų� name�� �� ����
				return bef;
			}
		}
}
