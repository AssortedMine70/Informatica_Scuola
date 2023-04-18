#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nPermutazioni(int N) {
	if(N == 1)
		return 1;
	return N*nPermutazioni(N-1);
}

void printMatrice(int **m, int N) {
	for(int i = 0; i < nPermutazioni(N); ++i) {
		for(int j = 0; j < N; ++j) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

int** permutazioni(int N) {
	int p = nPermutazioni(N);
	int** m = (int**) malloc(N * p * sizeof(int));
	for(int i = 0; i < p; ++i) {
		m[i] = malloc(N * sizeof(int));
		for(int j = 0; j < N; ++j)
			m[i][j] = j%N;
	}
	return m;
}

void solve(int t) {
    int N;
    assert(1 == scanf("%d", &N));

    int *X = malloc(N * sizeof(int));
    int *Y = malloc(N * sizeof(int));
    for(int i = 0; i < N; ++i) {
        assert(2 == scanf("%d %d", &X[i], &Y[i]));
    }

    int risposta = 42;

	int** m = permutazioni(N);
	printMatrice(m, N);

    printf("Case #%d: %d\n", t, risposta);
    free(X);
    free(Y);
    free(m);
}

int main() {
    int T, t;

    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &T));

    for (t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
