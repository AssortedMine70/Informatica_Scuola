#include<stdio.h>

void printvec(int vec[], size_t n) {
	for(size_t i = 0; i<n; ++i)
		printf("%3i ", vec[i]);
	printf("\n");
}

void printmat11(int mat[][11], size_t rows, size_t cols) {
	for(size_t i = 0; i<rows; ++i) {
		for(size_t j = 0; j<cols; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
}

void printmat10(int mat[][10], size_t rows, size_t cols) {
	for(size_t i = 0; i<rows; ++i) {
		for(size_t j = 0; j<cols; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
}

void Es1(int vec[], size_t n) {
	for(size_t i = 0; i<n; ++i) {
		if(vec[i+1]>vec[i]) {
			int temp = vec[i];
			vec[i] = vec[n+1];
			vec[n+1] = temp;
		}
	}
}

size_t Es2(int vec[], size_t n) {
	for(size_t i = 0; i<n/2; ++i)
		vec[i] = vec[i+1];
	return n;
}

unsigned Es3(int mat[][11], size_t rows, size_t cols) {
	int sum = 0;
	for(size_t i = 0; i<rows; ++i)
			sum += mat[i][0];
	int maxsum = sum, maxcol = 0;
	for(size_t j = 1; j<cols; ++j) {
		sum = 0;
		for(size_t i = 0; i<rows; ++i)
			sum += mat[i][j];
		if(sum>maxsum) {
			maxcol = j;
			maxsum = sum;
		}
	}
	return maxcol;
}

void Es5(int mat[][10], size_t rows, size_t cols) {
	for(size_t i = 0; i<rows; ++i)
		for(size_t j = 0; j<cols/2; ++j) {
			int temp = mat[i][j];
			mat[i][j] = mat[i][cols-j-1];
			mat[i][cols-j-1] = temp;
		}
}

int main() {
	printf("Esercizio 1:\n");
	int vec1[]={51, 56, 43, 40, 50, 44, 49, 45, 56, 54};
	printvec(vec1, 10);
	printf("Array ordinato in modo Non Crescente:\n");
	Es1(vec1, 10);
	printvec(vec1, 10);
	
	printf("\nEsercizio 2:\n");
	int vec2[]={41, 36, 42, 30, 31, 33, 40, 31, 36, 41, 24};
	printvec(vec2, 10);
	printf("Shift a Sinistra degli elementi della prima meta':\n");
	printvec(vec2, Es2(vec2, 10));
	
	printf("\nEsercizio 3:\n");
	int mat1[][11]={
	{49,32,36,38,29,19,37,11,39,24,43,},
	{28,17,13,38,45,34,35,28,35,28,38,},
	{44,26,35,45,32,30,14,41,47,49,17,},
	{49,36,46,31,35,27,29,16,11,45,20,},
	{45,30,48,35,43,30,25,44,39,31,35,},
	{39,14,10,43,26,39,21,36,18,36,42,},
	{32,47,45,33,25,36,27,14,19,14,29,},
	{29,40,24,16,10,41,43,16,17,19,12,},
	{14,44,39,36,19,45,49,17,19,10,22,},
	{45,28,14,36,46,32,46,18,37,46,24,},
	{28,42,27,44,13,36,25,38,16,43,46,},
	};
	printmat11(mat1, 11, 11);
	printf("Indice della Colonna di Somma Massima: %i\n", Es3(mat1, 11, 11)); // Indice quindi primo 0?
	
	printf("\nEsercizio 5:\n");
	int mat2[][10]={
	{49,45,36,23,27,39,33,43,40,38,},
	{35,19,23,37,21,14,18,30,39,26,},
	{12,43,33,28,30,48,22,30,37,34,},
	{44,23,13,38,38,21,30,48,27,16,},
	{42,47,47,39,43,43,16,35,25,16,},
	{11,16,17,32,31,34,14,46,28,41,},
	{44,40,14,31,31,11,46,21,44,37,},
	{40,34,39,48,32,49,29,41,18,32,},
	{47,27,13,17,28,17,16,17,20,26,},
	{31,33,41,38,10,49,20,33,44,43,},
	};
	printmat10(mat2, 10, 10);
	Es5(mat2, 10, 10);
	printf("Matrice con Colonne invertite di Ordine:\n");
	printmat10(mat2, 10, 10);
}
