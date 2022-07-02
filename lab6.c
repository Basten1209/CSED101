#include <stdio.h>

int main()
{
	FILE *infile, *outfile;
	float user=0; //인원수 체크
	int sid; //ID 
	int mid, fin; //중간, 기말 점수 
	float last=0; //총점
	char grade; //학점 
	float lastsum; //총점  합 
	float avg; //평균
	 
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
	fprintf(outfile, " 학번 	총점(학점)\n");
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
	fprintf(outfile, " 평균 	%.1f\n", avg);
	
	return 0;
}
