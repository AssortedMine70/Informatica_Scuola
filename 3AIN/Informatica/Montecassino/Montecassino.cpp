#include<graphics.h>
#include<stdio.h>
#include<conio.h>

// draws backgraund
void background() {
	// draws and colors the sky
	setfillstyle(SOLID_FILL, LIGHTBLUE);
    floodfill(10, 10, LIGHTBLUE);
    // draws the ground
    setcolor(GREEN);
    line(0, 400, 250, 400);
    // draws the hill
	arc(400, 400, 90, 180, 150);
	line(400, 250, 700, 250);
	// colors the ground and the hill
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(450, 450, GREEN);
    // draws montecassino's abbey
    readimagefile("abbey.bmp", 450, 150, 650, 300);
}

int main(void) {
    int gdriver = DETECT, gmode;
    
    // init graphics drivers
    initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
    
    background();
    
	getch();
	closegraph();
    return 0;
}
