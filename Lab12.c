#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[20];
    int exam[2];
    float avg;
    char grade;
    
}STUDENT;

typedef struct node
{
    STUDENT data;
    struct node* next;
    
}NODE;

typedef struct
{
    int count;
    NODE* head;
    NODE* tail;
    
}LIST;

void find_list(LIST* plist);
void print_list(LIST* plist);
void insert_node(LIST* plist);
void free_list(LIST* plist);
void print_one_student(STUDENT s, int no);
void add_student(STUDENT *p);

int main() {
    char command[20];
    LIST slist;

    //초기화 
    slist.count = 0;
    slist.head = NULL;
    slist.tail = NULL;

    while (1) {
        printf(">> ");
        scanf("%s",command);

        if (strcmp(command, "add") == 0)
		{
            insert_node(&slist);
        }
        else if (strcmp(command, "print") == 0)
		{
            print_list(&slist);
        }
        else if (strcmp(command, "find") == 0)
		{
            find_list(&slist);
        }
        else if (strcmp(command, "quit") == 0)
		{
            free_list(&slist);
            break;
        }
    }
    return 0;
}

void print_list (LIST* plist)
{
    NODE* temp;
    int i = 0;
    printf("번호       이름\t\t        중간 기말 평균 (학점)\n");
    for(temp = plist->head; temp != NULL; temp = temp->next) {
        i++;
        print_one_student(temp->data,i);
    }
    printf("\n");
}

void print_one_student(STUDENT s, int no) {
    printf("%d\t  %-20s %d   %d   %.1f (%c)\n", no, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
}

void free_list(LIST* plist)
{
    NODE* temp;
    while (plist->head != NULL)
    {
        temp = plist->head;
        plist->head = plist->head->next;
        free(temp);
    }
}

void find_list(LIST* plist)
{
    NODE* temp;
    int i = 0;
    char name[20];
    printf("이름: ");
    scanf("%s",name);
    for(temp = plist->head; temp != NULL; temp = temp->next) {
        i++;
        if (strcmp(name,temp->data.name) == 0) {
            printf("번호       이름\t\t        중간 기말 평균 (학점)\n");
            print_one_student(temp->data, i);
        }
    }
    printf("\n");
}

void insert_node(LIST* plist)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->next = NULL;
    add_student(&temp->data);

    if (plist->head == NULL)
    {
        plist->head = temp;
    }
    else
    {
        plist->tail->next = temp;
    }
    plist->tail = temp;
    plist->count++;
}

void add_student(STUDENT *p) {
    printf("이름: ");
    scanf("%s", &p->name);
    printf("중간고사: ");
    scanf("%d", &p->exam[0]);
    printf("기말고사: ");
    scanf("%d", &p->exam[1]);
    p->avg = (float)(0.5)*(p->exam[0]+p->exam[1]);

    if(p->avg >=90) {
        p->grade = 'A';
    }
    else if(p->avg <90 &&p->avg >=80) {
        p->grade = 'B';
    }
    else if(p->avg <80 &&p->avg >=70) {
        p->grade = 'C';
    }
    else if(p->avg <70 &&p->avg >=60) {
        p->grade = 'D';
    }
    else {
        p->grade = 'F';
    }
    printf("\n");
}
