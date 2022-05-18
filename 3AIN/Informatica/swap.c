#include<stdio.h>

void printmatrix(int mat[][5], size_t rows, size_t cols) {
	for(size_t i = 0; i<rows; ++i){
		for(size_t j = 0; j<cols; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

void swapdiagonal(int mat[][5], size_t rows, size_t cols) {
	for(size_t i = 0; i<rows; ++i) {
		int temp = mat[i][i];
		mat[i][i] = mat[i][cols-i-1];
		mat[i][cols-i-1] = temp;
	}
}

int main() {
	int mat[][5] = {
	{1, 0, 0, 0, 0,},
	{0, 1, 0, 0, 0,},
	{0, 0, 1, 0, 0,},
	{0, 0, 0, 1, 0,},
	{0, 0, 0, 0, 1,},	
	};
	
	printmatrix(mat, 5, 5);
	swapdiagonal(mat, 5, 5);
	printmatrix(mat, 5, 5);
}
