#include<stdio.h>
#include<graphics.h>
#include<ctype.h>

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\TC\BGI");
	
	// Draws 20 Pixels of different color.
	for(unsigned i = 0; i<20; ++i)
		putpixel(50+i, 50, i);
	
	// Draws 2 Segments of different color.
	setcolor(RED);
	line(100, 150, 250, 150);
	setcolor(GREEN);
	line(100, 160, 250, 160);
	setcolor(WHITE);
	
	// Draws 2 Rectangles of different color.
	setcolor(RED);
	rectangle(200, 100, 300, 200);
	setcolor(GREEN);
	rectangle(200, 250, 300, 350);
	setcolor(WHITE);
	
	// Draws 5 Circles of different color.
	for (unsigned i = 35; i<=100; i+=15) {
		setcolor(i%16);
		circle(350, 350, i);
	}
	
	getch();
	closegraph();
	return 0;
}
