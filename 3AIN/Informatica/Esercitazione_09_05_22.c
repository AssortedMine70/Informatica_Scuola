#include <stdlib.h>
#include <stdio.h>
// Includere qui eventuali altri file di header (se necessario)
#include <string.h>
#include <ctype.h>

int main() {
	int risposta1, risposta2, risposta3, risposta4, risposta6, risposta7;
	char risposta5[100+1];
	// Aggiungete qui le definizioni delle variabili necessarie
	FILE *fp = fopen("content.txt", "rt");
	char c, lastc, buffer[200+1], spaces;
	int key = 9;
	// Aggiungete qui il codice necessario al calcolo dei valori
	if(fp!=NULL) {
		// risposta1
		risposta1 = 0;
		while((c = fgetc(fp))!=EOF)
				++risposta1;
		// risposta2
		rewind(fp);
		risposta2 = fgetc(fp)!=EOF ? 1 : 0;
		rewind(fp);
		while((c = fgetc(fp))!=EOF)
			if(c == '\n')
				++risposta2;
		// risposta3
		rewind(fp);
		risposta3 = 0;
		while(fgets(buffer, sizeof(buffer), fp)!=NULL) {
			spaces = 0;
			for(char *pc = buffer; *pc!='\0' && spaces<=1; ++pc)
				if(*pc==' ')
					++spaces;
			if(spaces<=1)
				++risposta3;
		}
		// writing decrypted file
		FILE *clear = fopen("clear.txt", "w+t");
		if(clear!=NULL) {
			rewind(fp);
			while((c = fgetc(fp))!=EOF)
				if(c!=' ' && c!='\n')
					fputc(c-key, clear);
				else
					fputc(c, clear);
			// risposta4
			risposta4 = 0;
			rewind(clear);
			while((c = fgetc(clear))!=EOF)
				if(strchr("AEIOU", toupper(c))!=NULL)
					++risposta4;
			// risposta5
			rewind(clear);
			for(size_t i = 1; fgets(risposta5, sizeof(risposta5), clear), i<59; ++i);
			while(risposta5[strlen(risposta5)-1]=='\n')
				risposta5[strlen(risposta5)-1] ='\0';
			fclose(clear);
		} else
			perror("Error");
		// risposta6
		risposta6 = 0;
		rewind(fp);
		while(fgets(buffer, sizeof(buffer), fp)!=NULL)
			if(risposta6<(int)strlen(buffer))
				risposta6 = strlen(buffer)-1; // removes '/0'
		// risposta7
		risposta7 = 0;
		rewind(fp);
		lastc = fgetc(fp);
		while((c = fgetc(fp))!=EOF) {
			if(lastc == c)
				++risposta7;
			lastc = c;
		}
		fclose(fp);
	} else
		perror("Errore");
	
	// Stampa delle risposte
	printf("1. %d\n", risposta1);
	printf("2. %d\n", risposta2);
	printf("3. %d\n", risposta3);
	printf("4. %d\n", risposta4);
	printf("5. %s\n", risposta5);
	printf("6. %d\n", risposta6);
	printf("7. %d\n", risposta7);
	
	return 0;
}
