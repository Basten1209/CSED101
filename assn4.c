//ASSN4
//학번 20210661 이름 오승준 개발환경 : Visual Studio 2022

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct User { //유저 구조체
	char name[21];
	char email[41];
	struct User* next;
}USER;

typedef struct Participant{ //참여자 구조체
	USER* user;
	bool camera;
	bool microphone;
	struct Participant* next;
}PARTICIPANT;

typedef struct Conference{ //회의 구조체
	char roomname[21];
	int numParticipant;
	int maxParticipant;
	PARTICIPANT* participants;
}CONFERENCE;

USER* arrange(USER* head, char* name); //위치 정렬 함수
void user_list(USER* u); //user list 명령 함수
void user_add(USER* u); // user add 명령 함수
void user_delete(USER* u); //user delete 명령 함수
void conf_info(CONFERENCE* c); // conf info 명령 함수
void conf_join(CONFERENCE* c, USER* u); //conf join 명령 함수
void conf_hangup(CONFERENCE* c); //conf hangup 명령 함수
void conf_toggle_camera(CONFERENCE* c); //conf toggle camera 명령 함수
void conf_toggle_mic(CONFERENCE* c); //conf toggle mic 명령 함수
int main(){

	char command[20];
	CONFERENCE* conf = (CONFERENCE*)malloc(sizeof(CONFERENCE)); //conf 선언 및 초기값 설정
	conf->maxParticipant = 0;
	conf->numParticipant = 0;
	conf->participants = NULL;
	strcpy(conf->roomname,"temproomname");

	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT)); 
	part->camera = 0;
	part->microphone = 0;
	part->next = NULL;
	part->user = NULL;

	FILE* infile; //파일 구제체 infile 선언

	char filename[31]; //파일명 입력받기 위한 배열 선언
	printf("유저 리스트 파일 이름을 입력해주세요. >>");
	scanf("%s", filename);  // 파일명 입력받기
	
	while(!(infile = fopen(filename, "r"))){ //파일명에 해당하는 파일이 없는 경우 다시 입력받음
		printf("유효하지 않은 입력입니다. 유저 리스트 파일 이름을 입력해주세요. >>");
		scanf("%s", filename);
		getchar();
		}
	
	USER* head, * curuser, * prev; //USER 구조체 3개 선언(순서 재배열을 위함)
	char tempname[21], tempemail[41]; //임시로 이름, 이메일을 받을 배열
	char rname[21]; //회의명을 받을 배열
	int maxp; //최대 인원을 받을 배열
	int count = 0; //파일의 인원 수를 받을 배열
	head = NULL;
	prev = NULL;
	while(!feof(infile)){  //파일 끝이 나오기 전까지 반복하며 파일의 이름, 이메일 읽기

 
        fscanf(infile, "%s\t%s\n", &tempname, &tempemail);
		curuser = (USER*)malloc(sizeof(USER));
		strcpy(curuser->name, tempname);
		strcpy(curuser->email, tempemail);
		
		if (!head) {
			head = curuser;
			curuser->next = NULL;
		}
		else {
			prev = arrange(head, tempname); //head와 이름을 비교하여 순서 정렬
			if (!prev) {
				curuser->next = head;
				head = curuser;
			}
			else {
				curuser->next = prev->next;
				prev->next = curuser;
			}
		}
		count++; //1번 돌때마다 count 1씩 추가
	}
	curuser = head;
	printf("[INFO] user.txt에서 총 %d 명의 유저를 불러왔습니다.\n", count);

	printf("회의실 이름을 입력해주세요. >>"); //회의실 이름 입력받음
	scanf("%s", rname);
	strcpy(conf->roomname, rname);
	printf("최대 사용자 수를 입력해주세요. >>"); //최대 인원 입력받음
	scanf("%d", &maxp);
	conf->maxParticipant = maxp;
	conf->numParticipant = 0; //현재 회의실 인원 0명으로 초기 설정
	printf("[INFO] %s 회의실이 생성되었습니다! \n", conf->roomname);
	getchar();
	while(1){

		printf("명령어를 입력해주세요. >>"); //명령어 입력받음. 각 명령어에 맞는 함수 실행
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
		else if(strcmp(command, "quit")==0){ //명령어가 quit인 경우 문구만 출력하고 exit()로 프로그램 정상종료.
			printf("[INFO]  회의가 종료되었습니다. \n");
			exit(0);
		}
		else { //지정된 입력이 아닌 경우 다시 명령어 입력받음
			printf("유효하지 않은 입력입니다. ");
		}
		getchar();
	}
}
void user_list(USER* u){ 
int i = 0;

	printf("\n===============================================================\n");
	printf("                  이름                                   이메일\n");
	printf("---------------------------------------------------------------\n");
while(u) { //u가 null이 아닐때 까지 반복
	i++;
	printf("%d %20s %40s\n", i, u->name, u->email);
	u = u->next; //다음 사람을 읽어옴
}

	printf("===============================================================\n");
	
}

void user_add(USER* u) {
	USER* new, * temp, * front; //USER 구조체 3개 선언(순서 배열을 위해)
	char* name[21];
	char* email[21];
	new = malloc(sizeof(USER));
	front = u; //front에 u 저장

	printf("추가할 유저의 이름을 입력해주세요. >>"); //이름과 이메일을 받아 new에 저장
	scanf("%s", name);
	strcpy(new->name, name);
	getchar();
	printf("추가할 유저의 이메일을 입력해주세요. >>");
	scanf("%s", email);

	strcpy(new->email, email);
	temp = new; //new에 저장된 값을 temp에 임시로 저장

	while (front != NULL) { //front가 NULL이 아닌 경우 반복
		if (strcmp(name, front->name) < 0) //front->name과 name을 비교하여 순서대로 배열
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
	printf("[INFO] %s, %s 유저가 추가되었습니다.\n", name, email); //유저 추가 문구 출력
}
void user_delete(USER* u){
	char name[21];
	char yorn;
	USER* dump; //유저 구조체 dump 선언
	dump = malloc(sizeof(USER)); //동적할당
	printf("제거할 유저의 이름을 입력해주세요. >>");
	scanf("%s", name); //제거할 유저 이름 받기

	while (u) { //u가 NULL이 아닐 때 까지 반복

		if (u->next == NULL) { //반복했는데 name와 일치하는 유저가 없는 경우
			printf("[INFO] 해당 유저는 존재하지 않습니다! \n");
			break;
		}

		if (strcmp(u->next->name, name) == 0) { // name과 일치하는 유저 발견
			getchar();
			printf("%s, %s 유저를 제거하시겠습니까? (y/n) >>", u->next->name, u->next->email);
			scanf("%c", &yorn);
			if (yorn == 'y') { //y를 입력 받은 경우
				printf("[INFO] %s, %s 유저를 제거하였습니다.\n", u->next->name, u->next->email);
				dump = u->next; //dump가 u->next를 가르키게 함
				 u->next = dump->next; //dump->next가 u->next를 가리키게 함으로써 유저 삭제
				free(dump); //할당 해제
				break;
			}
			else if (yorn == 'n') { //n이면 반복문 탈출, 함수 종료
				break;
			}
		}
		else {
			u = u->next;
		}
	}

}
void conf_info(CONFERENCE* c){
	int i = 0; //번호를 표현하기 위한 변수
	PARTICIPANT* curr = c->participants; //참여자 리스트 curr 선언
	printf("\n");
	printf("회의실 이름 : %s \n", c->roomname);
	printf("최대 사용자 수: %d \n", c->maxParticipant);
	printf("참여자 목록 : \n");
	printf("\n===================================================================================\n");
	printf("                  이름                                   이메일    카메라    마이크\n");
	printf("-------------------------------------------------------------------------------------\n");
	while (curr) { //curr가 null이 아닐때 까지 반복
		i++;
		char* yesorno1 = (char*)malloc(sizeof(char)); //1이면 ON, 0이면 OFF
		char* yesorno2 = (char*)malloc(sizeof(char)); //1이면 ON, 0이면 OFF
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
		curr = curr->next; //다음 회의실 참여자로 넘어가기
	}

	printf("===================================================================================\n");
}
void conf_join(CONFERENCE* c, USER* u){
	if (c->numParticipant == c->maxParticipant) { //최대 인원만큼 이미 참여중인 경우
		printf("[INFO] 회의에 최대 인원 %d 명이 참여하고 있습니다!\n", c->maxParticipant);
		return;
	}

	char* name = (char*)malloc(sizeof(char));
	char camyn;
	char micyn;

	printf("추가할 유저의 이름을 입력해주세요. >>"); //유저 이름 입력받음
	scanf("%s", name);

	USER* temp = u; //u를 temp에 저장
		
	while (temp) { //temp가 null이 아닐때까지 하나씩 밀어가며 반복, 이름 비교하여 확인
		if (strcmp(temp->name, name) == 0)
			break;
		temp = temp->next;
	}

	if (temp == NULL) { //동일 이름이 없는 경우 문구 띄우고 return
		printf("[INFO] 해당 유저는 존재하지 않습니다!\n");
		return;
	}
	PARTICIPANT* curpart = c->participants; //참여자 구조체 curpart 선언
	while (curpart) { //curpart가 null이 아닐때 까지 반복문 실행
		if (strcmp(curpart->user->name, name) == 0) { //이미 동일한 이름의 참여자가 존재하는 경우 문구 띄우고 return
			printf("[INFO] %s 이(가) 회의에 이미 참여했습니다!\n", name);
			return;
		}
		curpart = curpart->next;
	}

	curpart = c->participants; //c->participants의 값을 curpart에 저장

	if (curpart) { //curpart가 null이 아닌 경우, curpart의 마지막을 가르키도록 반복
		while (curpart->next) {
			curpart = curpart->next;
		}
	}
	
	PARTICIPANT* part = (PARTICIPANT*)malloc(sizeof(PARTICIPANT));  //참여자 주고체 part 선언 및 동적할당
	part->user = temp;
	part->next = NULL;
	getchar();
			printf("카메라를 켠 상태로 시작하시겠습니까? (y/n) >>"); //y인경우 1, 아닌경우 0
			scanf("%c", &camyn);
			getchar();
			if(camyn=='y'){
				part->camera = 1;
			}
			else{
				part->camera = 0;
			}

			printf("마이크를 켠 상태로 시작하시겠습니까? (y/n) >>");//y인경우 1, 아닌경우 0
			scanf("%c", &micyn);
			if (micyn == 'y'){
				part->microphone = 1;
			}
			else{
				part->microphone = 0;
			}

			if (curpart) { //curpart의 마지막을 가리키게 함
				curpart->next = part;
			}
			else {
				c->participants = part;
			}
			printf("[INFO] %s 이(가) 입장했습니다!\n", name);
			c->numParticipant++; //인원수 1 추가

}
void conf_hangup(CONFERENCE* c) {

	if (c->numParticipant == 0) { //참석자가 없는경우
		printf("[INFO] 회의 참석자가 없습니다!\n");
		return;
	}
	char name[21];
	char yorn;
	PARTICIPANT* curr = c->participants; //참여자 구조체 curr 선언
	printf("제외할 유저의 이름을 입력해주세요. >>");
	scanf("%s", name);



	if (strcmp(curr->user->name, name) == 0) { //첫 노드 참석자가 삭제대상
		getchar();
		printf("유저를 회의에서 내보내시겠습니까? (y/n) >>");
		scanf("%c", &yorn);
		if (yorn == 'y') {
			c->participants = curr->next; //다음 노드가 c->participants 에 들어가도록 하여 첫 노드 삭제
			free(curr);
			printf("[INFO] %s 유저를 회의에서 내보냈습니다.\n", name);
			c->numParticipant--; //인원수 1 감소
			return;
		}
		else return;
	}

	while (curr->next) { //노드를 찾을때 까지 하나씩 밀어가며 반복
		if (strcmp(curr->user->name, name) == 0) {
			printf("유저를 회의에서 내보내시겠습니까? (y/n) >>");
			getchar();
			scanf("%c", &yorn);
			if (yorn == 'y') {
				PARTICIPANT* temp = curr->next; //curr->next를 temp에 저장
				curr->next = temp->next; //temp->next를 curr->next에 저장함으로써 노드 삭제
				free(temp);
				printf("[INFO] %s 이(가) 회의에서 나갔습니다!\n", name);
				c->numParticipant--; //인원수 1 감소
				return;
			}
			else return;
		}
		curr = curr->next;
	}
	printf("[INFO] 입력한 유저는 회의에 존재하지 않습니다!\n"); //반복문으로 curr->next==NULL까지 온 경우 이름이 없다는 뜻이므로 문구 출력
}
void conf_toggle_camera(CONFERENCE* c){
	char name[21];
	printf("카메라 상태를 변경할 유저의 이름을 입력해주세요. >>");
	scanf("%s", &name);
	PARTICIPANT* curr = c->participants;

	while (curr) { //curr가 null이 아니면 계속하여 한 칸씩 밀며 동일한 이름이 있는지 확인
		if (strcmp(curr->user->name, name) == 0) {
			if (curr->camera == 1) {//카메라가 1인 경우 0으로 변경
				curr->camera = 0;
				printf("[INFO] %s 의 카메라가 ON->OFF 되었습니다!\n", name);
				return;
			}
			else if (curr->camera == 0) {//카메라가 0인 경우 1으로 변경
				curr->camera = 1;
				printf("[INFO] %s 의 카메라가 OFF->ON 되었습니다!\n", name);
				return;
			}
		}
		curr = curr->next;
	}

	printf("[INFO] 해당 유저는 회의에 없습니다!\n");
}
void conf_toggle_mic(CONFERENCE* c){
	char name[21];
	printf("마이크 상태를 변경할 유저의 이름을 입력해주세요. >>");
	scanf("%s", &name);
	PARTICIPANT* curr = c->participants;
	while (curr) {	// curr가 null이 아니면 계속하여 한 칸씩 밀며 동일한 이름이 있는지 확인
		if (strcmp(curr->user->name, name) == 0) {
			if (curr->microphone== 1) {//마이크가 1인 경우 0으로 변경
				curr->microphone = 0;
				printf("[INFO] %s 의 마이크가 ON->OFF 되었습니다!\n", name);
				return;
			}
			else if (curr->microphone == 0) {//마이크가 0인 경우 1으로 변경
				curr->microphone = 1;
				printf("{INFO] %s 의 마이크가 OFF->ON 되었습니다!\n", name);
				return;
			}
		}
		curr = curr->next;
	}

	printf("[INFO] 해당 유저는 회의에 존재하지 않습니다!\n"); //curr이 null값이 될 때 까지 같은 이름이 없으므로 문구 출력
}
USER* arrange(USER* head, char* name) {
	USER* temp, *bef; //USER 구조체 2개 선언
	int check = 0;
	
	temp = (USER*)malloc(sizeof(USER)); //동적할당
	
	bef = NULL;
	temp = head; //temp에 head 저장

	while(1){
		check = strcmp(name, temp->name); //입력받은 이름과 temp->name의 아스키코드값 비교
		
		if(check>0) { //check가 0보다 큰 경우 : name이 더 큼
			bef = temp;
			temp = temp->next;
			if(temp==NULL)
				return bef;
			}
			else if(check<=0){ //check가 0 이하인경우 : 동일하거나 name이 더 작음
				return bef;
			}
		}
}
