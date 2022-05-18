#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

// Constants
#define SETUP_TIME		150
#define ANIMATION_TIME	1000
#define TABLE_X			20
#define TABLE_Y			5
#define TABLE_WIDTH		96
#define TABLE_HIGH		24

// Data Structures Declarations
enum Types{COPPE = 1, DENARA, SPADE, BASTONI};

struct Card {
	unsigned seed;  // from 1 to 4. (Coppe, Denara, Spade, Bastoni)
	unsigned value; // from 1 to 10.
};					// 0, 0 is NULL.

struct Stack {
	struct Card cards[11];
	int sp;
};

struct Deck {
	struct Card cards[36]; // 40-4 = 36. Aces are already on the table.
	size_t sp;
};

// Cards Functions
void gotoxy(short col, short row) {
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position={col,row};
	SetConsoleCursorPosition(h,position);
}

void Card_Print(size_t x, size_t y, struct Card carta) {
	for(size_t i = 0; i<7; ++i) {
		gotoxy(x, y+i);
		if(i == 0)
			printf("/--------\\\n");
		else if(i == 6)
			printf("\\--------/\n");
		else if(i == 1 || i == 5)
			printf("|%2u    %-2u|\n", carta.value, carta.value);
		else if(i == 3)
			switch(carta.seed) {
				case COPPE: 
					printf("| COPPE  |\n");
					break;
				case DENARA: 
					printf("| DENARA |\n");
					break;
				case SPADE: 
					printf("| SPADE  |\n");
					break;
				case BASTONI: 
					printf("| BASTONI|\n");
					break;
				default:
					printf("| VUOTO  |\n");
			}
		else
			printf("|        |\n");
	}
}

char *Card_Nominal(struct Card carta, char *str) {
	*str = '\0';
	switch(carta.value) {
				case 1:
				    strcat(str, "ASSO");
					break;
				case 2:
					strcat(str, "2");
					break;
				case 3:
					strcat(str, "3");
					break;
				case 4:
					strcat(str, "4");
					break;
				case 5:
					strcat(str, "5");
					break;
				case 6:
					strcat(str, "6");
					break;
				case 7:
					strcat(str, "7");
					break;
				case 8:
					strcat(str, "FANTE");
					break;
				case 9:
					strcat(str, "CAVALLO");
					break;
				case 10:
					strcat(str, "RE");
					break;
				default:
					strcat(str, "VUOTO");
	}
	switch(carta.seed) {
				case COPPE:
				    strcat(str, " di COPPE");
					break;
				case DENARA:
					strcat(str, " di DENARA");
					break;
				case SPADE:
					strcat(str, " di SPADE");
					break;
				case BASTONI:
					strcat(str, " di BASTONI");
					break;
				default:
					strcat(str, " di VUOTO");
	}
	return str;
}

// Stack Functions
void Stack_Push(struct Stack *pila, struct Card carta) {
	size_t sp = pila->sp;
	if(sp<10) {
		pila->cards[sp] = carta;
		pila->sp = sp+1;
	}
}

struct Card Stack_Pop(struct Stack *pila) {
	int sp = pila->sp;
	pila->sp = --sp;
	return pila->cards[sp];
}

void Stack_Print_dx(size_t x, size_t y, struct Stack pila) {
	for(int i = 0; i<pila.sp; ++i)
			Card_Print(x+i*8, y, pila.cards[i]);
}

void Stack_Print_sx(size_t x, size_t y, struct Stack pila) {
	for(int i = 0; i<pila.sp; ++i)
		Card_Print(x-9-i*8, y, pila.cards[i]);
}

// Deck Functions
struct Deck Deck_Generate(void) {
	srand(time(NULL));
	struct Deck Mazzo;
	Mazzo.sp = 36; // The Deck top is set to maximum.
	struct Card nullCard = {.seed = 0, .value = 0};
	for(size_t i = 0; i<36; ++i)
		Mazzo.cards[i] = nullCard;
	struct Card nextCard = {.seed = COPPE, .value = 2};
	for(size_t i = 0, flag = 36; flag!=0; ++i) { // This loop repeats untill all 36 cards are positioned.
		_Bool tag = 1;
		while(tag) { // This loop finds a valid index for the new card.
			size_t j = rand()%36;
			if(Mazzo.cards[j].value==0) {
				Mazzo.cards[j] = nextCard;
				--flag;
				tag = 0;
			}
		}
		if(nextCard.value<10) // Updates the variable nextCard.
			nextCard.value++;
		else if(nextCard.seed<4) {
			nextCard.seed++;
			nextCard.value = 2;
		}
	}
	return Mazzo;
}

struct Card Deck_TakeCard(struct Deck *deck) {
	int sp = deck->sp;
	if(--sp>=0) {
		deck->sp = sp;
		return deck->cards[sp];
	} else {
		struct Card voidCard = {0,0};
		return voidCard;
	}
}

// Table Functions
void Table_Zero(struct Stack Table[4][3]) {
	for(size_t i = 0; i<4; ++i)
		for(size_t j = 0; j<3; ++j) {
			Table[i][j].sp = 0;
			for(size_t y = 0; y<10; ++y) {
				Table[i][j].cards[y].value = 0;
				Table[i][j].cards[y].seed = 0;
			}
		}
	for(size_t i = 0; i<4; ++i) {
		struct Card Ace = {.seed = i+1, .value = 1};
		Stack_Push(&Table[i][1], Ace);
	}
}

void Table_Print(size_t x, size_t y, struct Stack Table[4][3]) {
	for(size_t i = 0; i<4; ++i)
		for(size_t j = 0; j<3; ++j)
			switch(j) {
				case 0:
					Stack_Print_sx(x+41, y+(i*7), Table[i][j]);
					break;
				case 1:
					Card_Print(x+43, y+(i*7), Table[i][j].cards[Table[i][j].sp-1]);
					break;
				case 2:
					Stack_Print_dx(x+54, y+(i*7), Table[i][j]);
					break;
			}
}

void Table_Init(size_t x, size_t y, struct Stack Table[4][3]) {
	Table_Zero(Table);
	Table_Print(x, y, Table);
	Sleep(ANIMATION_TIME);
	struct Deck Mazzo = Deck_Generate();
	for(size_t i = 0; i<4; ++i)
		for(size_t j = 0; j<3; j+=2)
			for(size_t g = i>=2?4:5; g-->0; ) {
				Stack_Push(&Table[i][j], Deck_TakeCard(&Mazzo));
				Table_Print(x, y, Table);
				Sleep(SETUP_TIME);
			}
}

// Game Functions
_Bool Game_Move(struct Stack Table[4][3], size_t x2, size_t y2, size_t x1, size_t y1) {
	if(Table[y1][x1].sp!=0) {
		if(Table[y2][x2].sp==0) {
			Stack_Push(&Table[y2][x2], Stack_Pop(&Table[y1][x1]));
			return 1;
		}
		else {
			struct Card scrCard = Table[y1][x1].cards[Table[y1][x1].sp-1],
						dstCard = Table[y2][x2].cards[Table[y2][x2].sp-1];
			if(x2 == 1) {
				if(((dstCard.value+1) == scrCard.value) && (dstCard.seed == scrCard.seed)) {
					Stack_Push(&Table[y2][x2], Stack_Pop(&Table[y1][x1]));
					return 1;
				}
			} else if((dstCard.value == (scrCard.value+1)) && (dstCard.seed != scrCard.seed)) {
					Stack_Push(&Table[y2][x2], Stack_Pop(&Table[y1][x1]));
					return 1;
			}
		}
	}
	return 0;
}

_Bool Game_CeckMove(struct Stack Table[4][3], size_t x2, size_t y2, size_t x1, size_t y1) {
	if(Table[y1][x1].sp!=0) {
		if(Table[y2][x2].sp==0)
			return 1;
		else {
			struct Card scrCard = Table[y1][x1].cards[Table[y1][x1].sp-1],
						dstCard = Table[y2][x2].cards[Table[y2][x2].sp-1];
			if(x2 == 1) {
				if(((dstCard.value+1) == scrCard.value) && (dstCard.seed == scrCard.seed))
					return 1;
			} else if((dstCard.value == (scrCard.value+1)) && (dstCard.seed != scrCard.seed))
					return 1;
		}
	}
	return 0;
}

_Bool Game_CeckUnderCard(struct Stack Table[4][3], size_t x, size_t y) {
	if((Table[y][x].cards[Table[y][x].sp-2].value)==(Table[y][x].cards[Table[y][x].sp-1].value+1) &&
	  (Table[y][x].cards[Table[y][x].sp-2].seed) !=(Table[y][x].cards[Table[y][x].sp-1].seed     ))
		return 0;
	return 1;
}

_Bool Game_NullToNull(struct Stack Table[4][3], size_t x2, size_t y2, size_t x1, size_t y1) {
	if(Table[y1][x1].cards[Table[y1][x1].sp-2].seed  == 0 &&
	   Table[y2][x2].cards[Table[y2][x2].sp-1].seed  == 0 )
		return 0;
	return 1;
}

size_t Game_Movement(size_t *x2, size_t *y2, size_t *x1, size_t *y1, struct Stack Table[4][3]) {
	gotoxy(0, TABLE_Y+30);
	printf("Seleziona la carta che vuoi spostare.");
	*x1 = 0; *y1 = 0;
	int input = 'a';
	size_t x = TABLE_X/8,
		   y = TABLE_Y+3;
	gotoxy(x, y);
	printf("->");
	gotoxy(x, y);
	while(input!=13) {
		if(kbhit()) {
			input = getch();
			switch(input) {
				case 27:
					gotoxy(0, TABLE_Y+33);
					return 0;
				case 72:    // key up
					if(y-6>TABLE_Y) {
						*y1=*y1-1;
						printf("  ");
						y-=7;
						gotoxy(x, y);
						printf("%s", x==TABLE_X/8?"->":"<-");
						gotoxy(x, y);
					}
					break;
				case 80:    // key down
					if(y+6<TABLE_Y+TABLE_HIGH) {
						*y1=*y1+1;
						printf("  ");
						y+=7;
						gotoxy(x, y);
						printf("%s", x==TABLE_X/8?"->":"<-");
						gotoxy(x, y);
					}
					break;
				case 77:    // key right
					if(x==TABLE_X/8){
						*x1+=2;
						printf("  ");
						x=TABLE_WIDTH+TABLE_X*2+TABLE_X/8;
						gotoxy(x, y);
						printf("<-");
						gotoxy(x, y);
					}
					break;
				case 75:    // key left
					if(x==TABLE_WIDTH+TABLE_X*2+TABLE_X/8) {
						*x1-=2;
						printf("  ");
						x=TABLE_X/8;	
						gotoxy(x, y);
						printf("->");
						gotoxy(x, y);
					}
					break;
			}
		}
	}
	printf("  ");
	gotoxy(0, TABLE_Y+30);
	char str[256];
	printf("Carta Selezionata: %s                \n", Card_Nominal(Table[*y1][*x1].cards[Table[*y1][*x1].sp-1], str));
	gotoxy(0, TABLE_Y+31);
	printf("Seleziona dove spostare la Carta. Premere S per mandare, se possibile, la carta nel Mazzetto al Centro.\n");
	*x2 = 0; *y2 = 0;
	input = 'a';
	x = TABLE_X/8,
	y = TABLE_Y+3;
	gotoxy(x, y);
	printf("->");
	gotoxy(x, y);
	while(input!=13) {
		if(kbhit()) {
			input = getch();
			switch(input) {
				case 72:    // key up
					if(y-6>TABLE_Y) {
						*y2=*y2-1;
						printf("  ");
						y-=7;
						gotoxy(x, y);
						printf("%s", x==TABLE_X/8?"->":"<-");
						gotoxy(x, y);
					}
					break;
				case 80:    // key down
					if(y+6<TABLE_Y+TABLE_HIGH) {
						*y2=*y2+1;
						printf("  ");
						y+=7;
						gotoxy(x, y);
						printf("%s", x==TABLE_X/8?"->":"<-");
						gotoxy(x, y);
					}
					break;
				case 77:    // key right
					if(x==TABLE_X/8){
						*x2+=2;
						printf("  ");
						x=TABLE_WIDTH+TABLE_X*2+TABLE_X/8;
						gotoxy(x, y);
						printf("<-");
						gotoxy(x, y);
					}
					break;
				case 75:    // key left
					if(x==TABLE_WIDTH+TABLE_X*2+TABLE_X/8) {
						*x2-=2;
						printf("  ");
						x=TABLE_X/8;	
						gotoxy(x, y);
						printf("->");
						gotoxy(x, y);
					}
					break;
				case 115:	// key S
					*x2=1;
					*y2=Table[*y1][*x1].cards[Table[*y1][*x1].sp-1].seed-1;
					input = 13;
					break;
			}
		}
	}
	gotoxy(0, TABLE_Y+33);
	return 1;
}

_Bool Game_Won(struct Stack Table[4][3]) {
	for(size_t i = 0; i<4; ++i)
		if(Table[i][1].sp!=10)
			return 0;
	return 1;
}

_Bool Game_Blocked(struct Stack Table[4][3]) {
	for(size_t y1 = 0; y1<4; ++y1)
		for(size_t x1 = 0; x1<3; x1+=2)
			for(size_t y2 = 0; y2<4; ++y2)
				for(size_t x2 = 0; x2<3; ++x2)
						if(Game_CeckMove(Table, x2, y2, x1, y1))
							if(Game_NullToNull(Table, x2, y2, x1, y1))
								return 1;
	return 0;
}

void Game_TitleScreen(void) {
	printf("SOLITARIO (NAPOLEONE) - by Federico Santucci\n\n");
	printf("COMANDI\n");
	printf("	- Per spostarsi di pila di carte in pila di carte utilizzare le FRECCETTE.\n");
	printf("	- Per selezionare una carta premere INVIO.\n");
	printf("	- Per abbandonare la partita in caso di blocco, premere ESC durante la selezione della prima carta.\n");
	printf("	  (Il Gioco si ferma da solo se non nell'eventualita' in cui ci sia una mossa ripetibile all'infinito.)");
	printf("\nREGOLE\n");
	printf("	- Potete costruite sulle ali del tableau in senso discendente solo per seme diverso.\n");
	printf("	- Si puo' spostare una sola carta alla volta. Quando una fila e' libera, potete collocarvi una qualsiasi carta.\n");
	printf("	- Il solitario riesce se riuscite a spostare tutte le carte sugli assi, in ordine discendente.");
	printf("\n\n\n Premere un pulsante qualsiasi per continuare.");
	getch();
	system("CLS");
}

// WinMain
int main(void) {
	struct Stack Table[4][3];
	Game_TitleScreen();
	Table_Init(TABLE_X, TABLE_Y, Table);
	_Bool flag = Game_Blocked(Table);
	do {
		system("CLS");
		Table_Print(TABLE_X, TABLE_Y, Table);
		size_t x2, y2, x1, y1;
		if(!Game_Movement(&x2, &y2, &x1, &y1, Table)) {
			printf("\nHai abbandonato la Partita.");
			return 0;
		}
		printf("%s", Game_Move(Table, x2, y2, x1, y1)?"Mossa Effettuata.":"Mossa non Valida.");
		flag = Game_Blocked(Table);
		Sleep(ANIMATION_TIME);
	} while(flag);
	if(Game_Won(Table))
		printf("\nHai Vinto!\n");
	else if(!flag)
		printf("\nIl Tavolo e' Bloccato!\n");
	return 0;
}
