#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>

char getch();

typedef struct {
	char name[20];
	char sex;
	int age;
} Anagraphics;

char *fsgets(char *str, int size, FILE *file) {
	scanf(" ");
	fgets(str, size, file);
	while(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
	return str;
}

typedef enum { BLACK=0
	, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE, } COLORS;
void gotoxy(int x,int y){
	COORD V={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), V);
}
void printcolor(const char * str, COLORS Text, COLORS Background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	SetConsoleTextAttribute(hStdOut, (Text & 0xF) | ((Background & 0xF)<<4));
	printf("%s", str);
	SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
}
//Select Function (Array Lenght, Options Array[][256], Style (TRUE = >>, FALSE = Inverted Colors), CLS (if TRUE clears the Terminal after the selection), escExit (Exit or not the program at the pressing of esc button))
int Select(int n, char *Options[], _Bool style, _Bool CLS, _Bool escExit) {
	int input = 0, y = 0;
	for(int i = 0; i < n; i++)
	{
		if(style)
    		printf("	%s\n", Options[i]);
    	else
    		printf("%s\n", Options[i]);
	}
	while(1)
	{
		gotoxy(0, y);
		if(style)
			printf(">>");
		else
			printcolor(Options[y], BLACK, WHITE);
		input = getch();
		if(input == 72)
		{
			if(y > 0)
				y--;
			gotoxy(0, y);
			if(style)
				printf(">>");
			else
				printcolor(Options[y], BLACK, WHITE);
		}
		else if(input == 80)
		{
			if(y < n-1)
				y++;
			gotoxy(0, y);
			if(style)
				printf(">>");
			else
				printcolor(Options[y], BLACK, WHITE);
		}
		else if(input >= 49 && input <= 48+n)
		{
			y = input - 49;
			gotoxy(0, y);
			if(style)
				printf(">>");
			else
				printcolor(Options[y], BLACK, WHITE);
		}
		else if(input == 13)
		{
			if(CLS)
				system("cls");
			else
				gotoxy(0, n+1);
				return y;
		}
		else if(input == 27 && escExit)
		{
			system("cls");
			exit(0);
		}
		for(int j = 0; j < n; j++)
		{
			gotoxy(0, j);
			if(style)
				printf("  ");
			else
				printf("%s", Options[j]);
		}
	}
}

void printData(Anagraphics Data) {
	printf("%20s %c %4i\n", Data.name, Data.sex, Data.age);
}

void printAllData(size_t n, Anagraphics *Data) {
	printf("%20s %3s %s\n", "NOME", "SEX", "AGE");
	for(size_t i = 0; i<n; ++i)
		printData(Data[i]);
}

void scanData(Anagraphics *Data) {
	printf("Name: ");
	fsgets(Data->name, sizeof(Data->name), stdin);
	do {
		printf("Sex (M/F): ");
		scanf(" ");
		scanf("%c", &Data->sex);
		if(Data->sex != 'M' && Data->sex != 'F')
			printf("Invalid Input.\n");
	} while(Data->sex != 'M' && Data->sex != 'F');
	printf("Age: ");
	scanf("%i", &Data->age);
	printf("\n");
}

void sexCount(size_t n, Anagraphics *Data) {
	unsigned f = 0, m = 0;
	for(unsigned i = 0; i<n; ++i)
		if(Data[i].sex == 'M')
			++m;
		else
			++f; 
	printf("Ci sono %i Maschi e %i Femmine.\n", m, f);
}

void averageManAge(size_t n, Anagraphics *Data) {
	unsigned f = 0, m = 0;
	for(unsigned i = 0; i<n; ++i)
	printf("Ci sono %i Maschi e %i Femmine.\n", m, f);
}

int main() {
	Anagraphics Data[20];
	unsigned n, count = 0;
	printf("Quante persone si vogliono inserire? ");
	scanf("%u", &n);
	while(count<n) {
		scanData(&Data[count]);
		++count;
	}
	system("CLS");
	printAllData(n, Data);
	printf("----------------------------------\nPremere un Tasto per Continuare. Premere Esc nel Menu per uscire.");
	getch();
	system("CLS");
	char *selections[] = {
		"Quanti sono i maschi e quante sono le femmine",
		"L'eta' media dei soli maschi",
		"L'elenco dei nomi delle persone di età compresa tra i 20 e i 30 anni (esclusi)",
		"Determinare l’eta' della persona più vecchia e visualizzare il nome delle persone che hanno tale eta'",
		"Visualizzare i dati (sesso ed età) di una persona di cui si conosce il nome (inserito in input); emettere segnalazione se la persona e' inesistente",
		"Elenco dei dati di tutte le persone in formato tabellare",
	};
	do {
		switch(Select(6, selections, 0, 1, 1)) {
			case 0:
				sexCount(n, Data);
				break;
			case 1:
				averageManAge(n, Data);
				break;
		}
		printf("----------------------------------\nPremere un Tasto per tornare al Menu.");
		getch();
		system("CLS");
	} while(1);
	return 0;
}
