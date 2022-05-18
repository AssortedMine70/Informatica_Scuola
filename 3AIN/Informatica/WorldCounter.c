#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *fsgets(char *str, int size, FILE *file) {
	fflush(stdin);
	fgets(str, size, file);
	while(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
	return str;
}

int wordcounter(char *str) {
	unsigned count = 0;
	for(char *pc = str; pc=='\0'; ++pc)
		if(*pc==' ' || *pc=='\n' || *pc=='\t')
			++count;
	return ++count;
}

int main() {
	char str[256];
	printf("%i", wordcounter(fsgets(str, sizeof(str), stdin)));
	return 0;
}
