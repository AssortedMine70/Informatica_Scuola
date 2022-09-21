// Federico Santucci, 4AIN
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int id;
	char nome[20];
} studente;

size_t countStudents(FILE *fp) {
	if(fp) {
		rewind(fp);
		int id;
		char name[20]; 
		size_t i = 0;
		while(fscanf(fp, "%i%s", &id, name)==2)
			++i;
		return i;
	} else
		return 0;
}

size_t readStudents(FILE *fp, studente *studArray) {
	if(fp) {
		rewind(fp);
		size_t i = 0;
		while(fscanf(fp, "%i%s", &studArray[i].id, studArray[i].nome)==2)
			++i;
		return i;
	} else
		return 0;
}

int main() {
	FILE *fp = fopen("studenti.txt", "rt");
	size_t n = countStudents(fp);
	studente *studArray = malloc(n * sizeof(studente));
	
	printf("Read %i Students:\n\n", (int)n);
	if(readStudents(fp, studArray)) {
		for(size_t i = 0; i < n; ++i)
			printf("%2i %s\n", studArray[i].id, studArray[i].nome);
		fclose(fp);
	}
	else
		perror("Errore");
	free(studArray);
	return 0;
}
