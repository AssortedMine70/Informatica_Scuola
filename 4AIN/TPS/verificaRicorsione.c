#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct List List;
struct List {
	int data;
	List *next;
};

List * newList(int n) {
	List * l = malloc(sizeof(List));
	l->data = n;
	l->next = NULL;
	return l;
}

List * insInTesta(int n, List * l) {
	List * ll = newList(n);
	ll->next = l;
	return ll;
}

void printList(List *l) {
	if(l == NULL) {
		printf("\n");
		return;
	}
	printf("%i ", l->data);
	printList(l->next);
}

List * simpleList(int n, int val) {
	if(n == 0)
		return NULL;
	return insInTesta(val, simpleList(n-1, val+10));
}

List * sottolista(int indiceInizio, int indiceFine, List * l) {
	if(l == NULL || indiceFine < 0)
		return NULL;
	if(indiceInizio == 0)
		return insInTesta(l->data, sottolista(0, indiceFine-1, l->next));
	return sottolista(indiceInizio-1, indiceFine-1, l->next);
	// Versione altrernativa
	// if(l == NULL || indiceFine == 0) return NULL;
	// if(indiceInizio > 0) return sottolista(indiceInizio-1, indiceFine-1, l->next);
	// return sottolista(indiceInizio, indiceFine-1, l->next);
}

_Bool trova(int valDaCercare, List * l) {
	if(l == NULL)
		return 0;
	if(l->data == valDaCercare)
		return 1;
	return trova(valDaCercare, l->next);
}

List * creaR3(int quanti, int primoVal, int secondoVal, int cont) { // cont è inutilizzato.
	if(quanti == 0)
		return NULL;
	// inutili, ma
	// if(quanti == 1) return insInTesta(primoVal, NULL);
	// if(quanti == 2) return insInTesta(primoVal, insInTesta(secondoVal, NULL));
	return insInTesta(primoVal, creaR3(quanti-1, secondoVal, primoVal + secondoVal, cont+1));
}

List * mergeR(List * l1, List * l2) {
	if(l1 == NULL)
		return l2;
	if(l2 == NULL)
		return l1;
	return insInTesta(l1->data, mergeR(l2, l1->next));
	// Versione altrernativa
	// return insInTesta(l1->data, insInTesta(l2->data, merge(l1->next, l2->next)));
}

int main(void) {
	printList(simpleList(10, 10));
	printList(sottolista(3, 6, simpleList(10, 10)));
	printf("Trovato: %s\n", trova(50, simpleList(10, 10)) ? "true" : "false");
	printList(creaR3(8, 0, 1, 0));
	printList(simpleList(5, 10));
	printList(simpleList(10, 15));
	printList(mergeR(simpleList(5, 10), simpleList(10, 15)));
	return 0;
}
