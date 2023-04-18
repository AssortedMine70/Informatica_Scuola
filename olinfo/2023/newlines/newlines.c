#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void solve(int t) {
    int N, K1 = INT_MIN, K2 = INT_MAX;
    assert(1 == scanf("%d", &N));

    int* W = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        assert(1 == scanf("%d", &W[i]));
    }
    
    // K1
    int count = 0;
    for(int i = 0; i < N+1; ++i) {
    	if(W[i] != -1 && i<N)
    		count += W[i] + 1;
    	else {
    		--count;
			//printf("%d\n", count);
    		if(count > K1)
    			K1 = count;
			count = 0;
		}
	}
	// K2
	for(int i = 0; i < N+1; ++i) {
    	if(W[i] != -1 && i<N)
    		count += W[i] + 1;
    	else {
			if(i < N)
				count += W[i+1];
			else
				--count;
			--count;
			//printf("%d\n", count);
			if(count < K2 && count >= K1)
				K2 = count;
			
			count = 0;
		}
	}
    
    printf("Case #%d: %d %d\n", t, K1, K2);
    free(W);
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
