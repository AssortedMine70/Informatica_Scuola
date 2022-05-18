#include<stdio.h>
#include<graphics.h>

void drawPoly(unsigned n, int points[], int multiplier) {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\TC\BGI");
	
	for(unsigned i = 0; i<n+n; ++i)
		points[i] *= multiplier;
	drawpoly(n, points);
	line(points[0], points[1], points[n+n-2], points[n+n-1]);
	for(size_t i = 0; i<n; ++i)
		points[i] /= multiplier;
		
	getch();
	closegraph();
}

int main() {
	int points[20];
	
	freopen("input.txt", "r", stdin);
	unsigned n;
	scanf("%u", &n);
	for(unsigned i=0; i<n+n; ++i)
		scanf("%i", &points[i]);
	
	drawPoly(n, points, 25);
}
