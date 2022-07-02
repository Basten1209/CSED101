#include <stdio.h>

char upperToLower(char c);
int getPosition(char c);

int main(){
	
	char a;
	printf("Input a character in Uppercase: ");
	scanf("%c", &a);
	char b = upperToLower(a);
	printf("\nLowercase of Entered character is %c \n", b);
	printf("Position of '%c' in English Alphabets is %d\n", b, getPosition(b));
	
	return 0;
}

char upperToLower(char c){
	char d;
	d=c+32;
	return d;
}

int getPosition(char c){
	int d;
	d=c-'a'+1;
	return d;
	
}
