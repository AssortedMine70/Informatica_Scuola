#include<stdio.h>
#include<stdlib.h>

#ifndef LIST_TYPE
#define LIST_TYPE int
#endif

typedef struct List List;
struct List {
	LIST_TYPE data;
	List * next;
};

List * goInTail(List * l) {
	while(l->next)
		l = l->next;
	return l;
}

size_t countElements(List * l) {
	size_t i = 0;
	while(l->next)
		l = l->next, ++i;
	return i;
}

List * newList() {
	List * l = malloc(sizeof(List));
	l->next = NULL;
	return l;
}

List * addInTail(List *l) {
	return goInTail(l)->next = newList();
}

// TODO da provare
List * addInHead(List *l) {
	List ll = newList();
	ll->next = l;
	return ll;
}

LIST_TYPE popInTail(List *l) {
	size_t N = countElements(l)-1;
	for(size_t i = 0; i < N; ++i)
		l = l->next;
	LIST_TYPE poppedData = l->next->data;
	free(l->next);
	l->next = NULL;
	return poppedData;
}

List * mergeInHead(List * l, List * ll) {
	return goInTail(l)->next = ll;
}

List * setList(List *l, LIST_TYPE data) {
	l->data = data;
	return l;
}

void printList(List *l) {
	while(l) {
		printf("%i ", l->data);
		l = l->next;
	}
	printf("\n");
}


// Esercizi
List * newNewList(size_t n) {
	if(n == 0) return NULL;
	List * l = newList();
	size_t c = 0;
	for(List * i = l; c < n; ++c, i = addInTail(i)) {
		setList(i, c);
	}
	popInTail(l);
	return l;
}

void newNewNewList(List ** l, size_t n) {
	if(n == 0) return;
	*l = newList();
	size_t c = 0;
	for(List * i = * l; c < n; ++c, i = addInTail(i)) {
		setList(i, c);
	}
	popInTail(*l);
}

List * newAddInHead(LIST_TYPE n, List * l);
void * newNewAddInHead(LIST_TYPE n, List ** l);

// fin.

int main(void) {
	List * l = newList();
	size_t c = 0;
	for(List * i = l; c < 10; ++c, i = addInTail(i)) {
		setList(i, c);
		// printList(l);
	}
	popInTail(l);
	// printList(l);
	// printf("%i\n", popInTail(l));
	printList(l);
	
	List * ll = newNewList(10);
	printList(ll);
	
	List * lll = NULL;
	newNewNewList(&lll, 10);
	printList(lll);
	
	return 0;
}
