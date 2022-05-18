#include<stdio.h>
#include<string.h>

// Esercise 1B
size_t search(int *array, size_t n, int value) {
	if(array[n-1]==value || n==0)
		return n-1;
	else
		return search(array, --n, value);
}

// Esercise 2A
int mutualStrcpy_ric(char *destination, char *source, size_t len);

void strcpy_ric(char *destination, char *source) {
	mutualStrcpy_ric(destination, source, strlen(source)-1);
}

int mutualStrcpy_ric(char *destination, char *source, size_t len) {
	*(destination+len) = *(source+len);
	if (len==0)
		return 0;
	else
		return mutualStrcpy_ric(destination, source, --len);
}

// Esercise 2B
int mutualStrcmp_ric(char *str1, char *str2, size_t len);

int strcmp_ric(char *str1, char *str2) {
	if(strlen(str1)==strlen(str2))
		return mutualStrcmp_ric(str1, str2, strlen(str1));
	else if(strlen(str1)>strlen(str2))
		return 1;
	else
		return -1;
}

int mutualStrcmp_ric(char *str1, char *str2, size_t len) {
	if(str1+len>str2+len)
		return 1;
	else if(*(str2+len)<*(str1+len))
		return -1;
	else if(len==0 && *str1==*str2)
		return 0;
	else
		return mutualStrcmp_ric(str1, str2, --len);
}

// Esercise 3
int fatt(int n) {
	if(n==1)
		return 1;
	else
		return n*fatt(n-1);
}

int cobin(int n, int k) {
	if(n>=k)
		return fatt(n)/(fatt(k)*fatt(n-k));
	else
		return 0;
}

int main(void) {
	printf("1B | search:\n");
	int array[] = {3, 4, 1, 3};
	int n = search(array, sizeof(array)/sizeof(int), 5);
	if(n == -1)
		printf("n = %i | Valore non trovato.\n", n);
	else
		printf("n = %i | %i\n", n, array[n]);
	
	printf("2A | strcpy_ric:\n");
	char str1[] = "Hello World", str2[256];
	strcpy_ric(str2, str1);
	printf("%s", str2);
	
	printf("2B | strcpy_ric:\n");
	printf("%i\n", strcmp_ric(str2, str1));
	
	printf("3  | cobin\n");
	printf("%i\n", cobin(4, 3));
	
	return 0;
}
