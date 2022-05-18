#include<stdio.h>
#define N 10

//misc
int Abs(int x) { // Calcola il valore Assoluto di un numero Intero.
	return x>=0 ? x : -x;
}

void print(int mat[][N], size_t l) { // Stampa la matrice quadrata di lato l.
	for(size_t i = 0; i < l; ++i) {
		for(size_t j = 0; j < l; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
}

// Matrixes
void BullseyeMatrix(int mat[][N], unsigned n) { // Stampa la Bullseye Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = (Abs(((n+1)/2)-j-1)+1 > Abs(((n+1)/2)-i-1)+1) ? Abs(((n+1)/2)-j-1)+1 : Abs(((n+1)/2)-i-1)+1;
}

void SpyralMatrix(int mat[][N], unsigned n) { // Stampa la Spyral Matrix in funzione della sua dimensione. //TODO
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j);
			
}

void TranslatedMatrix(int mat[][N], unsigned n) { // Stampa la Translated Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = i+j+1;
}

void DiagonalMatrix(int mat[][N], unsigned n) { // Stampa la Diagonal Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = Abs(i-j)+1;
}

void ZigzagMatrix(int mat[][N], unsigned n) { // Stampa la Zigzag Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = i%2 ? (N*i)+(N-j) : (N*i)+j+1;
}

void AztecMatrix(int mat[][N], unsigned n) { // Stampa la Aztec Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = (((j+1)%2 ? j+1 : j) < ((i+1)%2 ? i+1 : i) ? ((j+1)%2 ? j+1 : j) : ((i+1)%2 ? i+1 : i)) < (((i+1)%2 ? n-i-1 : n-i) < ((j+1)%2 ? n-j-1 : n-j) ? ((i+1)%2 ? n-i-1 : n-i) : ((j+1)%2 ? n-j-1 : n-j)) ? (((j+1)%2 ? j+1 : j) < ((i+1)%2 ? i+1 : i) ? ((j+1)%2 ? j+1 : j) : ((i+1)%2 ? i+1 : i)) : (((i+1)%2 ? n-i-1 : n-i) < ((j+1)%2 ? n-j-1 : n-j) ? ((i+1)%2 ? n-i-1 : n-i) : ((j+1)%2 ? n-j-1 : n-j));
}

void DoublestepMatrix(int mat[][N], unsigned n) { // Stampa la Doublestep Matrix in funzione della sua dimensione.
	for(size_t i = 0; i < n; ++i)
		for(size_t j = 0; j < n; ++j)
			mat[i][j] = (j < i ? j+1 : i+1) < (j > i ? n-j : n-i) ? (j < i ? j+1 : i+1) : (j > i ? n-j : n-i);
}

// Main
int main() {
	int mat[N][N];
	printf("Bullseye Matrix:\n");
	BullseyeMatrix(mat, N%2 ? N : N-1);
	print(mat, N%2 ? N : N-1);
	printf("\nSpyral Matrix:\n");
	SpyralMatrix(mat, N);
	print(mat, N);
	printf("\nTranslated Matrix:\n");
	TranslatedMatrix(mat, N);
	print(mat, N);
	printf("\nDiagonal Matrix:\n");
	DiagonalMatrix(mat, N);
	print(mat, N);
	printf("\nZigzag Matrix:\n");
	ZigzagMatrix(mat, N);
	print(mat, N);
	printf("\nAztec Matrix:\n");
	AztecMatrix(mat, N%2 ? N-1 : N);
	print(mat, N%2 ? N-1 : N);
	printf("\nDoublestep Matrix:\n");
	DoublestepMatrix(mat, N%2 ? N-1 : N);
	print(mat, N%2 ? N-1 : N);
	
	return 0;
}
