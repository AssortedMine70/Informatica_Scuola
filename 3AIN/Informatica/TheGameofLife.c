#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
#include <unistd.h>

void gotoxy(int x,int y){
	COORD V={x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), V);
}

void init(int matrix[30][40]) {
	for(int i = 0; i<30; ++i)
		for(int j = 0; j<40; ++j)
			matrix[i][j] = 0;
}

void print(int matrix[30][40]) {
	for(int i = 0; i<30; ++i) {
		for(int j = 0; j<40; ++j)
			printf("%s", matrix[i][j] ? "X" : " ");
		printf("\n");
	}
}

void setup(int matrix[30][40]) {
	int x = 0, y = 0, input = 0, mode = 1;
	do{
		gotoxy(x, y);
		if(kbhit()) {
			switch(getch()) {
				case 32:
					mode = 0;
					break;
			case 72:
				if(y-1>0)
						gotoxy(x, y--);
					break;
			case 80:
				if(y+1<40)
						gotoxy(x, y++);
					break;
			case 75:
					if(x-2>0)
						gotoxy(x-=2, y);
					break;
			case 77:
					if(x+2<30)
						gotoxy(x+=2, y);
					break;
			case 13:
				if(matrix[x][y]) {
					matrix[x][y] = 0;
					printf(" ");
				} else {
					matrix[x][y] = 1;
					printf("X");
				}
				break;
			}
		}
	} while(mode);
}

void update(int matrix[30][40]) {
	for(int i = 0; i<30; ++i)
		for(int j = 0; j<40; ++j) {
			int neighbours = matrix[i+1][j] + matrix[i-1][j] + matrix[i][j+1] + matrix[i][j-1];
			if (matrix[i][j]) {
				if(matrix[i][j] && neighbours < 2)
					matrix[i][j] = 0;
				else if(matrix[i][j] && neighbours > 3)
					matrix[i][j] = 0;
			} else if(neighbours == 3) 
				matrix[i][j] = 1;
		}
}

int main() {
	int M[30][40];
	init(M);
	setup(M);
	print(M);
//	do{
//		system("CLS");
//		update(M);
//		sleep(3);
//		print(M);
//	}while(!kbhit());
	return 0;
}
