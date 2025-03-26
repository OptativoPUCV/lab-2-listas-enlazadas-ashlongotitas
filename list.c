#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List* list = (List*)malloc(sizeof(List));
    if(list != NULL)
    {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    }
    return list;
}

void * firstList(List * list) 
{
    if(list == NULL || list->head == NULL)
    {
        return NULL;
    }
    list->current = list->head;
    if(list->current != NULL)
    {
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) 
{
    if(list->current)
    {
        list->current = list->current->next;
        if(list->current != NULL)
        {
            return list->current->data;
        }
    }
    return NULL;
}

void * lastList(List * list) 
{
    if(list != NULL || list->tail != NULL)
    {
        list->current = list->tail;
        if(list->current != NULL)
        {
            return list->current->data;
        }
    }
    return NULL;
}

void * prevList(List * list) 
{
    if(list->current)
    {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) 
{
    Node* nodo = createNode(data);
    if(list->head == NULL)
    {
        list->head = nodo;
        list->tail = nodo;
    }
    else
    {
        nodo->next = list->head;
        list->head->prev = nodo;
        list->head = nodo;
    }
    list->current = nodo;    
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node* nodo = createNode(data);
    if(list->current == NULL)
    {
        list->head = nodo;
        list->tail = nodo;
    }
    else
    {
        if(list->current->next != NULL)
        {
            nodo->next = list->current->next;
            list->current->next->prev = nodo;
        }
        else
        {
            list->tail = nodo;
        }

        nodo->prev = list->current;
        list->current->next = nodo;
        list->current = nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    if(list->current != NULL)
    {
        void* data = list->current->data;
        Node* eliminar = list->current;
        if(list->current == list->head)
        {
            list->head = list->current->next;
            if(list->head != NULL)
            {
                list->head->prev = NULL;
            }
        }
        else if(list->current == list->tail)
        {
            list->tail = list->current->prev;
            if(list->tail != NULL)
            {
                list->tail->next = NULL;
            }
        }
        else
        {
            list->current->prev->next = list->current->next;
            list->current->next->prev = list->current->prev;
        }

        list->current = list->current->next;
        free(eliminar);
        return data;
    }

    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}   