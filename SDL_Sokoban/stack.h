/*
 stack.h
 
 Luong Duc Duong
 
 last change: 29/02/2020
 */

#ifndef _STACK_H
#define _STACK_H

typedef int cache;
typedef struct node
{
    cache action;
	struct node *next;
}node;
#define empty -1

node *createNode(cache element);
void initStack(node **top);
int isEmpty(node *top);
void push(node **top, cache element);
cache pop(node **top);


#endif



