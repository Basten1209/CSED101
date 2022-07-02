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
	while(1) //�ʱ� ȭ������ ��� ���ư��� ���� 
	{
	
	char command[20];
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"); //�ʱ� ȭ�� ��� 
	printf("CSED101\n");
	printf("Assignment 3\n\n");	
	printf("Naive Baysian Classifier for Spam Filtering\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Command:");
	scanf("%s", command); //Ŀ�ǵ� �Է� 
	
	if(strcmp(mystrlower(command), "train") == 0) //train �� �Է¹��� ��� 
	{
	char filename[20]; //���ϸ��� ���� �迭 ���� 
	printf("File name : ");
	scanf("%s", filename); //���ϸ� �Է� ���� 
	FILE *fp; //���� ������ ���� 
	fp = fopen(filename, "r"); //�б� �������� ���� ���� 

	if(fp == NULL) //������ ���� ��� 
	{
		printf("Error : File does not exist");
		Sleep(1000);
		system("cls");
	}
	char line[1000]; //�� ������ ���� �迭 
	char templine[1000]; // ������ �ӽ÷� ������ �迭 
	int *freq_ham; //ham�� ���� �ܾ� ����  �󵵸� ������ �迭 
	int *freq_spam;//spam�� ���� �ܾ� ���� �󵵸� ������ �迭 
	int hamcount = 0; //ham�� ���� ���� ������ ���� 
	int spamcount = 0; //spam�� ���� ���� ������ ���� 
	char **words; //�ܾ���� ������ �迭 
	char *label; //���̺��� ������ �迭 

	while(fgets(line, 1000, fp)!=EOF) //������ EOF�� �ƴҶ� ���� �ݺ� 
	{

	strcpy(line, mystrlower(line)); //������ ���� �ҹ��ڷ� ���� �� ���� 
	label = strtok_s(line,"\t",templine); //���̺� ���� �Ͽ� label�� ���� 
	//strcpy(templine, line);
	//label = strtok(line, "\t");
	//printf("%s", label);
	
	for(int i = 0; i<1000; i++) //�� �࿡ ���� �ҹ��� ���ĺ��� �ƴ� ���ڵ��� ' '�� ��ȯ 
	{	
		if(line[i] != '\0'){
		
		if(line[i]<'a' || line[i]>'z')
		{
			line[i] = ' ';
		}
		}
	}
	
	if(strcmp(label, "ham") == 0) //label�� ham�� ��� ham ++ 
	{
		hamcount++;
	}
	else if(strcmp(label, "spam") == 0) // label�� spam�� ��� spam++ 
	{
		spamcount++;
	}
	
	char word[MAX_WORD_LEN]; //�ܾ �ӽ÷� ���� �迭 
	strcpy(word, label); //���̺� ���� word�� ���� 
	while(word != NULL); //word�� null���� �ƴ� �� ���� �ݺ��Ͽ� �� �ܾ �޾� words�� ���� 
	{
		int i = 0;
	strcpy(word,strtok_s(NULL, " ", templine));
	words[i] = (char*)malloc(sizeof(char) * (strlen(word) + 1));
	strcpy(words[i], word);
	printf("%s\n", words[i]);
	i++;
	}
	//����, �� �ܾ���� ASCII���� �������� �������� ����(mystrcmp�� Ȱ��), �̶�, �� index�� ���� ������ �� �ϳ��� �������� ����
	//label�� ham�� ���, �ش��ϴ� �ܾ��� freq_ham�� index�� �ش��ϴ� ���� 1 �߰�, spam�� ���� freq_spam�� index�� �ش��ϴ� ���� 1 �߰�
	//��� ���忡 ���� �ݺ� 
	// ����, �ܾ���� ASCII���� �������� ��� ������ �ܾ�鿡 ���� �������� ����, ���� �ܾ �����ϴ� ��� �ϳ��� �����, freq_ham, freq_spam ���� �ջ�
	//fprintf�� ���� word, freq_ham, freq_spam �� ������� 
	}
	}
	else if(strcmp(mystrlower(command), "test") == 0) //test�� �Է¹��� ��� 
	{
		FILE *fp2; //���� ������ fp2 ���� 
		char word[MAX_WORD_LEN];
		int ham, spam; //ham, spam�� ���� ���� ���� ���� 
		int hamc[100], spamc[100]; // �� �ܾ��� ham�� ���� ���� Ƚ��, spam�� ���� ���� Ƚ���� ���� ���� 
		char **testwords = malloc(sizeof(char*)*30); //������ word���� �޾� ������ �迭 ������ ���� �� ���� �Ҵ� 
		char testline[1000]; // �Է¹޴� ���� ���� �迭 
		fp2 = fopen("stats.txt", "r"); // ���� �б� �������� �ҷ����� 
		fscanf(fp2, "Ham:%d, Spam:%d\n", &ham, &spam); //ham, spam ���� �� �Է� �ޱ� 
		 //printf("%d %d\n", ham, spam); -> ham, spam �� ���� �� ��Ȯ�� �Է� �޾Ҵ��� Ȯ�� 
		int i=0;
		while ((fscanf(fp2, "%s", testline))!= EOF) //���� ������ ���� �� ���徿 �б� 
	{	
		strcpy(word,strtok(testline, ",")); //, �� �������� word ���� 
		testwords[i] = (char*)malloc(sizeof(char) * (strlen(word) + 1)); //word�� ��� ���� testwords[i] ���� �Ҵ� 
		strcpy(testwords[i], word); // word�� testwords[i]�� ���� 
		hamc[i]= atoi(strtok(NULL, ",")); // ,�� �������� ham�϶��� ���� �� ���� int������ ��ȯ�Ͽ� hamc[i]�� ���� 
		spamc[i]= atoi(strtok(NULL, ","));
 	   //printf("Line = %s, %d, %d \n", testwords[i], hamc[i], spamc[i]); -> �� �迭�� �ش��ϴ� ���� �� ������ Ȯ���ϱ� ���� ��� 
		i++;
	}
		printf("Enter a message:");
		char **inputwords =malloc(sizeof(char*)*30); //�Է¹��� �ܾ���� ������ �迭 ������ ���� �� �����Ҵ� 
		char inputline[1000];
		scanf("%s", inputline);
		strcpy(inputline, mystrlower(inputline));

		for(int i = 0; i<1000; i++) //�� �࿡ ���� �ҹ��� ���ĺ��� �ƴ� ���ڵ��� ' '�� ��ȯ 
	{	
		if(inputline[i] != '\0'){
		
		if(inputline[i]<'a' || inputline[i]>'z')
		{
			inputline[i] = ' ';
		}
		}
	}
		int j = 0;
		char *inputword = strtok(inputline, " "); //�ܾ ���� �������� �����Ͽ� �Է¹޴� �迭 ���� 
		while(inputword != NULL)
		{
		inputwords[j] = (char*)malloc(sizeof(char) * (strlen(inputword) + 1)); //�ܾ ������ ������ �迭 �����Ҵ� 
		strcpy(inputwords[j],inputword); //inputword�� ���� inputwords[i] �� ���� 
		printf("%s", inputwords[j]);
		inputword = strtok(NULL, " "); //inputword�� �ٽ� ������ �������� �����Ͽ� ���� �ܾ� ���� 
		j++;
		}
		//inputwords�� �ܾ�� testwords�� �ܾ� ��ġ�� �� Ȯ��, ��ġ�� ��� testwords�� index�� �ش��ϴ� hamc, spamc�� �������� ���Ǻ�Ȯ�� ����
		//��ġ�� �ʴ� ��� ���Ǻ�Ȯ�� = 0.1�� ���
		//����������, ���Ǻ�Ȯ���� �κа��� ���� ���忡 ���� ham, spam ���Ǻ�Ȯ�� ���
		//P(ham|sentence)>P(spam|sentence)�� ��� ham���� ���ϴ� ���� ���, �ƴ� ��� spam���� ���ϴ� ���� ���  
	}
	else if(strcmp(mystrlower(command), "exit") == 0) //exit�� �Է¹��� ��� 
	{ 
		exit(0); //�������� ���� 
	}
	else //��Ÿ �߸��� �Է��� ���� ���, invalid input ��� �� ȭ�� ���� 
	{
		printf("Invalid Input"); 
		Sleep(1000);
		system("cls");
	}
	}
}



int mystrlen(char* str){ //string�� ���� Ȯ�� �Լ� 
int a=0;
	while(str[a]!='\0') //������ ������ �� ���� �ϳ��� count 
	{
		++a;
	}
	return a;
}

int mystrcmp(char* str1, char* str2){ //���ڿ� ũ�� �� 
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

char* mystrcpy(char* toStr, char* fromStr){ //���ڿ� ���� �� �������� '\0'�� �־������ν� ���ڿ� ���� 
	int i = 0;
	while(fromStr[i] != '\0')
	{
		toStr[i] = fromStr[i];
		i++;
	}
	toStr[i] = '\0';
	return toStr;
}

char* mystrlower(char* str){ //�빮�ڿ� �ش��ϴ� ASCII�� ���� ���ڸ� �ҹ��ڷ� ���� 
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
