#include <stdio.h>

int main()
{
	FILE *infile, *outfile;
	float user=0; //�ο��� üũ
	int sid; //ID 
	int mid, fin; //�߰�, �⸻ ���� 
	float last=0; //����
	char grade; //���� 
	float lastsum; //����  �� 
	float avg; //���
	 
	infile = fopen("score.txt", "r");
	
	if (infile==NULL)
	{
		printf("could not open input file\n");
		return 100;
	}
	
	outfile = fopen("report.txt", "w");
	if(outfile==NULL){
		printf("could not open output file\n");
		return 102;
	}
	
	fprintf(outfile, "===================\n");
	fprintf(outfile, " �й� 	����(����)\n");
	fprintf(outfile, "===================\n");
		
	while(fscanf(infile, "%d %d %d", &sid, &mid, &fin) != EOF){
		user++;
		last = mid*0.4+fin*0.6;
		lastsum += last;
		if (last>=90){
			grade = 'A';
		}
		else if(last>=80&&last<90){
			grade = 'B';
		}
		else if(last>=70&&last>80){
			grade = 'C';
		}
		else if(last>=60&&last<70){
			grade = 'D';
		}
		else{
			grade = 'F';
		}
		
		fprintf(outfile, "%d	%.1f (%c)\n", sid, last, grade);
	}
	avg = lastsum/user;
	fprintf(outfile, "===================\n");
	fprintf(outfile, " ��� 	%.1f\n", avg);
	
	return 0;
}
