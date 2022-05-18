#include<stdio.h>
#include<string.h>
#include<math.h>

void printvec(float *v) {
	for(size_t i = 0; i<3; ++i)
		printf("%.2f ", v[i]);
	printf("\n");
}

float *vectorzero(float *result) {
	return memset(result, 0, 3*sizeof(*result));
}

float *vectorcpy(float *result, const float *src) {
	return memcpy(result, src, 3*sizeof(*result));
}

float *sum(float *result, const float *va, const float *vb) {
	vectorcpy(result, va);
	for(size_t i=0; i<3; ++i)
		result[i]+=vb[i];
	return result;
}

float *diff(float *result, const float *va, const float *vb) {
	vectorcpy(result, va);
	for(size_t i=0; i<3; ++i)
		result[i]-=vb[i];
	return result;
}

float ps(const float *va, const float *vb) {
	float result=0;
	for(size_t i=0; i<3; ++i)
		result+=va[i]*vb[i];
	return result;
}

float *pps(float *result, const float *va, const float k) {
	vectorcpy(result, va);
	for(size_t i=0; i<3; ++i)
		result[i]*=k;
	return result;
}

float *pv(float *result, const float *va, const float *vb) {
	result[0]=va[1]*vb[2]-va[2]*vb[1];
	result[1]=va[2]*vb[0]-va[0]*vb[2];
	result[2]=va[1]*vb[0]-va[0]*vb[1];
	return result;
}

float mod(const float *v) {
	return sqrt(ps(v, v));
}

float pm(const float *va, const float *vb, const float *vc) {
	float t[3];
	return ps(pv(t, va, vb), vc);
}

_Bool arealligned(const float *va, const float *vb) {
	return ((vb[0]-va[0])*())-()==0 && ()-();
}

_Bool arecomplanar(const float *va, const float *vb, const float *vc) {
	return pm(va, vb, vc)==0;
}

_Bool isnull(const float *v) {
	return ps(v,v)==0;
}

int main() {
	float result[3], va[3], vb[3], vc[3], k;
	
	freopen("input.txt", "r", stdin);
	for(size_t i = 0; i<3; ++i)
		scanf("%f", &va[i]);
	for(size_t i = 0; i<3; ++i)
		scanf("%f", &vb[i]);
	for(size_t i = 0; i<3; ++i)
		scanf("%f", &vc[i]);
	scanf("%f", &k);
	
	printf("Calcoli sui Vettori di Federico Santucci.\n\n");
	printf("Vettore A:\n");
	printvec(va);
	printf("Vettore B:\n");
	printvec(vb);
	printf("Vettore C:\n");
	printvec(vc);
	printf("Valore Scalare: %.2f\n", k);
	
	printf("Vettore A + Vettore B:\n\n");
	sum(result, va, vb);
	printvec(result);
	printf("Vettore A - Vettore B:\n\n");
	diff(result, va, vb);
	printvec(result);
	printf("Prodotto Scalare di Vettore A e Vettore B:\n\n");
	printf("%.2f\n", ps(va, vb));
	printf("Prodottp per Scalare di Vettore A e Valore Scalare:\n\n");
	pps(result, va, k);
	printvec(result);
	printf("Prodotto Vettoriale di Vettore A e Vettore B:\n\n");
	pv(result, va, vb);
	printvec(result);
	printf("Modulo Vettore A: %.2f\n\n", mod(va));
	printf("Modulo Vettore B: %.2f\n\n", mod(vb));
	printf("Modulo Vettore C: %.2f\n\n", mod(vc));
	printf("I 3 Vettori sono Complanari? %s.\n", arecomplanar(va, vb, vc) ? "Vero" : "Falso");
	
	return 0;
}
