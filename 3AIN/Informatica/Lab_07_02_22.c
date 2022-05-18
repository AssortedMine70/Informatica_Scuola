#include<stdio.h>
#include<string.h>
#include<ctype.h>

void fsgets(char *str, int size, FILE *file) {
	fflush(stdin);
	fgets(str, size, file);
	while(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
}

void removeChars(char *str) {
	for(size_t i = 0; i<strlen(str); ++i)
		if(str[i]=='.' || str[i]=='-')
			str[i] = ' ';
}

int main() {
	char str[255];
	printf("Inserire una Stringa: ");
	fsgets(str, sizeof(str), stdin);
	removeChars(str);
	printf("Stringa senza punti e trattini: %s", str);
	return 0;
}
