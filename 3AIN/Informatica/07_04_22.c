#include <stdio.h>

int main(void) {
	FILE *f1 = fopen( "file1.txt", "r"),
		 *f2 = fopen( "file2.txt", "r"),
		 *fw = fopen("output.txt", "w");
	if(f1!=NULL) {
		if(f2!=NULL) {
			if(fw!=NULL) {
				int n, m, last;
				_Bool flag1 = fscanf(f1, "%i ", &n)==1,
				      flag2 = fscanf(f2, "%i ", &m)==1;
				while(flag1 && flag2) {
					if(n<m) {
						if(n!=last) {
							fprintf(fw, "%i ", n);
							last = n;
						}
						flag1 = fscanf(f1, "%i ", &n)==1;
					} else {
						if(m!=last) {
							fprintf(fw, "%i ", m);
							last = m;
						}
						flag2 = fscanf(f2, "%i ", &m)==1;
					}
				}
				if(flag1)
					do
						if(n!=last)	{
							last = n;
							fprintf(fw, "%i ", n);
						}
					while(fscanf(f1, "%i ", &n)==1);
				else if(flag2)
					do
						if(m!=last) {
							last = m;
							fprintf(fw, "%i ", m);
						}
					while(fscanf(f2, "%i ", &m)==1);
				fclose(fw);
			}
			else
				perror("file1.txt");
			fclose(f2);
		}
		else
			perror("file2.txt");
		fclose(f1);
	}
	else
		perror("output.txt");
	return 0;
}
