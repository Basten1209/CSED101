#include <stdio.h>

float calc_average(int a, int b);
char calc_grade(float avg);

int main() {
	int mid, fin;
	
	printf("Enter your midterm score : ");
	scanf("%d", &mid);
	printf("Enter your final score : ");
	scanf("%d", &fin);
	
	printf("Average : %.1f",calc_average(mid, fin));
	printf("\nGrade : %c", calc_grade(calc_average(mid,fin)));
	
	return 0;
}

float calc_average(int a, int b) {
	float c;
	c=a+b;
	c=c/2;
	
	return c;
}
char calc_grade(float avg) {
	char grade;
	if (avg>=90){
		grade = 'A';
	}
	else if (80<=avg && avg<90){
		grade = 'B';
	}
	else if (70<=avg && avg<80){
		grade = 'C';
	}
	else if (60<=avg && avg<70){
		grade = 'D';
	}
	else if (avg<60){
		grade = 'E';
	}
	return grade;
}
