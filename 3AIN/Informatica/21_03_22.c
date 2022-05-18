#include<stdio.h>
#include<limits.h>
#include<assert.h>
#include<string.h>
#include<ctype.h>

// Exercises 4, 6, 7 with fgetc/fputc
unsigned contaparole(const char *filename) {
	FILE *fp = fopen(filename, "r");
	assert(fp);
	char c;
	unsigned count = 0, flag = 1;
	while((c = fgetc(fp))!=EOF) {
		if(isspace(c))
			++count;
		flag = 0;
	}
	fclose(fp);
	if(flag)
		return 0;
	else
		return ++count;
}

void copiafile2(const char *dst, const char *src) {
	FILE *fsrc = fopen(src, "r"), *fdst = fopen(dst, "w");
	assert(fsrc); assert(fdst);
	char c;
	while((c = fgetc(fsrc))!=EOF)
		if(isupper(c))
			fputc(tolower(c), fdst);
		else
			fputc(toupper(c), fdst);
	fclose(fsrc); fclose(fdst);
}

void copialettere(const char *filename) {
	FILE *fp = fopen(filename, "r"), *alpha = fopen("lettere.txt", "w"), *others = fopen("altri_char.txt", "w");
	assert(fp); assert(alpha); assert(others);
	char c;
	while((c = getc(fp))!=EOF)
		if(isalpha(c))
			fputc(c, alpha);
		else
			fputc(c, others);
	fclose(fp); fclose(alpha); fclose(others);
}

// Exercises 11, 12, 13 with fgets/fputs
void accordalinee(const char *filename) {
	FILE *src = fopen(filename, "r"), *dst = fopen("risultato.txt", "w");
	assert(src); assert(dst);
	char buffer[256];
	while(fgets(buffer, sizeof(buffer), src)!=NULL)
		if(strlen(buffer)>20)
			fputs("--LINEA TROPPO LUNGA--\n", dst);
		else
			fputs(buffer, dst);
	fclose(src); fclose(dst);
}

unsigned contalinee(const char *filename, const char *str) {
	FILE *fp = fopen(filename, "r");
	assert(fp);
	char buffer[256];
	unsigned count = 0;
	while(fgets(buffer, sizeof(buffer), fp)!=NULL)
		if(strstr(buffer, str)!=NULL)
			++count;
	fclose(fp);
	return count;
}

void paginaweb() {
	FILE *fp = fopen("test.html", "w");
	assert(fp);
	fputs("<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; charset=UTF-8'><title>Pagina generata automaticamente</title></head><body><p style='color: red;'>Questa pagina &egrave; stata generata automaticamenteda un programma scritto in linguaggio C.</p></body></html>", fp);
	fclose(fp);
}

// Exercises 17, 19, 20 with fscanf/fprintf
void statistica(const char *dst, const char *src) {
	FILE *fsrc = fopen(src, "r"), *fdst = fopen(dst, "w");
	assert(fsrc); assert(fdst);
	int x, y;
	while(fscanf(fsrc, "%i %i", &x, &y)==2)
		fprintf(fdst, "%i %.1f\n", x+y, (x+y)/.2);
	fclose(fsrc); fclose(fdst);
}

void maxmin(const char *dst, const char *src) {
	FILE *fsrc = fopen(src, "r"), *fdst = fopen(dst, "w");
	assert(fsrc); assert(fdst);
	int max, min, n;
	if(fscanf(fsrc, "%i", &n)!=1)
		n = 0;
	max=min=n;
	while(fscanf(fsrc, "%i", &n)==1) {
		if(n>max)
			max = n;
		else if(n<min)
			min = n;
	}
	fprintf(fdst, "Valore minimo: %i\nValore massimo: %i", min, max);
	fclose(fsrc); fclose(fdst);
}

void voti1(const char *filename) {
	FILE *fp = fopen(filename, "r"), *medie = fopen("medie.txt", "w"), *esiti = fopen("esiti.txt", "w");
	assert(fp); assert(medie); assert(esiti);
	char name[256], surname[256];
	unsigned n;
	float vote;
	while(fscanf(fp, "%s %s %u", name, surname, &n)==3) {
		float avg = 0;
		for(unsigned i = 0; i<n; ++i) {
			fscanf(fp, "%f", &vote);
			avg+=vote;
		}
		avg/=n;
		fprintf(medie, "%s %s %.1f\n", name, surname, avg);
		fprintf(esiti, "%s %s %s\n", name, surname, avg<6?"debito":"promosso");
	}
	fclose(fp); fclose(medie); fclose(esiti);
}
