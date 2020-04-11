/* This file has the prototypes and definitions required for the ast.c file
	@Anshul Kumar
*/

#pragma once										//pre-processor directive to ensure that the file gets defined once per compilation
#include "symbolTable.h"

//enumerated data types for the operators defined in the grammar
typedef enum { ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE} ASTNodeType;
typedef enum { ADDopn, SUBopn, MULTopn, DIVopn } ASTArithmaticOp;
typedef enum { ANDopn, ORopn } ASTLogicOp;
typedef enum { LTopn, GTopn, LEopn, GEopn, EQTopn, NETopn } ASTCompOp;
typedef struct ASTNode ASTNode;

//Structure for Arithmatic opn
typedef struct {
	
  ASTArithmaticOp op;
  ASTNode *left;
  ASTNode *right;
  
} ASTArithmaticOpNode;

//Structure for assignment opn
typedef struct {
	
  ASTNode *left;
  ASTNode *right;
  
} ASTAssignmentNode;

//Structure for Comparision
typedef struct {
	
  ASTCompOp op;
  ASTNode *left;
  ASTNode *right;
  
} ASTCompOpNode;

//Structure fir if construct
typedef struct {
	
  ASTNode *condition;
  ASTNode *ifBody;
  ASTNode *elseBody;
  
} ASTIfNode;

//Structure for Logical opns
typedef struct {
	
  ASTLogicOp op;
  ASTNode *left;
  ASTNode *right;
  
} ASTLogicalOpNode;

//Structure for while loop
typedef struct {
	
  ASTNode *condition;
  ASTNode *loopBody;
  
} ASTWhileLoopNode;

//Strucrture to handle the nodes of the Abstract Syntax tree that we are creating
typedef struct ASTNode{
	
  ASTArithmaticOpNode arithmaticOp;
  ASTLogicalOpNode logicalOp;
  ASTCompOpNode compOp;
  ASTAssignmentNode assignOp;
  ASTIfNode ifConstruct;
  ASTWhileLoopNode whileLoop;
  Symbol *ident;
  int num;
  ASTNodeType type;
  ASTNode *next;
  
};

//These functions are called by the code embedded in the grammar.
//This is the function that generates the ILOC code after the construction of the AST
//void GenerateILOC(ASTNode* node);
ASTNode *createArithmaticOpNode(ASTArithmaticOp op, ASTNode *left, ASTNode *right);
ASTNode *createAssignmentOpNode(ASTNode *left, ASTNode *expr);
ASTNode *createCompOpNode(ASTCompOp op, ASTNode *left, ASTNode *right);
ASTNode *createIdentNode(Symbol *symbol);
ASTNode *createIfNode(ASTNode *condition, ASTNode *ifBody, ASTNode *elseBody);
ASTNode *createLogicalOpNode(ASTLogicOp op, ASTNode *left, ASTNode *right);
ASTNode *createNumNode(int num);
ASTNode *createStatementListNode(ASTNode *statement, ASTNode *statement_list);
ASTNode *createWhileLoopNode(ASTNode *condition, ASTNode *loopBody);
