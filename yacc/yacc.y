%{

#include <stdio.h>
#include <stdlib.h>

/* Lexer parsing method. */
extern int yylex();

/* Reports error if YACC finds one. */
__attribute((noreturn)) void yyerror(const char* error_str)
{
  fprintf(stderr, "YACC: %s \n", error_str);
  exit(EXIT_FAILURE);
}

%}

%token ADD SUB MUL DIV AND XOR NOT OR
%token VAR_ID STD_CONST STD_FUNC NUMINT NUMFLT 
%token OPEN_BR_RND CLOS_BR_RND OPEN_BR_CRVD CLOS_BR_CRVD

/* Rules section. */
%%

expr:      top_term | expr AND top_term | expr OR top_term
top_term:  term | expr ADD term | expr SUB term
term:      factor | term MUL factor | term DIV factor
factor:    VAR_ID | constant | OPEN_BR_CRVD expr CLOS_BR_CRVD | unary | std_func

constant:  STD_CONST | number
number:    NUMINT | NUMFLT

unary:     NOT factor

std_func:  STD_FUNC OPEN_BR_RND expr CLOS_BR_RND
