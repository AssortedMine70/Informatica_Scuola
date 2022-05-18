#include<stdio.h>
#define N 15
void Es35() {
	int v1[N], v2[N], Sum[N], Diff[N];
	printf("Inserire il Primo Vettore:\n");
	for(int i = 0; i < N; ++i)
		scanf("%i", &v1[i]);
	printf("Inserire il Secondo Vettore:\n");
	for(int i = 0; i < N; ++i)
		scanf("%i", &v2[i]);
	
	for(int i = 0; i < N; ++i) {
		Sum[i] = v1[i] + v2[i];
		Diff[i] = v1[i] - v2[i];
	}
	
	printf("\nPrimo Vettore:		");	
	for(int i = 0; i < N; ++i) {
		printf("%3i ", v1[i]);
	}
	printf("\nSecondo Vettore:	");
	for(int i = 0; i < N; ++i) {
		printf("%3i ", v2[i]);
	}
	printf("\n\nVettore Somma:		");
	for(int i = 0; i < N; ++i) {
		printf("%3i ", Sum[i]);
	}	
	printf("\nVettore Differenza:	");
	for(int i = 0; i < N; ++i) {
		printf("%3i ", Diff[i]);
	}
}

void Es36() {
	int v1[N], v2[N], sum = 0;
	printf("Inserire il Primo Vettore:\n");
	for(int i = 0; i < N; ++i)
		scanf("%i", &v1[i]);
	printf("Inserire il Secondo Vettore:\n");
	for(int i = 0; i < N; ++i)
		scanf("%i", &v2[i]);
	
	
	printf("\nPrimo Vettore:					");	
	for(int i = 0; i < N; ++i) {
		printf("%3i ", v1[i]);
	}
	printf("\nSecondo Vettore:				");
	for(int i = 0; i < N; ++i) {
		printf("%3i ", v2[i]);
	}
	printf("\n\nProdotto Scalare Naturale:		");
	for(int i = 0; i < N; ++i)
		sum+=v1[i]*v2[i];
	printf("%3i ", sum);
}

int main() {
	Es35();
	return 0;
}
