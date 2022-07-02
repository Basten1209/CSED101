#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#define MAX_FILE_NAME 30
#define MAX_WORD_LEN 30

int mystrlen(char* str);
int mystrcmp(char* str1, char* str2);
char* mystrcpy(char* toStr, char* fromStr);
char* mystrlower(char* str);
int main()
{
	while(1) //초기 화면으로 계속 돌아가기 위함 
	{
	
	char command[20];
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"); //초기 화면 출력 
	printf("CSED101\n");
	printf("Assignment 3\n\n");	
	printf("Naive Baysian Classifier for Spam Filtering\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Command:");
	scanf("%s", command); //커맨드 입력 
	
	if(strcmp(mystrlower(command), "train") == 0) //train 을 입력받은 경우 
	{
	char filename[20]; //파일명을 받을 배열 선언 
	printf("File name : ");
	scanf("%s", filename); //파일명 입력 받음 
	FILE *fp; //파일 포인터 선언 
	fp = fopen(filename, "r"); //읽기 형식으로 파일 오픈 

	if(fp == NULL) //파일이 없는 경우 
	{
		printf("Error : File does not exist");
		Sleep(1000);
		system("cls");
	}
	char line[1000]; //한 문장을 받을 배열 
	char templine[1000]; // 문장을 임시로 저장할 배열 
	int *freq_ham; //ham에 대한 단어 출현  빈도를 저장할 배열 
	int *freq_spam;//spam에 대한 단어 출현 빈도를 저장할 배열 
	int hamcount = 0; //ham인 문장 수를 저장할 변수 
	int spamcount = 0; //spam인 문장 수를 저장할 변수 
	char **words; //단어들을 저장할 배열 
	char *label; //레이블을 저장할 배열 

	while(fgets(line, 1000, fp)!=EOF) //라인이 EOF가 아닐때 까지 반복 
	{

	strcpy(line, mystrlower(line)); //문장을 전부 소문자로 변경 후 복사 
	label = strtok_s(line,"\t",templine); //레이블만 분할 하여 label에 저장 
	//strcpy(templine, line);
	//label = strtok(line, "\t");
	//printf("%s", label);
	
	for(int i = 0; i<1000; i++) //각 행에 대해 소문자 알파벳이 아닌 문자들을 ' '로 변환 
	{	
		if(line[i] != '\0'){
		
		if(line[i]<'a' || line[i]>'z')
		{
			line[i] = ' ';
		}
		}
	}
	
	if(strcmp(label, "ham") == 0) //label이 ham인 경우 ham ++ 
	{
		hamcount++;
	}
	else if(strcmp(label, "spam") == 0) // label이 spam인 경우 spam++ 
	{
		spamcount++;
	}
	
	char word[MAX_WORD_LEN]; //단어를 임시로 받을 배열 
	strcpy(word, label); //레이블 값을 word에 저장 
	while(word != NULL); //word가 null값이 아닐 때 까지 반복하여 한 단어씩 받아 words에 복사 
	{
		int i = 0;
	strcpy(word,strtok_s(NULL, " ", templine));
	words[i] = (char*)malloc(sizeof(char) * (strlen(word) + 1));
	strcpy(words[i], word);
	printf("%s\n", words[i]);
	i++;
	}
	//이후, 각 단어들의 ASCII값을 바탕으로 버블정렬 실행(mystrcmp를 활용), 이때, 두 index의 값이 동일할 시 하나를 공백으로 변경
	//label이 ham인 경우, 해당하는 단어의 freq_ham의 index에 해당하는 값을 1 추가, spam인 경우는 freq_spam의 index에 해당하는 값을 1 추가
	//모든 문장에 대해 반복 
	// 이후, 단어들의 ASCII값을 바탕으로 모든 문장의 단어들에 대해 버블정렬 실행, 같은 단어가 존재하는 경우 하나를 지우고, freq_ham, freq_spam 값은 합산
	//fprintf를 통해 word, freq_ham, freq_spam 값 파일출력 
	}
	}
	else if(strcmp(mystrlower(command), "test") == 0) //test를 입력받은 경우 
	{
		FILE *fp2; //파일 포인터 fp2 선언 
		char word[MAX_WORD_LEN];
		int ham, spam; //ham, spam인 문장 수를 받을 변수 
		int hamc[100], spamc[100]; // 각 단어의 ham일 때의 출현 횟수, spam일 때의 출현 횟수를 받을 변수 
		char **testwords = malloc(sizeof(char*)*30); //파일의 word들을 받아 저장할 배열 포인터 선언 및 동적 할당 
		char testline[1000]; // 입력받는 문장 받을 배열 
		fp2 = fopen("stats.txt", "r"); // 파일 읽기 전용으로 불러오기 
		fscanf(fp2, "Ham:%d, Spam:%d\n", &ham, &spam); //ham, spam 문장 수 입력 받기 
		 //printf("%d %d\n", ham, spam); -> ham, spam 인 문장 수 정확히 입력 받았는지 확인 
		int i=0;
		while ((fscanf(fp2, "%s", testline))!= EOF) //문장 단위로 파일 한 문장씩 읽기 
	{	
		strcpy(word,strtok(testline, ",")); //, 를 기준으로 word 분할 
		testwords[i] = (char*)malloc(sizeof(char) * (strlen(word) + 1)); //word를 담기 위한 testwords[i] 동적 할당 
		strcpy(testwords[i], word); // word를 testwords[i]에 복제 
		hamc[i]= atoi(strtok(NULL, ",")); // ,를 기준으로 ham일때의 출현 빈도 값을 int형으로 변환하여 hamc[i]에 저장 
		spamc[i]= atoi(strtok(NULL, ","));
 	   //printf("Line = %s, %d, %d \n", testwords[i], hamc[i], spamc[i]); -> 각 배열에 해당하는 값이 잘 들어갔는지 확인하기 위한 출력 
		i++;
	}
		printf("Enter a message:");
		char **inputwords =malloc(sizeof(char*)*30); //입력받은 단어들을 저장할 배열 포인터 선언 및 동적할당 
		char inputline[1000];
		scanf("%s", inputline);
		strcpy(inputline, mystrlower(inputline));

		for(int i = 0; i<1000; i++) //각 행에 대해 소문자 알파벳이 아닌 문자들을 ' '로 변환 
	{	
		if(inputline[i] != '\0'){
		
		if(inputline[i]<'a' || inputline[i]>'z')
		{
			inputline[i] = ' ';
		}
		}
	}
		int j = 0;
		char *inputword = strtok(inputline, " "); //단어를 공백 기준으로 분할하여 입력받는 배열 선언 
		while(inputword != NULL)
		{
		inputwords[j] = (char*)malloc(sizeof(char) * (strlen(inputword) + 1)); //단어를 저장할 포인터 배열 동적할당 
		strcpy(inputwords[j],inputword); //inputword의 값을 inputwords[i] 에 복사 
		printf("%s", inputwords[j]);
		inputword = strtok(NULL, " "); //inputword에 다시 공백을 기준으로 분할하여 얻은 단어 저장 
		j++;
		}
		//inputwords의 단어와 testwords의 단어 겹치는 지 확인, 겹치는 경우 testwords의 index에 해당하는 hamc, spamc를 바탕으로 조건부확률 연산
		//겹치지 않는 경우 조건부확률 = 0.1로 계산
		//최종적으로, 조건부확률의 부분곱을 통해 문장에 대한 ham, spam 조건부확률 계산
		//P(ham|sentence)>P(spam|sentence)인 경우 ham임을 뜻하는 문장 출력, 아닌 경우 spam임을 뜻하는 문장 출력  
	}
	else if(strcmp(mystrlower(command), "exit") == 0) //exit를 입력받은 경우 
	{ 
		exit(0); //정상적인 종료 
	}
	else //기타 잘못된 입력을 받은 경우, invalid input 출력 후 화면 지움 
	{
		printf("Invalid Input"); 
		Sleep(1000);
		system("cls");
	}
	}
}



int mystrlen(char* str){ //string의 길이 확인 함수 
int a=0;
	while(str[a]!='\0') //공백을 만나기 전 까지 하나씩 count 
	{
		++a;
	}
	return a;
}

int mystrcmp(char* str1, char* str2){ //문자열 크기 비교 
	char c1, c2;
	int a;
	while(1)
	{
		c1 = *str1++;
		c2 = *str2++;
		
		if (c1!=c2)
		{
			a = (c1 < c2 ? -1 : 1);
			return a;
		}
		if (!c1)
			break;
	}
	return 0;
}

char* mystrcpy(char* toStr, char* fromStr){ //문자열 복사 후 마지막에 '\0'을 넣어줌으로써 문자열 종료 
	int i = 0;
	while(fromStr[i] != '\0')
	{
		toStr[i] = fromStr[i];
		i++;
	}
	toStr[i] = '\0';
	return toStr;
}

char* mystrlower(char* str){ //대문자에 해당하는 ASCII를 지닌 문자를 소문자로 변경 
	int i = 0;
	while(str[i] != '\0')
	{
	
		if(str[i]>='A' && str[i]<='Z')
		{
		str[i] = str[i]+32;
		}
		i++;
	}
	return str;
}
