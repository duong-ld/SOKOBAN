/*
 stack.h
 
 Luong Duc Duong
 
 last change: 29/02/2020
 */

#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int direc; // UP DOWN LEFT RIGHT
    int boxMove; // boolean: move box or not
} cache;

typedef struct node
{
    cache action;
	struct node *next;
}node;

node *createNode(cache element);
void initStack(node **top);
int isEmpty(node *top);
void push(node **top, cache element);
cache pop(node **top);
void freeStack(node *top);



#endif



