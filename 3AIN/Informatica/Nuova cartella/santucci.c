#include<stdio.h>
#include<math.h>

typedef float poly[11]; // poly[0]=coefficiente di x^0, poly[1]=coefficiente di x^1, poly[2]=coefficiente di x^2, ecc.

// restituisce il valore assoluto di un float
float fsabs(float n) {
	return n > 0 ? n : -n;
}

// restituisce il polinomio al polinomio nullo
void zero(poly result) {
	for(unsigned i=0; i<sizeof(poly)/sizeof(result[0]); ++i)
		result[i]=0;
}

// restituisce il massimo fra x e y
unsigned max(unsigned x, unsigned y) {
	return x>y ? x : y;
}

// restituisce il grado del polinomio aumentato di 1, altrimenti 0 se i coefficienti sono tutti nulli
unsigned degree(poly p) {
	for(unsigned i=sizeof(poly)/sizeof(p[0]); i-->0; )
		if(p[i])
			return i+1;
	return 0;
}

// stampa il polinomio ed il suo grado
void print(poly p){
	if(degree(p)) {
		printf("Degree: %d\n", degree(p));
		for(int i=degree(p)+1; i-->0; )
			if(p[i] != 0) //Se il polinomio è nullo non stampa nulla in quanto ogni p[i] è 0
				p[i] > 0 ? printf("+ %.2fx^%d ", p[i], i) : printf("- %.2fx^%d ", -p[i], i);
		printf("\n");
	}
	else
		printf("Polinomio Nullo\n");
}

// calcola il polinomio somma p1+p2
void sum(poly result, poly p1, poly p2) {
	zero(result); // si imposta a 0 il polinomio risultato
	unsigned deg = max(degree(p1), degree(p2)); // imposta il grado del polinomio risultato
	for(unsigned i=0; i<deg; ++i)
		result[i] = p1[i] + p2[i]; // imposta i coefficienti del polinomio risultato
}

// calcola il polinomio opposto -p
void neg(poly result, poly p) {
	zero(result); // si imposta a 0 il polinomio risultato
	for(unsigned i=degree(p); i-->0; )
		result[i] = -p[i]; // moltiplica il coefficente per -1
}

// calcola il polinomio prodotto p1*p2
void mul(poly result, poly p1, poly p2) {
	zero(result); // si imposta a 0 il polinomio risultato
	for(unsigned i=0; i<degree(p1); ++i)
		for(unsigned j=0; j<degree(p2); ++j) // moltiplicazione per ogni monomio del primo polinomio con ogni polinomio del secondo
			result[i+j] += p1[i] * p2[j]; // imposta i coefficienti del polinomio risultato come moltiplicazione dei monomi, sommate alle moltiplicazioni precedenti di stesso grado
}


// calcola il polinomio a radici opposte
void radopposte(poly result, poly p) {
	zero(result); // si imposta a 0 il polinomio risultato
	for(unsigned i=degree(p); i-->0; )
		i%2 ? (result[i] = -p[i]) : (result[i] = p[i]); // cambia il segno al monomio se di grado dispari
}

// calcola il polinomio a radici reciproche
void radreciproche(poly result, poly p) {
	zero(result); // si imposta a 0 il polinomio risultato
	for(unsigned i=0; i<degree(p); ++i)
		result[i]=p[degree(p)-i-1]; // imposta i coefficenti del polinomio risultato specchiati sull'asse y rispetto al polinomio originale
}

// calcola il numero di radici nulle
unsigned maxnulls(poly p) {
		for(unsigned i=0; degree(p); ++i)
			if(p[i]) // controlla se il monomio di grado i del polinomio è nullo
				return i; // restituisce il numero di radici nulle, corrispondente al grado del monomio di grado minore del polinomio.
	return 0;
}

// calcola il numero massimo di radici positive
unsigned maxpos(poly p) {
	unsigned vars = 0, last = maxnulls(p); // vars: conta il numero di variazioni di segno, corrispondente al numero di radici positive. last: indice dell'ultimo valore diverso da 0.
	for(unsigned i=last; i<degree(p); ++i)
		if(p[last]*p[i+1] < 0) { // controlla che l'ultimo monomio diverso da zero e il successivo non siano nulli nè discordi
			vars++;
			last=i+1; // imposta l'ultimo monomio diverso da 0 al successivo monomio diverso da 0
		}
	return vars; // restituisce il numero di variazioni di segno, corrispondente al numero di radici positive
}

// calcola il numero massimo di radici negative
unsigned maxneg(poly p) {
	poly negp;
	radopposte(negp, p); // inverte il segno del polinomio per calcolare le radici negative
	return maxpos(negp); // il numero massimo di radici positive di un polinomio è il numero massimo di radici megative di un polinomio opposto
}

// calcola il valore del polinomio nel punto x
float polyval(poly p, float x) {
	float sum = 0.0;
	for(unsigned i = 0; i < degree(p); ++i)
		sum+=p[i]*pow(x, i); // moltiplica il coefficente per il valore di x elevato al grado di x
	return sum;
}

 // copia il polinomio source sul polinomio destination
void polycopy(poly destination, poly source) {
	for(unsigned i = sizeof(poly)/sizeof(source[0]); i-->0; )
		destination[i] = source[i];
}

// calcola il polinomio quoziente p1/p2
void quotient(poly result, poly p1, poly p2) {
	zero(result); // si imposta a 0 il polinomio risultato
	poly Q, temp;
	zero(Q); // si inizializza la variabile di appoggio per il quoziente e per i calcoli intermedi
	polycopy(Q, p1); // copia il dividendo in una variabile d'appoggio
	if(degree(p2) && degree(Q)>=degree(p2)) { // si controlla se il grado di p1 è maggiore di p2, in quanto criterio di divisibilità. p2 deve essere diverso da 0 in quanto la divisione per 0 è sempre impossibile
		while(degree(Q)>=degree(p2)) {
			result[degree(Q)-degree(p2)] = Q[degree(Q)-1]/p2[degree(p2)-1];
			zero(temp);
			unsigned t = degree(Q)-degree(p2)+maxnulls(p2);
			for(unsigned i=t; i<=degree(p1); ++i) // moltiplicazione dell'ultimo monomio ottenuto per il divisore
				temp[i] = p2[i-t]*result[degree(Q)-degree(p2)];
			for(unsigned i=0; i<degree(Q); ++i)
					Q[i] -= temp[i];
		}
	}
	else if(degree(p2))
		zero(result);
}

// calcola il polinomio resto p1%p2
void reminder(poly result, poly p1, poly p2) {
	zero(result); // si imposta a 0 il polinomio risultato
	poly Q, temp;
	zero(Q); // si inizializza la variabile di appoggio per il quoziente e per i calcoli intermedi
	polycopy(Q, p1); // copia il dividendo in una variabile d'appoggio
	if(degree(p2) && degree(Q)>=degree(p2)) { // si controlla se il grado di p1 è maggiore di p2, in quanto criterio di divisibilità. p2 deve essere diverso da 0 in quanto la divisione per 0 è sempre impossibile
		while(degree(Q)>=degree(p2)) {
			result[degree(Q)-degree(p2)] = Q[degree(Q)-1]/p2[degree(p2)-1];
			zero(temp); 
			unsigned t = degree(Q)-degree(p2)+maxnulls(p2);
			for(unsigned i=t; i<=degree(p1); ++i) // moltiplicazione dell'ultimo monomio ottenuto per il divisore
				temp[i] = p2[i-t]*result[degree(Q)-degree(p2)];
			for(unsigned i=0; i<degree(Q); ++i)
					Q[i] -= temp[i];
		}
		zero(result);
		for(unsigned i = 0; i<degree(Q); ++i)
			result[i] = Q[i];
	}
	else
		for(unsigned i = 0; i<degree(p1); ++i)
			result[i] = p1[i];
}

// rende monico il polinomio p
void polymon(poly p) {
	for(unsigned i = 0; i<degree(p); ++i) // imposta a 0 tutti i coefficenti maggiori di 1
		p[i] /= p[degree(p)-1];
}


// calcola la derivata del polinomio p
void polyder(poly p) {
	for(unsigned i = 0; i<degree(p)-1; ++i)
		p[i]=p[i+1]*(i+1);
	p[degree(p)-1]=0;
}

// restituisce il valore massimo/minimo delle radici di un polinomio
float algCauchy(poly p) {
	polymon(p);
	float max = fsabs(p[degree(p)-1]);
	for(unsigned i = 0; i<degree(p)-2; ++i)
		if(fsabs(p[i])>max)
			max = fsabs(p[i]);
	return max;
}

int main() {
	poly p1, p2, p3, result;
	
	zero(p1);
	zero(p2);
	zero(result);
	
	printf("Calcoli polinomi di Federico Santucci\n\n");
	
	// legge il file
	freopen("input.txt", "r", stdin);
	unsigned grade;
	scanf("%u", &grade);
	for(unsigned i=grade+1; i-->0; )
		scanf("%f", &p1[i]);
	scanf("%u", &grade);
	for(unsigned i=grade+1; i-->0; )
		scanf("%f", &p2[i]);
	
	// stampa dei polinomi
	printf("Polinomio 1:\n");
	print(p1);
	printf("Polinomio 2:\n");
	print(p2);
	
	// stampa delle varie funzioni
	printf("\nSomma:\n");
	sum(result, p1, p2);
	print(result);
	
	printf("\nNegativo:\n");
	printf("Polinomio 1:\n");
	neg(result, p1);
	print(result);
	printf("Polinomio 2:\n");
	neg(result, p2);
	print(result);
	
	printf("\nMoltiplicazione:\n");
	mul(result, p1, p2);
	print(result);
	
	printf("\nQuoziente:\n");
	quotient(result, p1, p2);
	if(degree(p2))
		print(result);
	else
		printf("Impossibile\n");
	printf("Resto:\n");
	reminder(result, p1, p2);
	print(result);
	
	printf("\nPolinomio a Radici Opposte:\n");
	printf("Polinomio 1:\n");
	radopposte(result, p1);
	print(result);
	printf("Polinomio 2:\n");
	radopposte(result, p2);
	print(result);
	
	printf("\nPolinomio a Radici Reciproche:\n");
	printf("Polinomio 1:\n");
	radreciproche(result, p1);
	print(result);
	printf("Polinomio 2:\n");
	radreciproche(result, p2);
	print(result);
	
	printf("\nPolinomio 1:\n");
	printf("zero: %u, pos: %u, neg: %u\n", maxnulls(p1), maxpos(p1), maxneg(p1));
	for(float x=-2; x!=2; x++)
		printf("P(%9.2f): %9.2f\n", x, polyval(p1, x));
	printf("\nPolinomio 2:\n");
	printf("zero: %u, pos: %u, neg: %u\n", maxnulls(p2), maxpos(p2), maxneg(p2));
	for(float x=-2; x!=2; x++)
		printf("P(%9.2f): %9.2f\n", x, polyval(p2, x));
	
	printf("\nCopia del Primo Polinomio:\n");
	polycopy(p3, p1);
	print(p3);
	printf("\nTrasformazione del Primo Polinomio in polinomio Monico:\n");
	polycopy(p3, p1);
	polymon(p3);
	print(p3);
	printf("\nDerivata del Primo Polinomio:\n");
	polycopy(p3, p1);
	polyder(p3);
	print(p3); 
	polycopy(p3, p1);
	printf("\nValore Massimo/Minimo delle Radici del Primo Polinomio:\n %.2f", algCauchy(p3));
	
	return 0;
}
