#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

void zero(unsigned matrix[7][5]) {
	for(size_t i = 0; i<7; ++i)
		for(size_t j = 0; j<5; ++j)
			matrix[i][j] = 0;
}

void print(unsigned matrix[7][5]) {
	for(size_t i = 0; i<7; ++i) {
		for(size_t j = 0; j<5; ++j)
			printf("%3i ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

bool check(int i, int j, unsigned matrix[7][5]) {
	return i >= 0 && j >= 0 && i <= 7 && j <= 5 && matrix[i][j] == 0 ? true : false;
}

bool check_impossibility(int i, int j, unsigned matrix[7][5]) {
	if(check(i+3, j, matrix) || check(i-3, j, matrix) || check(i, j+3, matrix) || check(i, j-3, matrix) || check(i+2, j+2, matrix) || check(i-2, j-2, matrix) || check(i+2, j-2, matrix) || check(i-2, j+2, matrix))
		return false;
	return true;
}

int main() {
	unsigned matrix[7][5], x;
	do {
		zero(matrix);
		int i = 3, j = 2;
		matrix[i][j] = 1;
		for(x = 2; i<=35; ++x) {
			int last_i = i;
			int last_j = j;
			do {
				switch(rand()%8) {
					case 0:
						i+=3;
						break;
					case 1:
						i-=3;
						break;
					case 2:
						j+=3;
						break;
					case 3:
						j-=3;
						break;
					case 4:
						i+=2;
						j+=2;
						break;
					case 5:
						i+=2;
						j-=2;
						break;
					case 6:
						i-=2;
						j+=2;
						break;
					case 7:
						i-=2;
						j-=2;
						break;
				}
				if(!check(i, j, matrix)) {
					i = last_i;
					j = last_j;
				}
			}while(!check(i, j, matrix));
			matrix[i][j] = x;
			if(check_impossibility(i, j, matrix))
				break;
		}
		print(matrix);
	} while(x<35);
	print(matrix);
	return 0;
}
