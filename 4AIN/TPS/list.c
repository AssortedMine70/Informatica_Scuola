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

List * newListWithData(LIST_TYPE data) {
	List * l = malloc(sizeof(List));
	l->next = NULL;
	l->data = data;
	return l;
}

List * addInTail(List *l) {
	return goInTail(l)->next = newList();
}

List * addInHead(LIST_TYPE n, List *l) {
	List * ll = newList();
	ll->next = l;
	ll->data = n;
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

void mergeInPos(List * l, List * ll, size_t i) {
	if(countElements(l) < i) return;
	for(size_t j = 0;  j < i; ++j)
		l = l->next;
	List * x = l->next;
	l->next = ll;
	goInTail(ll)->next = x;
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

List * insInPos(int data, size_t i, List * l) {
	if(countElements(l) < i) return l;
	for(size_t j = 0;  j < i; ++j) {
		l = l->next;
	}
	List * x = l->next;
	l->next = newListWithData(data);
	l->next->next = x;
	return l;
}

List * addOrdered(LIST_TYPE n, List *l) {
	if(l->data > n) {
		l = addInHead(n, l);
		return l;
	}
	List * ll = l;
	while(l->next!=NULL && l->next->data < n)
		l = l->next;
	List * x = l->next;
	l->next = newListWithData(n);
	l->next->next = x;
	return ll;
}

LIST_TYPE elementSum(List * l) {
	LIST_TYPE sum = 0;
	while(l->next) {
		sum += l->data;
		l = l->next;
	}
	sum+=l->data;
	return sum;
}

List * removeValue(LIST_TYPE n, List * l) {
	if(l->data == n) {
		List * x = l->next;
		free(l);
		return x;
	}
	List * ll = l;
	List * last = NULL;
	while(l->next!=NULL) {
		l = l->next;
		if(l->data==n) {
			last->next = l->next;
			free(l);
			return ll;
		}
		last = l;
	}
	return ll;
}

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
	printf("sum: %i\n", elementSum(ll));
	
	List * lll = NULL;
	newNewNewList(&lll, 10);
	printList(lll);
	
	mergeInPos(ll, lll, 3);
	printList(ll);
	
	insInPos(5, 3, l);
	printList(l);
	
	List * llll = newNewList(10);
	printList(llll);
	llll = addOrdered(15, llll);
	printList(llll);
	llll = removeValue(5, llll);
	printList(llll);
	return 0;
}
