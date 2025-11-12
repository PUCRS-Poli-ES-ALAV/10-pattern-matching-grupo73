#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#define P 1
#define H 0

typedef struct Node Node;

struct Node
{
    int start_pos;
    int value;
    Node* next;
};

typedef struct {
	int size; 
    Node* head;
    Node** buffer;
} LinkedList;

int get_value(LinkedList* l, int value);

Node* get(LinkedList* l, int pos);

void append(LinkedList* l, int v, int sp);

void insert(LinkedList* l, int v, int pos);

void expel(LinkedList* l, int pos);

void toString(LinkedList* l);

#endif