#include <stdio.h>

typedef struct {
	char nome[20+1], cognome[20+1];
	unsigned eta;
} record;

int main() {
	FILE *fp = fopen("file.bin", "w+b");
	// r  = APRE IL FILE, LETTURA
	// w  = RICREA FILE, SCRITTURA
	// a  = APRE IL FILE, AGGIUNGE IN FONDO
	// r+ = APRE FILE IN LETTURA/SCRITTURA, CAMBIARE MODALITA' CON FSEEK
	// w+ = CREA FILE IN LETTURA/SCRITTURA, CAMBIARE MODALITA' CON FSEEK
	if(fp!=NULL) {
#ifdef VAR
		for(size_t i = 1; i<=10; ++i)
			fwrite(&i, sizeof(i), 1, fp);
		fseek(fp, 0, SEEK_SET);
		size_t i;
		while(fread(&i, sizeof(i), 1, fp)==1)
			printf("%u\n", (unsigned)i);
#endif
#ifdef VEC
		size_t vec[] = {28, 42, 69, 104, 420};
//		fwrite(vec, sizeof(vec[0]), sizeof(vec)/sizeof(vec[0]), fp);
		fwrite(vec, sizeof(vec), 1, fp);
		fseek(fp, 0, SEEK_SET);
//		size_t buffer;
//		while(fread(&buffer, sizeof(buffer), 1, fp)==1)
//			printf("%u\n", (unsigned)buffer);
		size_t buffer[5];
		while(fread(&buffer, sizeof(buffer), 1, fp)==1)
			for(size_t i = 0; i<sizeof(buffer)/sizeof(buffer[0]); ++i)
				printf("%u\n", (unsigned)buffer[i]);
#endif
#ifdef STRUCT
		record r = {.nome = "Mars", .cognome = "Baldini", .eta = 17};
		fwrite(&r, sizeof(record), 1, fp);
		fseek(fp, 0, SEEK_SET);
		record jinx;
		while(fread(&jinx, sizeof(record), 1, fp)==1)
			printf("%s\n%s\n%u\n", jinx.nome, jinx.cognome, jinx.eta);
#endif
	} else 
		perror("Errore");
	
	return 0;
}
