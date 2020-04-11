/* This file contains the functions for implementation of the symbol table. This concept uses a linked list for the storage of the symbols
	@Anshul Kumar
*/

#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure for the linked list
typedef struct Node Node;
struct Node {
	
  Symbol symbol;
  Node *next;
  
};

Node *head;
Node *tail;
size_t offset = 0;

//Function to create a new node
Node *createNode(void) {
	
  Node *node = (Node *)malloc(sizeof(Node));
  node -> symbol.name = NULL;
  node -> symbol.offset = 0;
  node -> next = NULL;
  return node;
  
}

//Function to add the new symbols to the linked list for future reference
void addDeclaration(char *symbol) {
	
  if (head == NULL) {
    head = createNode();
    tail = head;
  } 
  else {
    tail -> next = createNode();
    tail = tail -> next;
  }
  
  tail -> symbol.name = symbol;
  tail -> symbol.offset = offset;
  offset += 4;
  
}

//Function to return if the symbol table has a symbol already
bool isDeclared(char *symbol) { 

  return fetch(symbol) != NULL; 
	
}

//Function to find the given symbol in the linked list
Symbol *fetch(char *name) {
	
  Node *node;
  
  for (node = head; node != NULL; node = node -> next)
    if (strcmp(node -> symbol.name, name) == 0) 
      return &node -> symbol;
	  
  return NULL;
  
}

