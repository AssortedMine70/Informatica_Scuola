#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main() {
	char str[256];
	printf("Inserire una Frase:\n");
	fgets(str, 256, stdin);
	
	for(unsigned i = 0; i<strlen(str)-1; ++i)
		if(isspace(str[i]))
			str[i] = '*';
		else if(strchr("AEIOU", toupper(str[i]))!=NULL)
			str[i] = '.';
		else
			str[i] = '-';
	
	printf("%s", str);
	
	return 0;
}
