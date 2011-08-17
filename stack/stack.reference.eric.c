/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                               *
*   Name:   Eric Jacobs                       *
*   What:   Stack Implementation                      *
*   Date:   Aug 16, 2011                        *
*   File:   stack.c                       *
*   Version:0.1                           *
*                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include "include/stack.h"

// the implementation of the stack
struct Stack {
  struct Node* top;
  int length;
};

// Node for the linked list which will make the Stack.
struct Node {
  struct Node* prev;
  void* v;
};

// Initialize a Node.
struct Node* node_create(struct Node* prev, void* content);

struct Node* node_create(struct Node* prev, void* v) {
  struct Node* n = (struct Node*)malloc(sizeof(struct Node));
  n->prev = prev;
  n->v    = v;
  return n;
}

struct Stack* s_create() {
  struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));

  s->top    = NULL;
  s->length = 0;
  return s;
}

int s_length(struct Stack* s) {
  return s->length;
}

int s_push(struct Stack* s, void* v) {
  struct Node* new_node = node_create(s->top, v);
  s->top = new_node;
  return ++s->length;
}

void* s_pop(struct Stack* s) {
  if(s->top == NULL) {
    return NULL;
  }
  struct Node* node_tbd = s->top;
  void* v = node_tbd->v;
  s->top = node_tbd->prev;
  free(node_tbd);
  node_tbd = NULL;
  s->length--;
  return v;
}

void* s_peek(struct Stack* s) {
  if(s->top == NULL) {
    return NULL;
  }
  return s->top->v;
}

void s_destroy(struct Stack* s) {
  while(s->length > 0) {
    s_pop(s);
  }
  free(s);
  s = NULL;
}
