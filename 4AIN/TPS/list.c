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

List * newList() {
	List * l = malloc(sizeof(List));
	l->next = NULL;
	return l;
}

List * addInTail(List *l) {
	while(l->next)
		l = l->next;
	return l = l->next = newList();
}

List * setList(List *l, LIST_TYPE data) {
	l->data = data;
	return l;
}

void printList(List *l) {
	List * temp = l;
	while(temp) {
		printf("%i ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(void) {
	List * l = newList();
	
	int c = 0;
	for(List * i = l; c < 10; ++c, i = addInTail(i)) {
		setList(i, c);
		printList(l);
	}
	
	printList(l);
	
	return 0;
}
