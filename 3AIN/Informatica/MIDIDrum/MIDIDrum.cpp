#include <stdio.h>
#include <conio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>	/* needs to be added manually in Dev-C++ folders (headers are included in the ./_NEED TO INSTALL/Graphics Header Files.zip)*/
#include <mmsystem.h>	/* multimedia functions (such as MIDI) for Windows */
/* ATTENTION 
	add to the linker: -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm.
	compiler must be in 32-bit.
*/

// Global Variables
HMIDIOUT device; 										// MIDI device interface for sending MIDI output. needs to be global becasue is used across functions.
bool hithatpedal = false;								// pedal pression. needs to be global vecause is used across functions.
int width = getmaxwidth(), height = getmaxheight(); 	// screen resolution. needs to be global because is used across functions.
int notetime = 500;										// the time in milliseconds that must pass between notes in the music sheet mode. needs to be global because is used across functions.
bool metronome = true;									// metronome in music sheet mode. needs to be global because is used across functions.
size_t tick = 0;										// tells which Unit is playing. needs to be global because is used across functions.
size_t sheetlen = 0;									// tells how much Units are in the Sheet. needs to be global because is used across functions.

#define SAVESDIR "./saves" 		// indicates where the saves are located in the PC.
#define SPEEDSENSIBILITY 50 	// indicates how mutch the notetime changes at the press of the speed-changing buttons in music sheet mode.
#define MAXUNITS 20				// indicates the max number of Units that can have a Sheet.

// MISCELLANEUS FUNCTIONS
void gotoxy(short x, short y) {
	COORD V={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), V);
}

void printcolor(const char *str, unsigned Text, unsigned Background) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	SetConsoleTextAttribute(hStdOut, (Text & 0xF) | ((Background & 0xF)<<4));
	printf("%s", str);
	SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
}

void showConsoleCursor(bool Show) {
	int Size = 25;
	CONSOLE_CURSOR_INFO CurInfo; 	
	if (Size <= 0) Size = 1;
	if (Size > 100) Size = 100;
	CurInfo.dwSize = Size; 
	CurInfo.bVisible = Show;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void fullscreen() {
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

//Select Function (Array Lenght, Options Array[][256], Style (TRUE = >>, FALSE = Inverted Colors), CLS (if TRUE clears the Terminal after the selection), escExit (Exit or not the program at the pressing of esc button))
size_t select(int n, char Options[][256], bool style = false, bool CLS  = true, bool escExit  = false) {
	system("CLS");
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
		input = _getch();
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

// SANDBOX PART

// handles the mouseclick
void sandboxClickHandler(int x, int y) {
		// variable which is both an integer and an array of characters, used as MIDI message:
		union { unsigned long word; unsigned char data[4]; } message;
		   message.data[0] = 0x99;  // command byte of the MIDI message, for example: 0x90		MIDI note-on message (requires to data bytes)
		   message.data[1] = 0;     // first data byte of the MIDI message, for example: 60		MIDI note-on message: Key number
		   message.data[2] = 100;   // second data byte of the MIDI message, for example 100	MIDI note-on message: Key velocity (100 = loud)
		   message.data[3] = 0;     // not used for any MIDI messages, so set to 0				Unused parameter
	
	if(x > width*0.22 && y > height*0.15 && x < width*0.41 && y < height*0.22) // Crash
		message.data[1] = 49;
	else if(x > width*0.12 && y > height*0.32 && x < width*0.29 && y < height*0.38) // Hit-Hat / Closed Hit-Hat
		if(hithatpedal)
			message.data[1] = 44; // Closed Hit-Hat
		else
			message.data[1] = 46; // Hit-Hat
	else if(x > width*0.62 && y > height*0.27 && x < width*0.85 && y < height*0.36) // Ride
		message.data[1] = 51;
	else if(x > width*0.36 && y > height*0.33 && x < width*0.48 && y < height*0.41) // Tom 1
		message.data[1] = 47;
	else if(x > width*0.49 && y > height*0.33 && x < width*0.63 && y < height*0.42) // Tom 2
		message.data[1] = 48;
	else if(x > width*0.27 && y > height*0.44 && x < width*0.44 && y < height*0.52) // Snare
		message.data[1] = 38;
	else if(x > width*0.57 && y > height*0.45 && x < width*0.73 && y < height*0.51) // Floor Tom
		message.data[1] = 41;
	else if(x > width*0.43 && y > height*0.65 && x < width*0.51 && y < height*0.87) // Bassdrum
		message.data[1] = 36;
	
	if(message.data[1]!=0) {
		midiOutShortMsg(device, message.word);
	}
}

// sandbox mode
bool sandbox(void) {
	// setting window and background
	initwindow(width, height, "Drum Sandbox");
	char img[20] = "assets/drum.jpg";
	readimagefile(img, 0, 0, width, height);
	setcolor(BLACK);
	setbkcolor(WHITE);
	outtext((char*)"Premi H per iniziare a premere il pedale dell'Hit-Hat, ripremere H per smettere. Si puo' anche premere spazio per usare la Grancassa. Premere ESC per uscire.");
	outtextxy(0, textheight((char*)" "), (char*)"Cliccare sul componente effettivo della batteria per suonarlo.");
	// opens MIDI interface
	midiOutOpen(&device, 0, 0, 0, CALLBACK_NULL);
	// listening for left mouse clicks
	char input = 0;
	while(input!=27) { // ESC = 27
		registermousehandler(WM_LBUTTONDOWN, sandboxClickHandler);
		if(kbhit()>0) {
			input = getch();
			if(input==104) { // H = 104
				hithatpedal=!hithatpedal;
			} else if(input==32) { // SPACE = 32
				// play bassdrum
				// variable which is both an integer and an array of characters, used as MIDI message:
				union { unsigned long word; unsigned char data[4]; } message;
				   message.data[0] = 0x99;	// command byte of the MIDI message, for example: 0x90		MIDI note-on message (requires to data bytes)
				   message.data[1] = 36;	// first data byte of the MIDI message, for example: 60		MIDI note-on message: Key number
				   message.data[2] = 100;	// second data byte of the MIDI message, for example 100	MIDI note-on message: Key velocity (100 = loud)
				   message.data[3] = 0;		// not used for any MIDI messages, so set to 0				Unused parameter
				midiOutShortMsg(device, message.word);
			}
		}
	}
	// turns any MIDI notes currently playing
	midiOutReset(device);
	// removes any data in MIDI device and close the MIDI output port
	midiOutClose(device);
	// closes BGI window
	closegraph();
	return 0;
}

// MUSIC SHEET PART

// represents a column in the music sheet
typedef struct {
	bool part[8]; // Crash, Hit-Hat, Closed Hit-Hat, Ride, Tom 1, Tom 2, Floor Tom, Bassdrum
} Unit;

// prints on graphics the music sheet
void drawSheet() {
	unsigned	xoffset = width/5, yoffset = height/5,
				block = (width-(width/5)*2)/MAXUNITS;
	// erases the previous sheet
	setcolor(BLACK);
	for(size_t i = 1; i<=MAXUNITS; ++i)
		for(size_t j = 0; j<8; ++j)
			rectangle(xoffset, yoffset+block*j, xoffset+block*i, yoffset+block+block*j);
	// draws squares corresponding to the sheet notes
	setcolor(WHITE);
	for(size_t i = 1; i<=sheetlen; ++i)
		for(size_t j = 0; j<8; ++j)
			rectangle(xoffset, yoffset+block*j, xoffset+block*i, yoffset+block+block*j);
	// draws the new tick
	setcolor(RED);
	rectangle(xoffset+block*tick, yoffset, xoffset+block+block*tick, yoffset+block*8);
}

// for initializing the graphical music sheet
void readSheet(Unit Sheet[]) {
	unsigned	xoffset = width/5, yoffset = height/5,
				block = (width-(width/5)*2)/MAXUNITS;
	for(size_t col = 0; col<sheetlen; ++col)
		for(size_t row = 0; row<sizeof(Unit); ++row) {
			if(Sheet[col].part[row]==true) {
				int points[8];
				points[0] = xoffset+block*col+1;
				points[1] = yoffset+block*row+1;
				points[2] = points[0]+block-2;
				points[3] = points[1];
				points[4] = points[2];
				points[5] = points[1]+block-2;
				points[6] = points[0];
				points[7] = points[5];
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				fillpoly(4, points);
			}
	}
}

// scans the tick column
void scanTick() {
	unsigned	xoffset = width/5, yoffset = height/5,
				block = (width-(width/5)*2)/MAXUNITS;
	for(size_t i = 0; i<sizeof(Unit); ++i)
		if(getpixel(xoffset+block*tick+1, yoffset+block*i+1)==YELLOW) {
			// play bassdrum
			// variable which is both an integer and an array of characters, used as MIDI message:
			union { unsigned long word; unsigned char data[4]; } message;
			   message.data[0] = 0x99;	// command byte of the MIDI message, for example: 0x90		MIDI note-on message (requires to data bytes)
			   //message.data[1] = 36;	// first data byte of the MIDI message, for example: 60		MIDI note-on message: Key number
			   message.data[2] = 100;	// second data byte of the MIDI message, for example 100	MIDI note-on message: Key velocity (100 = loud)
			   message.data[3] = 0;		// not used for any MIDI messages, so set to 0				Unused parameter
			switch(i) {
				case 0: {
					message.data[1] = 49;
					break;
				}
				case 1: {
					message.data[1] = 44;
					break;
				}
				case 2: {
					message.data[1] = 46;
					break;
				}
				case 3: {
					message.data[1] = 51;
					break;
				}
				case 4: {
					message.data[1] = 47;
					break;
				}
				case 5: {
					message.data[1] = 48;
					break;
				}
				case 6: {
					message.data[1] = 41;
					break;
				}
				case 7: {
					message.data[1] = 36;
					break;
				}
				
			}
			// sends out the message
			midiOutShortMsg(device, message.word);
		}
	printf("\n");
}

// handles the mouseclick
void sheetClickHandler(int x, int y) {
	int	xoffset = width/5, yoffset = height/5,
		block = (width-(width/5)*2)/MAXUNITS;
	if(y>yoffset && y<yoffset+block*8 && x>xoffset && x<xoffset+(int)sheetlen*block) {
		size_t row = (x-xoffset)/block;
		size_t col = (y-yoffset)/block;
		int points[8];
		points[0] = xoffset+block*row+1;
		points[1] = yoffset+block*col+1;
		points[2] = points[0]+block-2;
		points[3] = points[1];
		points[4] = points[2];
		points[5] = points[1]+block-2;
		points[6] = points[0];
		points[7] = points[5];
		if(getpixel(points[0], points[1])!=YELLOW) {
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL, YELLOW);
		} else {
			setcolor(BLACK);
			setfillstyle(SOLID_FILL, BLACK);
		}
		fillpoly(4, points);
	}
}

// updates the Sheet variable in case of saving
void updateSheet(Unit Sheet[]) {
	unsigned	xoffset = width/5, yoffset = height/5,
				block = (width-(width/5)*2)/MAXUNITS;
	for(size_t i = 0; i<sheetlen; ++i)
		for(size_t j = 0; j<sizeof(Unit); ++j)
			Sheet[i].part[j] = getpixel(xoffset+block*i+1, yoffset+block*j+1)==YELLOW;
}

void writeNames() {
	unsigned	xoffset = width/10, yoffset = height/5,
				block = (width-(width/5)*2)/MAXUNITS;
	setcolor(WHITE);
	for(size_t i = 0; i<sizeof(Unit); ++i)
			switch(i) {
				case 0: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Crash");
					break;
				}
				case 1: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Closed HIt-Hat");
					break;
				}
				case 2: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"HIt-Hat");
					break;
				}
				case 3: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Ride");
					break;
				}
				case 4: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Tom 1");
					break;
				}
				case 5: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Tom 2");
					break;
				}
				case 6: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Floor Tom");
					break;
				}
				case 7: {
					outtextxy(xoffset+block*tick+1, yoffset+block*i+block/2, (char*)"Bassdrum");
					break;
				}
				
			}
}

// music sheet editing mode
bool musicSheet() {
	FILE *fp = NULL;
	char str[][256] = {
		"Nuovo",
		"Carica",
		"Elimina",
		"Torna al Menu principale",
	};
	showConsoleCursor(false);
	// opens SAVESDIR directory and stores the file names in files variable, or creates SAVESDIR folder if unexisting
	DIR *d = opendir(SAVESDIR);
	struct dirent *dir;
	char files[100][256];
	size_t i = 0;
	if (d!=NULL) {
		while((dir = readdir(d))!=NULL)
			if(strstr(dir->d_name, ".mididrum")!=NULL)
     			strcpy(files[i++], dir->d_name);
	} else {
		int check = mkdir(SAVESDIR);
    	// check if directory has been created or not
    	if (!check) {
       		printf("La cartella dei salvataggi non esisteva. E' stata quindi creata.\n[Premere un tasto per continuare]\n");
       		_getch();
		}
		else {
       		printf("Impossibile creare la cartella dei salvataggi. Inserire un percorso valido nelle impostazioni o liberare spazio su disco.\n[Premere un tasto per continuare]\n");
       		_getch();
       		return 1;
		}
	}
	// creates, opens or deleate a files untill it obtains a valid file pointer
	while(fp==NULL) {
		switch(select(4, str)) {
			case 0: {
				char newfilename[256];
				bool notexists = true;
				printf("Nome del file: ");
				scanf(" ");
				fgets(newfilename, sizeof(newfilename), stdin);
				while (newfilename[strlen(newfilename)-1]=='\n')
					newfilename[strlen(newfilename)-1] = '\0';
				strcat(newfilename, ".mididrum");
				for(size_t j = 0; j<i; ++j)
					if(strcmp(newfilename, files[j])==0)
						notexists = false;
				if(notexists) {
					strcpy(files[i++], newfilename);
					char filedir[256];
					strcpy(filedir, SAVESDIR);
					strcat(filedir, "/");
					strcat(filedir, newfilename);
					fp = fopen(filedir, "w+b");
					if(fp!=NULL) {
						printf("File creato correttamente.");
						bool null[8] = {0};
						fwrite(&null, sizeof(null), 1, fp);
						rewind(fp);
					} else
						perror("Errore durante la creazione del file");
				} else
					printf("Esiste gia' un file con questo nome.");
				printf("\n[Premere un tasto per continuare]\n");
				_getch();
				break;
			}
			case 1: {
				// selects between existing files
				if(i>0) {
					char filedir[256];
					strcpy(filedir, SAVESDIR);
					strcat(filedir, "/");
					strcat(filedir, files[select(i, files)]);
					printf("Apertura di %s...\n", filedir);
					fp = fopen(filedir, "r+b");
					if(fp!=NULL)
						printf("File aperto correttamente.");
					else {
						perror("Errore durante l'apertura");
					}
					printf("\n[Premere un tasto per continuare]\n");
					_getch();
				} else {
					printf("Non sono presenti file nella cartella.\n[Premere un tasto per tornare al Menu]\n");
					_getch();
				}
				break;
			}
			case 2: {
				if(i>0) {
					char filedir[256];
					strcpy(filedir, SAVESDIR);
					strcat(filedir, "/");
					strcat(filedir, files[select(i, files)]);
					printf("Rimozione di %s...\n", filedir);
					remove(filedir);
					for(size_t j = 0; j<i; ++j)
						*files[j] = '\0';
					i = 0;
					rewinddir(d);
					while((dir = readdir(d))!=NULL)
						if(strstr(dir->d_name, ".mididrum")!=NULL)
     						strcpy(files[i++], dir->d_name);
					printf("File rimosso.\n[Premere un tasto per continuare]\n");
					_getch();
				} else {
					printf("Non sono presenti file nella cartella.\n[Premere un tasto per tornare al Menu]\n");
					_getch();
				}
				break;
			}
			case 3: {
				if(fp!=NULL)
					fclose(fp);
				return 0;
			}
		}
	}
	closedir(d);
	//reads .mididrum file
	Unit Sheet[MAXUNITS];
	sheetlen = 0;
	fseek(fp, 0, SEEK_CUR); // change mode to READ
	while(fread(&Sheet[sheetlen], sizeof(Unit), 1, fp)==1)
		++sheetlen;
	rewind(fp);
	// opens MIDI interface
	midiOutOpen(&device, 0, 0, 0, CALLBACK_NULL);
	// opens the graphic window and inits it
	initwindow(width, height, "Drum Music Sheet");
	drawSheet();
	writeNames(); // writes drum pieces names
	readSheet(Sheet);
	// prints music sheet edit commands
	setcolor(WHITE);
	outtext((char*)"Spazio per avviare la riproduzione, Esc per uscire dal programma. Aggiungi o togli note cliccando sullo spartito.");
	outtextxy(0, textheight((char*)" "), (char*)"Premi M per attivare o disattivare il metronomo.");
	outtextxy(0, textheight((char*)" ")*2, (char*)"Per cambiare la velocita' di riproduzione: + per aumentare, - per diminuire.");
	outtextxy(0, textheight((char*)" ")*3, (char*)"Per cambiare la lunghezza dello spartito: freccia destra per diminuire, freccia sinistra per aumentare.");
	outtextxy(0, textheight((char*)" ")*4, (char*)"Premi spazio per far suonare lo spartito, ripremilo per fermare la riproduzione.");
	char input = 0;
	bool play = false;
	while(input!=27) { // ESC = 27
	    // looping till required time between notes is not achieved
		clock_t start_time = clock();
	    while (clock() < start_time+notetime && input!=27) {
		registermousehandler(WM_LBUTTONDOWN, sheetClickHandler);
		if(kbhit()>0)
			input = getch();
			if(input==109) {// M = 109
				metronome=!metronome;
				input = 0;
			} else if(input==32) {
				play=!play;
				tick = 0;
				input = 0;
			} else if(input==43 && notetime-SPEEDSENSIBILITY>0) { // ARROW UP = 72
				notetime-=SPEEDSENSIBILITY;
				input = 0;
			} else if(input==45) { // ARROW DOWN = 80
				notetime+=SPEEDSENSIBILITY;
				input = 0;
			} else if(input==75 && sheetlen>1) {
				--sheetlen;
				input = 0;
				// uptates graphics for sheet lenght
				drawSheet();
			} else if(input==77 && sheetlen<20) {
				++sheetlen;
				input = 0;
				// uptates graphics for sheet lenght
				drawSheet();
			}
		}
		if(metronome && play) { // cowbell is used as metronome
			union { unsigned long word; unsigned char data[4]; } message;
				   message.data[0] = 0x99;	// command byte of the MIDI message, for example: 0x90		MIDI note-on message (requires to data bytes)
				   message.data[1] = 56;	// first data byte of the MIDI message, for example: 60		MIDI note-on message: Key number
				   message.data[2] = 100;	// second data byte of the MIDI message, for example 100	MIDI note-on message: Key velocity (100 = loud)
				   message.data[3] = 0;		// not used for any MIDI messages, so set to 0				Unused parameter
			midiOutShortMsg(device, message.word);
		}

		// updates graphics for tick
		drawSheet();
		// plays sounds
		if(play) {
			// plays the Unit number tick
			scanTick();
			++tick;
			tick%=sheetlen;
		}
	}
	// scans the music sheet before closing the BGI window
	updateSheet(Sheet);
	// closes BGI window
	closegraph();
	// eventually saving the file
	char save[][256] = {
		"Salva",
		"Non Salvare",
	};
	switch(select(2, save)) {
		case 0: {
			rewind(fp);
			fseek(fp, 0, SEEK_CUR); // change mode to WRITE
			fwrite(Sheet, sizeof(Unit), sheetlen, fp);
			SetEndOfFile(fp); // to troncate the file
			printf("I progressi sono stati salvati.\n[Premere un tasto per continuare]\n");
			_getch();
			break;
		}
		case 1: {
			printf("I progressi non sono stati salvati.\n[Premere un tasto per continuare]\n");
			_getch();
			break;
		}
	}
	// turns any MIDI notes currently playing
	midiOutReset(device);
	// removes any data in MIDI device and close the MIDI output port
	midiOutClose(device);
	// closes the file
	fclose(fp);
	return 0;
}

int main(void) {
	printf("Batteria Elettronica MIDI - Federico Santucci, 2022\n\n");
	printf("Questo programma permette di suonare la batteria tramite protocollo MIDI in due modi diversi:\n");
	printf("	- Sandbox,  che permette facilmente di premere con il mouse sui vari componenti della batteria per suonarli;\n");
	printf("	- Spartito, che permette di creare semplici \"spartiti\" e di gestirne il salvataggio.\n\n");
	printf("I menù sono facilmente navigabili con i pulsanti FRECCIA SU e FRECCIA GIU', mentre comandi più specifici verranno\n");
	printf("direttamente illustrati nelle relative modalità.\n\nPremere un qualsiasi pulsante per accedere al menù' di selezione della modalita'...");
	_getch();
	showConsoleCursor(false);
	char cases[][256] = {
		"Sandbox",
		"Spartito",
		"Esci",
	};
	while(1) {
		switch(select(3, cases)) {
			case 0: {
				if(sandbox())
					perror("Errore, non è stato possibile aprire la sandbox.\n");
				break;
			}
			case 1: {
				if(musicSheet())
					perror("Errore, non è stato possibile aprire la gestione a spartito.\n");
				break;
			}
			case 2: {
				return 0;
			}
		}
	}
}
