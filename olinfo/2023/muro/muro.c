#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int *a, int N) {
    for(int i = 0; i < N-1; ++i)
        for(int j = 0; j < N-i-1; ++j)
            if(a[j] > a[j+1]) {
			    int t = a[j];
			    a[j] = a[j+1];
			    a[j+1] = t;
			}
}

void print(int *a, int N) {
	for(int i = 0;  i < N; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

int count(int *a, int N) {
	int count = 0, i = 0;
	bubbleSort(a, N);
    while(a[i] == -1)
    	i++;
	for(; i < N; ++i) {
		while(i < N-1 && a[i] == a[i+1])
            i++;
        count++;
    }
    return count;
}

void solve(int t) {
    int N, Q;
    assert(2 == scanf("%d%d", &N, &Q));
	int* wall = malloc(N * sizeof(int));
	memset(wall, -1, N * sizeof(int));

    int* L = malloc(Q * sizeof(int));
    for (int i = 0; i < Q; i++) {
        assert(1 == scanf("%d", &L[i]));
    }

	//print(L, Q);
	for(int i = 0; i < Q; ++i) {
		for(int j = 0; j < L[i]; ++j) {
			wall[(j+i)%N] = i;
		}
		//print(wall, N);
	}
	
	int risposta = count(wall, N);

    printf("Case #%d: %d\n", t, risposta);
    free(L);
    free(wall);
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    assert(1 == scanf("%d", &T));

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
