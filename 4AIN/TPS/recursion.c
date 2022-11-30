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

size_t countElements(List * l) {
	size_t i = 0;
	while(l->next)
		l = l->next, ++i;
	return i;
}

void printList(List *l) {
	if(l == NULL) {
		printf("\n");
		return;
	}
	printf("%i ", l->data);
	printList(l->next);
}

/*void printListInversa(List *l) {
	int lung = countElements(l);
	int arr[lung];
	int i = lung - 1;
	while(l != NULL) {
		arr[i] = l->data;
		l = l->next;
		--i;
	}
	for(int j = 0; j < i; ++j)
		printf("%i ", arr[j]);
	printf("\n");

	oppure
	
	List * inv;
	while(l!=NULL) {
		inv = insInTesta(l->data, inv);
		l = l->next;
	}
	printList(inv);
	
	oppure
	
	for(int i = countElements(l); i >= 0; --i) {
		List * temp = l;
		for(int j = 0; j < i; ++j)
			temp = temp->next;
		printf("%i ", temp->data);
	}
	printf("\n");
}*/

void printListInversa(List *l) {
	if(l == NULL) {
		printf("\n");
		return;
	}
	printListInversa(l->next);
	printf("%i ", l->data);
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

List * insInPos(int data, size_t i, List *l) {
	if(l==NULL)
		return newList(data);
	if(i==0)
		return insInTesta(data, l);
	return insInTesta(l->data, insInPos(data, i-1, l->next));
}

List * cancellaTutti(int data, List *l) {
	if(l==NULL)
		return NULL;
	if(l->data==data)
		return cancellaTutti(data, l->next);
	return insInTesta(l->data, cancellaTutti(data, l->next));
}

int max(List *l, int maxTemp){
	if(l == NULL)
		return maxTemp;
	if(l->data > maxTemp)
		return max(l->next, l->data);
	return max(l->next, maxTemp); 
}

int main(void) {
	printList(insInTesta(10, simpleList(10, 10)));
//	printList(insOrd(25, simpleList(10, 10)));
//	printList(cancellaTutti(10, simpleList(10, 10)));
//	printList(insInPos(42, 5, simpleList(10, 10)));
//	printListInversa(simpleList(10, 10));
//	printf("%d\n", max(simpleList(10, 10), INT_MIN));
	return 0;
}
