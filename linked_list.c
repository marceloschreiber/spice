#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

void initialize(linked_list_t *l){
    l->ini = NULL;
}

void destroy(linked_list_t *l){
    node_t *aux;
    while(l->ini != NULL){
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
}

void add_element(linked_list_t *l, char element_type, char *name, int terminal_a, int terminal_b, int terminal_c, int terminal_d, double valueDouble, char *valueString){
    element_t element;
    element.element_type = element_type;
    strcpy(element.name, name);
    element.terminal_a = terminal_a;
    element.terminal_b = terminal_b;
    element.terminal_c = terminal_c;
    element.terminal_d = terminal_d;
    if(valueDouble != -1){
        element.valueDouble = valueDouble;
    }else{
        strcpy(element.valueString, valueString);
    }

    insert_at_end(l, element);
}

void insert_at_end(linked_list_t *l, element_t element){
    node_t *new = NULL; // pointer to new element
    node_t *prev = NULL; // aux. for previous position
    node_t *aux = l->ini; // aux. for iterating over the list

    new = (node_t*)malloc(sizeof(node_t)); // alloc a new node
    if (new == NULL)
    {
        exit(1); // no memory available
    }
    new->element = element;
    // Search for the position to insert
    while(aux != NULL)
    {
        prev = aux;
        aux = aux->prox;
    }
    // Link the element
    if (prev == NULL) // insert in the first position (if list is null)
    {
        new->prox = l->ini;
        l->ini = new;
    }
    else // insert at the end
    {
        new->prox = prev->prox;
        prev->prox = new;
    }
}

void print_netlist(linked_list_t *l){
    int i = 0;
    node_t *aux = l->ini;

    while(aux != NULL){
        char element_type = aux->element.element_type;
        if(element_type == 'R' || element_type == 'C' || element_type == 'L' || element_type == 'V' || element_type == 'I' || element_type == 'D'){
            printf("#%d: %c[%s]\t\t; n+[%d], n-[%d]; value=%e\n", i, aux->element.element_type, aux->element.name, aux->element.terminal_a, aux->element.terminal_b, aux->element.valueDouble);
        }else if(element_type == 'E' || element_type == 'F' || element_type == 'G' || element_type == 'H'){
            printf("#%d: %c[%s]\t\t; na[%d], nb[%d], nc[%d], nd[%d]; value=%e\n", i, aux->element.element_type, aux->element.name, aux->element.terminal_a, aux->element.terminal_b, aux->element.terminal_c, aux->element.terminal_d, aux->element.valueDouble);
        }else if(element_type == 'Q' || element_type == 'M'){
            printf("#%d: %c[%s]\t\t; na[%d], nb[%d], nc[%d], value=%s\n", i, aux->element.element_type, aux->element.name, aux->element.terminal_a, aux->element.terminal_b, aux->element.terminal_c, aux->element.valueString);            
        }
        aux = aux->prox;
        i++;
    }
}