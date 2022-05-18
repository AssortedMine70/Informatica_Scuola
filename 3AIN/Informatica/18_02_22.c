#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Support Functions
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

// Exercises Functions
unsigned consonantscounts(const char *str) {
	unsigned count = 0;
	for(const char *pc = str; *pc!='\0'; ++pc)
		if(isalpha(*pc) && !isvowel(*pc))
			++count;
	return count;
}

char *swapCase( char * const str) {
	for(char *pc = str; *pc!='\0'; ++pc)
		if(isalpha(*pc)) {
			if(isupper(*pc))
				*pc = tolower(*pc);
			else
				*pc = toupper(*pc);			
		}
	return str;
}

char *rotatevowels(char * const str) {
	char vowels[] = "aeiou";
	for(char *pc = str; *pc!='\0'; ++pc)
		if(isvowel(*pc))
			for(size_t i = 0; ; ++i)
				if(vowels[i] == *pc) {
					*pc = vowels[(i+1)%5];
					break;
				}
	return str;
}

char *strltrim(char * const str) {
	char *pw = str, *pr = str;
	for(; isspace(*(pr)); ++pr);
	for(; *pr!='\0'; ++pr)
		*pw++=*pr;
	return str;
}

char *strrtrim(char * const str) {
	for(char *pc = str+strlen(str)-1; isspace(*pc); pc = str+strlen(str)-1)
		*pc = '\0';
	return str;
}

int main() {
	char str[256];
	printf("consonantscounts\n");
	printf("%u\n",consonantscounts(fsgets(str, sizeof(str), stdin)));
	printf("swapCase\n");
	printf("%s\n",swapCase(fsgets(str, sizeof(str), stdin)));
	printf("rotatevowels\n");
	printf("%s\n",rotatevowels(fsgets(str, sizeof(str), stdin)));
	printf("strltrim\n");
	printf("%s\n",strltrim(fsgets(str, sizeof(str), stdin)));
	printf("strrtrim\n");
	printf("%s.\n",strrtrim(fsgets(str, sizeof(str), stdin)));
	return 0;
}
