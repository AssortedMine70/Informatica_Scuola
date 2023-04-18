#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int> a, int N) {
	for(int i = 0;  i < N; ++i) {
		cout << a[i];
	}
	cout << endl;
}

int nPermutazioni(int N) {
	if(N == 1)
		return 1;
	return N*nPermutazioni(N-1);
}

void solve(int t) {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for(int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }
    
    int risposta = 1;
    for(int k = 2; k <= N; ++k) {
    	vector<int> permutazioni(k);
    	for(int z = 0; z < k; ++z)
    		permutazioni[z] = z;
    	int p = nPermutazioni(k);
		for(int i = 0; i < p; ++i) {
			//print(permutazioni, k);
			for(int j = 0; j < k-1; ++j) {
				if(X[permutazioni[j+1]] < X[permutazioni[j]] || Y[permutazioni[j+1]] < Y[permutazioni[j]])
					break;
				if(j == N-2)
					++risposta;
			}
			next_permutation(permutazioni.begin(), permutazioni.end());
		}
	}

    cout << "Case #" << t << ": " << risposta << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
