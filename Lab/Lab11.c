#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	int exam[2];
	float avg;
	char grade;
	
}STUDENT;

void print_one_student(STUDENT s, int no);
void print_students(STUDENT slist[], int n);
void add_student(STUDENT *p);
int main()
{
	STUDENT slist[10];
	char command[20];
	int idx = 0;
	
		while(1)
		{
			printf(">> ");
			scanf("%s", command);
			if(strcmp(command, "add") == 0 )
			{
				add_student(&slist[idx]);
				slist[idx].avg = slist[idx].exam[0]*0.5+slist[idx].exam[1]*0.5;
	if (slist[idx].avg >=90)
	{
		slist[idx].grade = 'A';
	}
	else if(slist[idx].avg<90 && slist[idx].avg>=80)
	{
		slist[idx].grade = 'B';
	}
	else if(slist[idx].avg<80 && slist[idx].avg>=70)
	{
		slist[idx].grade = 'C';
	}
	else if(slist[idx].avg<70 && slist[idx].avg>=60)
	{
		slist[idx].grade = 'D';
	}
	else
	{
		slist[idx].grade = 'F';
	}
				idx++;
			}
			else if(strcmp(command, "print") == 0 )
			{
				print_students(slist, idx);
			}
			else if(strcmp(command, "find") == 0)
			{	
			 char findname[20];
				printf("이름 : ");
				scanf("%s", findname);
				printf("번호		  이름 중간 기말 평균 (학점)\n");
				for (int i=0; i<idx; i++)
				{
				
				if(strcmp(findname, slist[i].name) == 0)
				{
				print_one_student(slist[i], i);
				}
				}
			}
			else if(strcmp(command, "quit") == 0 )
			{
				break;
			}
			printf("\n");
		}
		
		return 0;
}

void print_one_student(STUDENT s, int no)
{
	printf("%d %20s %d %d %.1f (%c)\n", no+1, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
}

void print_students(STUDENT slist[], int n)
{
	printf("번호		  이름 중간 기말 평균 (학점)\n");
	int i;
	for (i=0; i<n; i++)
	{
		print_one_student(slist[i], i);
	}
 } 

void add_student(STUDENT *p)
{
	printf("이름 : ");
	scanf("%s", p->name);
	printf("중간고사 : ");
	scanf("%d", &p->exam[0]);
	printf("기말고사 : ");
	scanf("%d", &p->exam[1]);

}
