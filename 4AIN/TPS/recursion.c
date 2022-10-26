#include<stdio.h>
#include<stdlib.h>

// 3 Regole sulla Ricorsione
//	1. Intestazione della funzione
//		1.1. Possiamo già usarla, fidandoci del fatto sia funzionante
//	2. Condizione di Terminazione
//	3. Ridurre la dimensione (in questo caso) della lista per facilitare il problema

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

void printList(List *l) {
	if(l == NULL) {
		printf("\n");
		return;
	}
	printf("%i ", l->data);
	printList(l->next);
}

List * insInTesta(int n, List * l) {
	List * ll = newList(n);
	ll->next = l;
	return ll;
}

List * simpleList(int n, int val) {
	if(n == 0)
		return NULL;
	return insInTesta(val, simpleList(n-1, val+10));
}

List * insOrd(int data, List * l) {
	if(l == NULL)
		return insInTesta(data, NULL);
	if(data < l->data)
		return insInTesta(data, l);
	return insInTesta(l->data, insOrd(data, l->next));
}


int main(void) {
	printList(insInTesta(10, simpleList(10, 10)));
	printList(insOrd(25, simpleList(10, 10)));
	return 0;
}
