#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void solve(int t) {
    int x[4], y[4];
	scanf(" %d %d", &x[0], &y[0]);
    scanf(" %d %d", &x[1], &y[1]);
    scanf(" %d %d", &x[2], &y[2]);
	
//	for(int i = 0; i < 3; ++i)
//		printf("%d %d\n", x[i], y[i]);
	
	if(x[0] == x[1])
		x[3] = x[2];
	else if(x[1] == x[2])
		x[3] = x[0];
	else
		x[3] = x[1];
    
    if(y[0] == y[1])
		y[3] = y[2];
	else if(y[1] == y[2])
		y[3] = y[0];
	else
		y[3] = y[1];
    
    printf("Case #%d: %d %d\n", t, x[3], y[3]);
}

int main() {
    int T, t;

    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &T));

    for (t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
