%{
	#include "ast.h"
	#include "symbolTable.h"
	#include <stdio.h>
	#include <string.h>

//The parser needs to call the scanner to get the next token
	extern int yylex();

//The error function
	extern int yyerror(const char *);

//The ASTNode root
    extern ASTNode* g_ast_root;
  
%}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...)
%union 
{

  ASTNode* node;					//Most $$ values will be ASTNodes
  int num;							//Integer numbers
  char* string;						//Strings for identifiers
  ASTCompOp compOp;					//Comparison
  
}

//Token types for IDENT and NUM
%token <string> IDENT
%token <num> NUM

//Each non-terminal type for the grammar defined below
%type <node> DeclarationList
%type <node> Statement
%type <node> StatementList
%type <node> Assignment
%type <node> left
%type <node> Condition
%type <node> Compare
%type <node> ComparePrime
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <compOp> CompOp

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'
{

  g_ast_root = $6;
  
};

DeclarationList: /* Empty */ {} | Declaration DeclarationList {}

Declaration: "int" IDENT ';'
{
  if (isDeclared($2)) {
  
    char *err_msg_part = "Multiple declarations of";
    char *err_msg = (char *)malloc(strlen(err_msg_part) + strlen($2) + 4);
    sprintf(err_msg, "%s '%s'", err_msg_part, $2);
    yyerror(err_msg);
	
  }
  
  addDeclaration($2);
  printf("Processing declaration of %s\n", $2);
  
};

StatementList: /* Empty */
{

  $$ = NULL;
  
} 
| Statement StatementList
{

  $$ = createStatementListNode($1,$2);
  printf("Adding a Statement to a Statement list \n");
  
};

Statement: Assignment
{

  $$ = $1;
  
}
| "while" '(' Condition ')' '{' StatementList '}'
{

  printf("Creating while loop node\n");
  $$ = createWhileLoopNode($3, $6);
  
}
| "if" '(' Condition ')' '{' StatementList '}'
{

  printf("Creating if Statement node\n");
  $$ = createIfNode($3, $6, NULL);
  
}
| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}'
{

  printf("Creating if-else Statement node\n");
  $$ = createIfNode($3, $6, $10);
  
};

Assignment: left '=' Expr ';'
{

  printf("Creating Assignment node\n");
  $$ = createAssignmentOpNode($1, $3);
  
};

left: IDENT
{

  Symbol *symbol = fetch($1);
  
  if (symbol == NULL) 
    yyerror("Ident not declared");
	
  
  printf("Creating left-hand IDENT node for %s\n", $1);
  $$ = createIdentNode(symbol);
  
};

Condition: Compare
{

  $$ = $1;
  
}
| Compare OR Compare
{

  printf("Creating OR node\n");
  $$ = createLogicalOpNode(ORopn, $1, $3);
  
};

Compare: ComparePrime
{

  $$ = $1;
  
}
| ComparePrime AND ComparePrime
{

  printf("Creating AND node\n");
  $$ = createLogicalOpNode(ANDopn, $1, $3);
  
};

ComparePrime: Expr CompOp Expr
{

  printf("Creating Compare node\n");
  $$ = createCompOpNode($2, $1, $3);
  
};

CompOp:
  '<'  
{ 

	$$ = LTopn; 
	
}
| '>'  
{

	$$ = GTopn;
	
}
| "<=" 
{

	$$ = LEopn; 
	
}
| ">=" 
{ 
	
		$$ = GEopn; 
		
}
| "==" 
{ 

	$$ = EQTopn; 
	
}
| "!=" { 

	$$ = NETopn; 
	
};

Expr: Expr '+' Term
{

  printf("Creating Addition node\n");
  $$ = createArithmaticOpNode(ADDopn, $1, $3);
  
}
| Expr '-' Term
{

  printf("Creating Subtraction node\n");
  $$ = createArithmaticOpNode(SUBopn, $1, $3);
  
}
| Term
{

  $$ = $1;
  
};

Term: Term '*' Factor
{

  printf("Creating Multiplication node\n");
  $$ = createArithmaticOpNode(MULTopn, $1, $3);
  
}
| Term '/' Factor
{

  printf("Creating Division node\n");
  $$ = createArithmaticOpNode(DIVopn, $1, $3);
  
}
| Factor
{

  $$ = $1;
  
};

Factor: IDENT
{

  Symbol *symbol = fetch($1);
  
  if (symbol == NULL) 
    yyerror("Ident not declared");
  
  printf("Creating IDENT node for %s\n", $1);
  $$ = createIdentNode(symbol);
  
}
| NUM
{

  $$ = createNumNode($1);
  printf("Creating NUM node for %d\n", $1);
  
}
| '(' Expr ')'
{

  printf("Creating Expression node in parentheses\n");
  $$ = $2;
  
};

%%
