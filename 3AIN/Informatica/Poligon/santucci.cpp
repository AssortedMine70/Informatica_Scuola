#include<stdio.h>
#include<graphics.h>
#include<iostream>

int abs(int n) {
	return n>0 ? n : -n;
}

float PointInPath(int x, int y, unsigned n, int points[][2]) {
	unsigned j=n-1, c=0;
	for(unsigned i = 0; i<n; ++i) {
		if(x == points[i][0] && y == points[i][1])
			return 2;
		if((points[i][1]>y) != (points[j][1]>y)) {
			int slope = (x-points[i][0])*(points[j][1]-points[i][1])-(points[j][0]-points[i][0])*(y-points[i][1]);
			if (slope==0)
				return 2;
			if((slope<0) != (points[j][1]<points[i][1]))
				c = !c;
		}
		j = i;
	}
	return c;
}

int evenodd(int x,int y,int poly[][2],int N){
    int j=N-1;
    int c=0;
    for(int i=0;i<N;i++){
        if ((x==poly[i][0]) && (y==poly[i][1])){
            return 2;
        }
        if ((poly[i][1]>y)!=(poly[j][1]>y)){
            int slope = (x-poly[i][0])* (poly[j][1]-poly[i][1])-(poly[j][0]-poly[i][0])*(y-poly[i][1]);
            if(slope==0){
                return 2;
            }
            if ((slope < 0) != (poly[j][1] < poly[i][1])){
                c = !c;
            }
        }
        j=i;
    }
    return c;
} 

void drawPoly(unsigned n, int points[][2], int multiplier) {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:/TC/BGI");
	
	for(unsigned i = 0; i+1<n; ++i)
		line(points[i][0]*multiplier, points[i][1]*multiplier, points[i+1][0]*multiplier, points[i+1][1]*multiplier);
	line(points[0][0]*multiplier, points[0][1]*multiplier, points[n-1][0]*multiplier, points[n-1][1]*multiplier);
	
	getch();
	closegraph();
}

float ShoelaceFormula(unsigned n, int points[][2]) {
	int sum = 0;
	for(unsigned i = 0; i+1<n; ++i)
		sum += points[i][0]*points[i+1][1] - points[i+1][0]*points[i][1];
	sum += points[n-1][0]*points[0][1] - points[0][0]*points[n-1][1];
	return abs(sum)*0.5;
}

float PickTheorem(unsigned n, int points[][2]) {
	unsigned a = 0, p = 0;
	for(unsigned i = 0; i<1024; ++i)
		for(unsigned j = 0; j<1024; ++j)
			if(PointInPath(j, i, n, points) == 2)
				++p;
			else if(PointInPath(j, i, n, points))
				++a;
	return a+(p/2.)-1;
}

int main() {
	int points[20][2];
	
	unsigned n;
	freopen("input.txt", "r", stdin);
		std::cin>>n;
	for(unsigned i=0; i<n; ++i)
		std::cin>>points[i][0]>>points[i][1];
	
	std::cout<<"Area Calcolata con Formula di Gauss: "<<ShoelaceFormula(n, points)<<std::endl;
	std::cout<<"Area Calcolata con il Teorema di Pick: "<<PickTheorem(n, points)<<std::endl;
	
	drawPoly(n, points, 25);
	
	return 0;
}
