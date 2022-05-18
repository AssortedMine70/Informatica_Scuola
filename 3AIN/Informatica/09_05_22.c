/*
Un provveditorato agli studi vuole avere una registrazione di tutte le scuole della provincia e del numero di alunni di ogni scuola, in modo da poter ottenere, 
dato il nome di una scuola, il numero dei suoi alunni, oppure l'elenco delle scuole con un numero di alunni inferiore o superiore ad un valore assegnato.
 - scrivere un programma per creare il file (o i file) con i nomi delle scuole ed il numero di alunni corrispondenti;
 - scrivere un programma che dato il nome di una scuola visualizzi il numero dei suoi alunni;
 - scrivere un programma che dato il numero di alunni, scriva l'elenco delle scuole con un numero di alunni inferiore al valore dato;
 - scrivere un programma che dato il numero di alunni, scriva l'elenco delle scuole con un numero di alunni maggiore o uguale al valore dato;
 - scrivere un programma unico che permetta di scegliere una delle richieste del punto 2 ed avere il risultato corrispondente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define TEXT
struct scuole {
	char nomescuola[30+1];
	int numeroalunni;
};


int main()
{
	// genero un file binario casuale
	struct scuole s;
#ifdef TEXT
	FILE *fw = fopen("scuole.txt", "w+t");
#else
	FILE *fw = fopen("scuole.bin", "w+b");
#endif
	if(fw)
	{
		for(int i=0; i<365; i++)
		{
			for(size_t k=0; k<sizeof(s.nomescuola); k++)
				s.nomescuola[k]=rand()%26+'A';
			s.nomescuola[rand()%(sizeof(s.nomescuola)-1)+1]='\0';
			s.numeroalunni = 500+rand()%(1200-500+1);
			printf("%-30s %u\n", s.nomescuola, s.numeroalunni);
#ifdef TEXT
			fprintf(fw, "%s %u\n", s.nomescuola, s.numeroalunni);
#else
			fwrite(&s, sizeof(s), 1, fw);
#endif
		}
		// cerco il numero alunni dato il nome della scuola
		rewind(fw);
		int max = INT_MIN;
		char nomescuoladacercare[100+1];
		printf("\nChe scuola si vuole cercare?\n");
		fgets(nomescuoladacercare, sizeof(nomescuoladacercare), stdin);
		if(strlen(nomescuoladacercare)>0 && nomescuoladacercare[strlen(nomescuoladacercare)-1]=='\n')
			nomescuoladacercare[strlen(nomescuoladacercare)-1] = '\0';
#ifdef TEXT
		while(fscanf(fw, "%s %i", s.nomescuola, &s.numeroalunni)>0)
#else
		while(fread(&s, sizeof(s), 1, fw)>0)
#endif
		{
			if(strcmp(nomescuoladacercare, s.nomescuola)==0)
				printf("%-30s %u\n", s.nomescuola, s.numeroalunni);
		}
		
		printf("Numero di studenti: ");
		scanf("%i", &max);
		
		rewind(fw);
		printf("\nINFERIORI A %i\n\n", max);
#ifdef TEXT
		while(fscanf(fw, "%s %i", s.nomescuola, &s.numeroalunni)>0)
#else
		while(fread(&s, sizeof(s), 1, fw)>0)
#endif
		{
			if(s.numeroalunni<max)
				printf("%-30s %u\n", s.nomescuola, s.numeroalunni);
		}
		
		rewind(fw);
		printf("\nMAGGIORI/UGUALI A %i\n\n", max);
#ifdef TEXT
		while(fscanf(fw, "%s %i", s.nomescuola, &s.numeroalunni)>0)
#else
		while(fread(&s, sizeof(s), 1, fw)>0)
#endif
		{
			if(s.numeroalunni>=max)
				printf("%-30s %u\n", s.nomescuola, s.numeroalunni);
		}
		
		
		
		fclose(fw);
	}
	return 0;
}
