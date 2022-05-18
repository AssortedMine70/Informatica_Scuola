#include<stdio.h>
#include<string.h>
#include<ctype.h>

char *fsgets(char *str, int size, FILE *file) {
	scanf(" ");
	fgets(str, size, file);
	while(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
	return str;
}

_Bool isvowel(char c) {
	return strchr("AEIOU", c)!=NULL;
}

_Bool monovocalic(const char *str) {
	char *vowels = "aeiou";
	unsigned count = 0;
	for(char *pc = vowels; *pc!='\0'; ++pc)
		if(strchr(str, *pc)!=NULL)
			++count;
	return count>1 ? 0 : 1;
}

_Bool monoconsonatic(const char *str) {
	char *consonants = "bcdfghlmnpqrstvz";
	unsigned count = 0;
	for(char *pc = consonants; *pc!='\0'; ++pc)
		if(strchr(str, *pc)!=NULL)
			++count;
	return count>1 ? 0 : 1;
}

_Bool eteroletteral(const char *str) {
	unsigned bcount = 0;
	for(char c = 'A'; c<='Z'; ++c) {
		unsigned count = 0;
		for(const char *pc=str; *pc!='\0'; ++pc)
			if(*pc==c)
				++count;
		if(count)
			++bcount;
		if(bcount>1)
			return 0;
	}
	return 1;
}

_Bool eterovocalic(const char *str) {
	char *vowels = "aeiou";
	unsigned bcount = 0;
	for(char *pv = vowels; *pv!='\0'; ++pv) {
		unsigned count = 0;
		for(const char *pc=str; *pc!='\0'; ++pc)
			if(*pc==*pv)
				++count;
		if(count)
			++bcount;
		if(bcount>1)
			return 0;
	}
	return 1;
}

_Bool evenvocalic(const char *str) {
	for(const char *pc=str; *pc!='\0'; ++pc)
		if((pc-str)%2 ^ isvowel(*pc))
			return 0;
	return 1;
}

_Bool evenconsonatic(const char *str) {
	for(const char *pc=str; *pc!='\0'; ++pc)
		if((pc-str)%2 ^ !isvowel(*pc))
			return 0;
	return 1;
}

_Bool omovocalic(const char *str1, const char *str2) {
	for(unsigned i = 0; i<strlen(str1); ++i)
		if(isvowel(*str1) && !isvowel(*str2))
			return 0;
	return 1;
}

_Bool omoconsonatic(const char *str1, const char *str2) {
	for(unsigned i = 0; i<strlen(str1); ++i)
		if(!isvowel(*str1) && isvowel(*str2))
			return 0;
	return 1;
}

_Bool alphaorder(const char *str) {
	for(unsigned i = 0; i<strlen(str)+1; ++i)
		if((i<strlen(str)/2) ^ (str[i]<=str[i+1]))
			return 0;
	return 1;
}

_Bool notalphaorder(const char *str) {
	for(unsigned i = 0; str[i+1]!='\0'; ++i)
		if((i<strlen(str)/2) ^ (str[i]>=str[i+1]))
			return 0;
	return 1;
}

_Bool palindromevowel(const char *str) {
	for(unsigned i = 0; i<strlen(str)/2; ++i)
		if(!(isvowel(str[i]) && isvowel(str[strlen(str)-i-1])))
			return 0;
	return 1;
}

int main() {
	
	return 0;
}
