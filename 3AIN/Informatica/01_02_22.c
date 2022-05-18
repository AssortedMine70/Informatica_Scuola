#include<stdio.h>
#include<string.h>
#include<ctype.h>

void fsgets(char *string, int size, FILE *file) {
	fgets(string, size, file);
	while(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
}

void Censor(char string[256], char key[256]) {
	char *pc = strstr(string, key);
	while(pc!=NULL) {
		memset(pc, '*', strlen(key));
		pc = strstr(string, key);
	}
}

int main() {
	//------------------------------//
	char str1[256], str2[128];
	printf("Es 1\nInserire le 2 Stringhe da concatenare:\nPrima Stringa: ");
	fsgets(str1, sizeof(str1)/2, stdin);
	printf("Seconda Stringa: ");
	fsgets(str2, sizeof(str2), stdin);
	strcat(str1, str2);
	printf("%s\n", str1);
	//------------------------------//
	char string[256], key[256];
	printf("\nEs 2\nInserire la Stringa da Censurare:\n");
	fsgets(string, sizeof(string), stdin);
	printf("Inserire la parola da Censurare:\n");
	fsgets(key, sizeof(key), stdin);
	Censor(string, key);
	printf("Frase Censurata:\n%s", string);
	
	return 0;
}
