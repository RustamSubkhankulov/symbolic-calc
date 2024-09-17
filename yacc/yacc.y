%{

#include <stdio.h>
#include <stdlib.h>

#include "yacc_calc_support.h"
#include "standard.h"
#include "calc.h"

/* Lexer parsing method. */
extern int yylex();

/* Reports error if YACC finds one. */
__attribute((noreturn)) void yyerror(float* eval_res, const char* error_str)
{
  (void) eval_res;
  fprintf(stderr, "YACC: %s \n", error_str);
  exit(EXIT_FAILURE);
}

#ifdef VERBOSE_YACC
#define YACC_VERBOSE_PRINT(...) do { fprintf(stderr, __VA_ARGS__); } while(0);
#else
#define YACC_VERBOSE_PRINT(...)
#endif

%}

%union
{
  int ival;
  float fval;
  const char* sval;
}

%parse-param {float* eval_res}

%token ADD SUB MUL DIV
%token VAR_ID STD_CONST STD_FUNC NUMINT NUMFLT
%token OPEN_BR_RND CLOS_BR_RND OPEN_BR_CRVD CLOS_BR_CRVD

/* Rules section. */
%%

result: expr { 
  YACC_VERBOSE_PRINT("Evaluating result. ");
  *eval_res = $<fval>$; return 0; 
}

expr:
  term { $<fval>$ = $<fval>1; }
  | expr ADD term { 
    $<fval>$ = $<fval>1 + $<fval>3; 
    YACC_VERBOSE_PRINT("%f + %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
  | expr SUB term {
    $<fval>$ = $<fval>1 - $<fval>3;
    YACC_VERBOSE_PRINT("%f - %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }

term:
  factor { $<fval>$ = $<fval>1; }
  | term MUL factor { 
    $<fval>$ = $<fval>1 * $<fval>3;
    YACC_VERBOSE_PRINT("%f * %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
  | term DIV factor { 
    $<fval>$ = $<fval>1 / $<fval>3; 
    YACC_VERBOSE_PRINT("%f / %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }

factor: 
  OPEN_BR_CRVD expr CLOS_BR_CRVD { $<fval>$ = $<fval>2; }
  | VAR_ID { 
    YACC_VERBOSE_PRINT("Evaluating 'var_id': name %s \n", $<sval>1);
    $<fval>$ = calc_get_var_value($<sval>1); 
    YACC_VERBOSE_PRINT("Evaluated 'var_id': %f \n", $<fval>$);
  }
  | constant { $<fval>$ = $<fval>1; }
  | std_func { $<fval>$ = $<fval>1; }

constant:  
  STD_CONST { 
    YACC_VERBOSE_PRINT("Evaluating 'STD_CONST': code %d \n", $<ival>1);
    $<fval>$ = std_const_value($<ival>1); 
    YACC_VERBOSE_PRINT("Evaluated 'STD_CONST': %f \n", $<fval>$);
  }
  | NUMINT { $<fval>$ = $<ival>1; }
  | NUMFLT { $<fval>$ = $<fval>1; }

std_func: STD_FUNC OPEN_BR_RND expr CLOS_BR_RND {
  YACC_VERBOSE_PRINT("Evaluating 'std_func': code %d arg %f \n", $<ival>1, $<fval>3);
  $<fval>$ = std_func_evaluate($<ival>1, $<fval>3);
  YACC_VERBOSE_PRINT("Evaluated 'std_func': %f \n", $<fval>$);  
}
