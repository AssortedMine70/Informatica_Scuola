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
char *lucchetto(char * const dst, const char *src1, const char *src2) {
	unsigned i;
	*dst = '\0';
	for(i = 1; strncmp(src1+strlen(src1)-i, src2, i)!=0; ++i);
	strncat(dst, src1, strlen(src1)-i);
	strcat(dst, src2+i);
	return dst;
}

char *syllabify(char * const str) {
	for(char *pc = str; *(pc+1)!='\0'; ++pc)
		if(toupper(*pc)>toupper(*(pc+1))) {
			memmove(pc+2, pc+1, strlen(pc+1)+1);
			*(pc+1) = '-';
			++pc;
		}
	return str;
}

char *rlebase(char * const str) {
	for(char *pc = str; *(pc+1)!='\0'; ++pc)
		if(isalpha(*pc) && islower(*pc)) {
			memmove(pc+2, pc+1, strlen(pc+1)+1);
			if(isvowel(*pc))
				*(pc+1) = '0';
			else
				*(pc+1) = '1';
		}
	return str;
}

char *strmix(char * const dst, const char *src1, const char *src2) {
	const char *min = strlen(src1)>strlen(src2) ? src2 : src1;
	const char *max = strlen(src1)>strlen(src2) ? src1 : src2;
	*dst = '\0';
	const char *pc;
	for(pc = min; *(pc+1)!='\0'; ++pc) {
		strcat(dst, *pc);
		strcat(dst, *(max+(pc-min)));
	}
	strcat(dst, max+(pc-min));
	return dst;
}

int main() {
	char str[256], str1[256], str2[256];
	printf("lucchetto\n");
	fsgets(str1, sizeof(str1), stdin);
	fsgets(str2, sizeof(str2), stdin);
	printf("%s\n", lucchetto(str, str1, str2));
	printf("syllabify\n");
	printf("%s\n", syllabify(fsgets(str, sizeof(str), stdin)));
	printf("rlebase\n");
	printf("%s\n", rlebase(fsgets(str, sizeof(str), stdin)));
	printf("strmix\n");
	fsgets(str1, sizeof(str1), stdin);
	fsgets(str2, sizeof(str2), stdin);
	printf("%s\n", strmix(str, str1, str2));
	return 0;
}
