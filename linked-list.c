#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked-list.h"


int get_value(LinkedList* l, int value)
{
    int count = 0;
    Node* current = (Node*)malloc(sizeof(Node));
    current = l->head;

    while (current!=NULL)
    {

        // printf("%u\n",current);
        // printf("\n %s \n",current->process_id);

        if (current->value == value)
        {
            return count;
        }
        current = current->next;
        count++;
    }
    return -1;
}

Node* get(LinkedList* l, int pos)
{
    // printf("    %s\n","Get Start");
    if (pos == 0) return l->head;
    Node* current = l->head;
    // current = &{100, next}
    for (int i = 0; i < l->size; i++)
    {
        // printf("        %d %d %s %u\n", i, current->value, "Next:", current->next);
        if (i == pos)
        {
            // printf("    %s\n", "Get End");
            return current;
        }
        current = current->next;
        // printf("        %s %d %d %s %u\n", "Current:",i, current->value, "Next:", current->next);
    }
    return NULL;
}

void append(LinkedList* l, int v, int sp)
{
    // printf("%s\n","Append Start");
    Node* new = malloc(sizeof (Node));
    new->value = v;
    new->start_pos = sp;
    new->next = NULL;
    // printf("    %s %d %d\n", "New new:",new->value,new->next);
    // printf("    %d\n", l->size-1);
    Node* tail = get(l,l->size-1);
    // printf("    %s %d %d %s %u\n", "Tail:",tail->next, tail->value,"New address:" ,&new);
    tail->next = new;
    // printf("    %u\n",new->next);
    l->size++;
}

void insert(LinkedList* l, int v, int pos)
{
    Node* new = malloc(sizeof (Node));
    new->value = v;
    new->next = NULL;

    Node* target = get(l,pos-1);
    new->next = (*target).next;
    (*target).next = new;
    l->size++;
}

// Remove já tem no stdio
void expel(LinkedList* l, int pos)
{

    //refazer para o contexto de gerenciamento de memoria
    Node* toExpel;
    if (pos == 0)
    {
        // toExpel = l->head;
        // l->head = toExpel->next;
        toExpel = l->head;
        l->head = toExpel->next;
        l->size--;
    }
    else
    {
        Node* before = get(l,pos-1);
        toExpel = before->next;
        before->next = toExpel->next;
        l->size--;
        //before == H && next == P
        // toExpel = before->next;
        // before->next = before->next->next;
    }
    toExpel = NULL;
    free(toExpel);
}


void toString(LinkedList* l)
{
    printf("%s\n","----------------");
    Node* n = l->head;
    //printf("%d\n",l->size);
    for (int i = 0; i < l->size; i++)
    {
        //printf("%d\n",i);
        char status;
        printf("Node: %d Value: %d Next: %u\n", i, n->value, n->next);
        n = n->next;
    }
    printf("%s\n\n","----------------");
}

