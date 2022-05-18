#include<stdio.h>

// Prints
void printvec(int vec[], size_t n) {
	for(size_t i = 0; i < n; ++i)
		printf("%3i ", vec[i]);
	printf("\n");
}
void printmatrix(int mat[][10], size_t rows, size_t cols) {
	for(size_t i = 0; i < rows; ++i) {
		for(size_t j = 0; j < cols; ++j)
			printf("%3i ", mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

// Exercises
void es1(int vec [], size_t n) {
	for(size_t i = 0; i < n; ++i) {
		int temp = vec[i];
		vec[i] = vec[i+n/2+1];
		vec[i+n/2+1] = temp;
	}
}

void es2(int mat[][10], size_t rows, size_t cols) {
	for(size_t i = 0; i < cols; ++i) {
		int temp = mat[i][i];
		mat[i][i] = mat[i][cols-i-1];
		mat[i][cols-i-1] = temp;
	}
}

size_t es3(int vec[], size_t n) {
	for(size_t i = ++n; i-- > n/2; )
		vec[i] = vec[i-1];
	for(size_t i = n/2; i-- > 1; )
		vec[i] = vec[i-1];
	return n;
}

void es4(int mat[][10], size_t rows, size_t cols) {
	int count = 0;
	for(size_t i = 0; i < rows; ++i)
		for(size_t j = 0; j < cols; ++j)
			if(mat[i][j])
				printf("false"), ++count;
	if(!count)
		printf("true");
}

void es5(int vec[], size_t n) {
	float sum = 0;
	for(size_t i = 0; i < n; ++i)
		if(vec[i]%10==9 || vec[i]==9)
			sum+=vec[i];
	printf("%.3f", sum/n);
}

int main()
{
	return 0;
}
