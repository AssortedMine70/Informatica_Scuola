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

_Bool isvowel(char c) {
	return strchr("AEIOU", toupper(c))!=NULL;
}

char *code(char *str) {
	for(char *pc = str; *pc != '\0'; ++pc)
		if(isvowel(*pc)) {
			memmove(pc+2, pc, strlen(pc)+1);
			*(pc+1) = 'f';
			pc+=2;
		}
	return str;
}

char *decode(char *str) {
	for(char *pc = str; *pc != '\0'; ++pc)
		if(isvowel(*pc))
			memmove(pc, pc+2, strlen(pc)+1);
	return str;
}

int main() {
	char str[256];
	printf("Inserire la Stringa: ");
	printf("Alfabeto Farfallino: %s\n", code(fsgets(str, sizeof(str), stdin)));
	printf("Frase Originale    : %s\n", decode(str));
	return 0;
}
