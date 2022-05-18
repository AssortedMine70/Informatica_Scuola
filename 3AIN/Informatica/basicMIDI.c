#include <stdio.h>
#include <conio.h>
#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */
#include <stdbool.h>
#include <unistd.h>    /* adds sleep funcion */
#define SHIFTER 2
#define NOTETIME 2

void gotoxy(int x,int y){
COORD V={x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), V);
}

int main(int argc, char** argv) {
	int ckey;           // storage for the current keyboard key being pressed
	int notestate = 0;  // keeping track of when the note is on or off
	int velocity = 100; // MIDI note velocity parameter value
	int midiport;       // select which MIDI output port to open
	int flag;           // monitor the status of returning functions
	HMIDIOUT device;    // MIDI device interface for sending MIDI output

	MIDIINCAPS inCaps;
	printf("MIDI_IN\n");
	for (unsigned mp=0; mp<midiInGetNumDevs(); ++mp) {
		midiInGetDevCaps(mp, &inCaps, sizeof(inCaps));
		printf("\t%s\n", inCaps.szPname);
	}

	MIDIOUTCAPS outCaps;
	printf("MIDI_OUT\n");
	for (unsigned mp=0; mp<midiOutGetNumDevs(); ++mp) {
		midiOutGetDevCaps(mp, &outCaps, sizeof(outCaps));
		printf("\t%s\n", outCaps.szPname);
	}

	// variable which is both an integer and an array of characters:
	union { unsigned long word; unsigned char data[4]; } message;
	// message.data[0] = command byte of the MIDI message, for example: 0x90
	// message.data[1] = first data byte of the MIDI message, for example: 60
	// message.data[2] = second data byte of the MIDI message, for example 100
	// message.data[3] = not used for any MIDI messages, so set to 0
	   message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
	// message.data[1] = 60;    // MIDI note-on message: Key number (60 = middle C)
	   message.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	// message.data[3] = 0;     // Unused parameter

	printf("MIDI output port set to %d.\n", 0);

	// Open the MIDI output port
	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
		return 1;
	}

	// Prints Pentagram of b beats and l lines
	int b = 5, l = 5;
	for(int i = 0; i < l; i++)
	{
		printf("|");
		for(int j = 0; j < b; j++)
			printf(" / / / |");
		printf("\n");
	}

	// Declare Matrix in function of Pentagram Dimensions
	int Notes[l][b*4];
	for(unsigned i = 0; i < l; i++)
		for(unsigned j = 0; j < b*4; j++)
			Notes[i][j] = 0;
	// Pentagram Editing
	
	// Pentagram Origin Coordinates
	int xs = 1, ys = 5;
	// Pentagram Finish Coordinates
	int xf = xs + 8*b-2, yf = ys + l-1;
	// Setting Coordinates Variables to Starting Position
	int x = xs, y = ys;
	bool mode = true;
	while(mode)
	{
		gotoxy(x, y);
		if(kbhit())
		{
			int input = getch();
			switch(input)
			{
				case 32:
					mode = false;
					break;
				case 72:
					if(y-1>=ys)
						gotoxy(x, y--);
					break;
				case 80:
					if(y+1<=yf)
						gotoxy(x, y++);
					break;
				case 75:
					if(x-2>=xs)
						gotoxy(x-=2, y);
					break;
				case 77:
					if(x+2<=xf)
						gotoxy(x+=2, y);
					break;
				case 13:
					if(Notes[y-ys][(x-xs)/2])
					{
						Notes[y-ys][(x-xs)/2] = 0;
						printf(" ");
					}
					else
					{
						Notes[y-ys][(x-xs)/2] = 1;
						printf("X");
					}
					break;
			}	
			gotoxy(10, 10);
			printf("                                                  ");
			gotoxy(10, 10);
			printf("%i [%i %i] [%i %i] [%i %i] %i", input, x, y,x-xs, y-ys, (x-xs)/2, y-ys, Notes[y-ys][(x-xs)/2]);
		}
	}
	
	gotoxy(0, 13);
	for(unsigned i = 0; i < l; i++)
	{
		for(unsigned j = 0; j < b*4; j++)
			printf("%i ", Notes[i][j]);
		printf("\n");
	}
	
	for(;;)
	{
		for(unsigned j = 0; j < b*4; j++)
		{
			for(unsigned i = 0; i < l; i++)
			{
				if(Notes[i][j])
				{
					message.data[1] = 108 - 7*(SHIFTER) - i;
					flag = midiOutShortMsg(device, message.word);
				}
			}
			
			sleep(NOTETIME);
		}
	}

	// turn any MIDI notes currently playing:
	midiOutReset(device);

	// Remove any data in MIDI device and close the MIDI Output port
	midiOutClose(device);

	return 0;
}
