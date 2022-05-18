#include<stdio.h>

void zero(int n, int m[][n]) {
	for(int i = 0; i<n; ++i)
		for(int j = 0; j<n; ++j)
			m[i][j] = 0;
}

int magicConstant(int n) {
	return (n*(n*n+1))/2;
}

void printMagicSquare(int n, int m[][n]) {
	for(int i = 0; i<n; ++i) {
		for(int j = 0; j<n; ++j)
			printf("%4i", m[i][j]);
		printf("\n");
	}
}

void generateMagicSquare(int n, int m[][n]) {
	zero(n, m);
	if(n%2) {
		int i = 0, j = n/2, x = 0;
		while(++x<=n*n) {
			m[i][j] = x;
			if(++j>n-1) j = 0;
			if(--i<0) i = n-1;
			if(m[i][j]) {
				i = i+2>n-1 ? i+2-n : i+2;
				if(--j<0) j = n-1;
			}
		}
	} else {
		if(n%4) {
			int Quarter[n/2][n/2];
			generateMagicSquare(n/2, Quarter);
			for(int i = 0; i<n/2; ++i)
				for(int j = 0; j<n/2; ++j)
					m[i][j] = Quarter[i][j];
			for(int i = n/2; i<n; ++i)
				for(int j = n/2; j<n; ++j)
					m[i][j] = Quarter[i%(n/2)][j%(n/2)]+(n/2)*(n/2);
			for(int i = 0; i<n/2; ++i)
				for(int j = n/2; j<n; ++j)
					m[i][j] = Quarter[i%(n/2)][j%(n/2)]+(n/2)*(n/2)*2;
			for(int i = n/2; i<n; ++i)
				for(int j = 0; j<n/2; ++j)
					m[i][j] = Quarter[i%(n/2)][j%(n/2)]+(n/2)*(n/2)*3;
			int k = (n/2-1)/2;
			for(int j = 0; j<k; ++j)
				for(int i = 0; i<n/2; ++i) {
					if(i==n/4) {
						int temp = m[i][j+1];
						m[i][j+1] = m[i+n/2][j+1];
						m[i+n/2][j+1] = temp;
					} else {
						int temp = m[i][j];
						m[i][j] = m[i+n/2][j];
						m[i+n/2][j] = temp;
					}
				}
			for(int j = n; j-->n-k+1; ) // n-k+1 = n-(k-1)
				for(int i = 0; i<n/2; ++i) {
					int temp = m[i][j];
					m[i][j] = m[i+n/2][j];
					m[i+n/2][j] = temp;
				}
		} else {
			int x = 0;
			for(int i = 0; i<n; ++i)
				for(int j = 0; j<n; ++j)
					if((i%4!=j%4) && (i%4!=(n-j-1)%4))
						m[i][j] = ++x;
					else
						++x;
			x = 0;
			for(int i = n; i-->0; )
				for(int j = n; j-->0; )
					if((i%4!=j%4) && (i%4!=(n-j-1)%4))
						++x;
					else
						m[i][j] = ++x;
		}
	}
}

int checkMagicSquare(int n, int m[][n]) {
	int c = magicConstant(n), sum = 0;
	// Checks lines
	for(int i = 0; i<n; ++i) {
		sum = 0;
		for(int j = 0; j<n; ++j)
			sum+=m[i][j];
		if(sum!=c) return 0;
	}
	// Checks columns
	for(int j = 0; j<n; ++j) {
		sum = 0;
		for(int i = 0; i<n; ++i)
			sum+=m[i][j];
		if(sum!=c) return 0;
	}
	// Checks diagonals
	sum = 0;
	for(int i = 0; i<n; ++i)
		sum+=m[i][i];
	if(sum!=c) return 0;
	sum = 0;
	for(int i = 0; i<n; ++i)
		sum+=m[i][n-i-1];
	if(sum!=c) return 0;
	return 1;
}

int main() {
	int N;
	printf("Inserire la dimensione del Quadrato Magico: ");
	scanf("%i", &N);
	int Square[N][N];
	printf("Costante Magica: %i\n", magicConstant(N));
	generateMagicSquare(N, Square);
	printMagicSquare(N, Square);
	printf("La Matrice %se' un Quadrato Magico.", checkMagicSquare(N, Square) ? "" : "non ");
	return 0;
}
