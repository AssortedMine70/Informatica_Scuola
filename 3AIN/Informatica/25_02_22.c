#include<stdio.h>
#include<string.h>
#include<ctype.h>

void free(char * const str);

_Bool istautogram(const char * str) {
	char c = *str;
	for(const char *pc = str+1; *pc!='\0'; ++pc)
		if(*pc == ' ' && toupper(*(pc+1)) != toupper(c))
			return 0;
	return 1;
}

char *hashtagyoda(char * const str) {
	for(size_t i = 0; i<strlen(str)/2; ++i) {
		int temp = str[i];
        str[i] = str[strlen(str)-i-1];
        str[strlen(str)-i-1] = temp;
	}
	char *pw = str;
	for(char *pc = str; *pc!='\0'; ++pc) {
		if(*(pc+1) == ' ' || *(pc+1) == '\0') {
			for(int i = 0; i<(pc-pw+1)/2; ++i) {
				int temp = pw[i];
        		pw[i] = pw[(pc-pw)-i];
        		pw[(pc-pw)-i] = temp;
			}
			pw = pc+2;
		}
	}
	return str;
}

size_t wordmaxlength(const char * str) {
	size_t max = 0;
	char *dup = strdup(str), *token = strtok(dup, " ");
	while (token!=NULL) {
		if(strlen(token)>max)
			max = strlen(token);
		token = strtok(NULL, " ");
	}
	free(dup);
	return max;
}

const char *getlonger(const char * str1, const char * str2) {
	return strlen(str1)>strlen(str2) ? str1 : str2;
}

const char *getlesser(const char * str1, const char * str2) {
	return strcmp(str1, str2)>0 ? str1 : str2;
}

_Bool islipogram(const char * src) {
	unsigned count = 0;
	for(char c = 'a'; c<='z'; ++c)
		if(strchr(src, c)!=NULL)
			++count;
	return count==25;
}

int main() {
	char str[256] = "Veni vidi vici";
	char str2[256] = "Carlo Magno re del Sacro Romano Impero";
	char str3[256] = "abcdefghijklmnoprstuvwxyz";
	printf("%i\n", istautogram("Veni, vidi, vici"));
	printf("%s\n", hashtagyoda(str));
	printf("%zu\n", wordmaxlength(str));
	printf("%s\n", getlonger(str, str2));
	printf("%s\n", getlesser(str, str2));
	printf("%i\n", islipogram(str3));
	return 0;
}
