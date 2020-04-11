/* This file contains the struct definitions and prototypes for the symbolTable.c file	
	@Anshul Kumar
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
	
  char *name;											//Name for the symbol
  size_t offset;										//size
  
} Symbol;

void addDeclaration(char *name);						//Protptype for adding symbol to table
bool isDeclared(char *symbol);							//checks if symbol already there
Symbol *fetch(char *name);								//returns true or false based in if symbol is present or not				