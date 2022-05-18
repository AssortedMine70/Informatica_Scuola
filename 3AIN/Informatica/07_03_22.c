#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void printmat(int mat[][10], size_t n) {
	for(size_t i = 0; i<n; ++i) {
		for(size_t j = 0; j<n; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
}

void printvec(int vec[], size_t n) {
	for(size_t i = 0; i<n; ++i)
		printf("%3i ", vec[i]);
}

void gen_mat_emisimmetrica(int mat[][10], size_t n) {
	srand(time(NULL));
	for(size_t i = 0; i<n; ++i) {
		for(size_t j = 0; j<i; ++j) {
			int r = rand()%100;
			mat[i][j] = r;
			mat[j][i] = -r;
		}
		mat[i][i] = 0;
	}
		
}

void conv2Celsius(int v[], size_t n) {
	for(size_t i = 0; i<n; ++i)
		v[i] -= 273.15;
}

void removeValues(int v1[], size_t *n1,  int v2[], size_t n2) {
	for(size_t i=0; i<*n1; i++)
		for(size_t j=0; j<n2; ++j) {
			if(v1[i]==v2[j]) {
				memmove(v1+i, v1+i+1, (*n1-i-1)*sizeof(int));
				i--;
				(*n1)--;
			}
		}
}
