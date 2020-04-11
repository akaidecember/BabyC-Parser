/* File for implementing the functions for making the ABSTRACT SYNTAX TREE
    
    @Anshul Kumar
*/

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

//Function to create the node for arithmatic op
ASTNode *createArithmaticOpNode(ASTArithmaticOp op, ASTNode *left, ASTNode *right) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_ARITH_OP;
  node -> arithmaticOp.op = op;
  node -> arithmaticOp.left = left;
  node -> arithmaticOp.right = right;
  return node;
    
}

//Function to create the node for the assignment op
ASTNode *createAssignmentOpNode(ASTNode *left, ASTNode *expr) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_ASSSIGN;
  node -> assignOp.left = left;
  node -> assignOp.right = expr;
  return node;
    
}

//Function to create the node for the Comparision op
ASTNode *createCompOpNode(ASTCompOp op, ASTNode *left, ASTNode *right) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_COMPARE;
  node -> compOp.op = op;
  node -> compOp.left = left;
  node -> compOp.right = right;
  return node;
    
}

//Function to create the node for the Ident
ASTNode *createIdentNode(Symbol *symbol) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_IDENT;
  node -> ident = symbol;
  return node;
    
}

//Function for creating node for if construct
ASTNode *createIfNode(ASTNode *condition, ASTNode *ifBody, ASTNode *elseBody) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_IF;
  node -> ifConstruct.condition = condition;
  node -> ifConstruct.ifBody = ifBody;
  node -> ifConstruct.elseBody = elseBody;
  return node;
    
}

//Function for creating the node for Logical OPn
ASTNode *createLogicalOpNode(ASTLogicOp op, ASTNode *left, ASTNode *right) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_LOGIC_OP;
  node -> logicalOp.op = op;
  node -> logicalOp.left = left;
  node -> logicalOp.right = right;
  return node;
    
}

//Function to create for the Numbers
ASTNode *createNumNode(int num) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_NUM;
  node -> num = num;
  return node;
    
}

//Function to create a linked list for the Statement List. We need this because each statement has to be traversed linearly
ASTNode *createStatementListNode(ASTNode *statement, ASTNode *statementList) {
    
  //Will return the statementList if the next element in the linked list is also a statement
  if (statementList != NULL) {
    statementList -> next = statement;
    return statementList;
  } 
  else 
    return statement;					//Otherwise, it will just return a statement
    
}

//Function to create the node for the while loop
ASTNode *createWhileLoopNode(ASTNode *condition, ASTNode *loopBody) {
    
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node -> type = ASTNODE_WHILE;
  node -> whileLoop.condition = condition;
  node -> whileLoop.loopBody = loopBody;
  return node;
    
}
