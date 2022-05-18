#include <stdlib.h>
#include <stdio.h>
// Includere qui eventuali altri file di header (se necessario)
#include <string.h>
#include <assert.h>

// Creare qui la struct
typedef struct {
	int family;
	char name[29+1], type[9+1], subtype[9+1];
	int id, hp, atk, def, atkspeed, defspeed, movspeed;
} Pokemon;

int main() {
	int risposta1, risposta2, risposta3;
	char risposta4[29+1];
	// Aggiungete qui le definizioni delle variabili necessarie
	FILE *fp = fopen("pokemon.bin", "rb");
	Pokemon p;
	
	// Aggiungete qui il codice necessario al calcolo dei valori
	if(fp!=NULL) {
		risposta2 = 0;
		risposta3 = 0;
		while(fread(&p, sizeof(p), 1, fp)==1) {
			if(strcmp(p.subtype, " ")==0)
				++risposta2;
			if(p.atkspeed > p.defspeed)
				++risposta3;
		}
		risposta1 = ftell(fp)/sizeof(Pokemon);
		fseek(fp, sizeof(Pokemon)*10, SEEK_SET);
		assert(fread(&p, sizeof(p), 1, fp)==1);
		strcpy(risposta4, p.name);
		fclose(fp);
	} else
		perror("Error");
	
	// Stampa delle risposte
	printf("1. %d\n", risposta1);
	printf("2. %d\n", risposta2);
	printf("3. %d\n", risposta3);
	printf("4. %s\n", risposta4);
}
