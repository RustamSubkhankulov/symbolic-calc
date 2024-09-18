%{

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "yacc_calc_support.h"
#include "standard.h"
#include "calc.h"

/* Lexer parsing method. */
extern int yylex();

/* Current symbol position. */
extern int gCur_pos;

/* Helper function for displaying parsing errors. */
extern void underline_print_error(int cur_pos);

/* Reports error if YACC finds one. */
__attribute__((noreturn)) void yyerror(float* eval_res, const char* error_str)
{
  (void) eval_res;

  fprintf(stderr, "YACC: %s \n", error_str);
  underline_print_error(gCur_pos - 1);

  exit(EXIT_FAILURE);
}

#define FLOAT_CMP_EPS 0.000001f
static bool float_is_zero_with_prec(float arg)
{
  return (fabs(arg) < FLOAT_CMP_EPS);
}

#ifdef VERBOSE_YACC
#define YACC_VPRINT(...) do { fprintf(stderr, __VA_ARGS__); } while(0);
#else
#define YACC_VPRINT(...)
#endif

%}

%union
{
  int ival;
  float fval;
  const char* sval;
}

%parse-param {float* eval_res}

%token ADD SUB MUL DIV POW NOT
%token VAR_ID STD_CONST STD_FUNC NUMINT NUMFLT
%token OPEN_BR_RND CLOS_BR_RND OPEN_BR_CRVD CLOS_BR_CRVD

/* Rules section. */
%%

result: expr { 
  YACC_VPRINT("Evaluating result. ");
  *eval_res = $<fval>$; return 0; 
}

expr:
  term { 
    $<fval>$ = $<fval>1; 
    YACC_VPRINT("Evaluating expr: %f = %f \n", $<fval>$, $<fval>1);
  }
  | expr ADD term { 
    $<fval>$ = $<fval>1 + $<fval>3; 
    YACC_VPRINT("Evaluating expr: %f + %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
  | expr SUB term {
    $<fval>$ = $<fval>1 - $<fval>3;
    YACC_VPRINT("Evaluating expr: %f - %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }

term:
  power { 
    $<fval>$ = $<fval>1; 
    YACC_VPRINT("Evaluating term: %f = %f \n", $<fval>$, $<fval>1);
  }
  | term MUL power { 
    $<fval>$ = $<fval>1 * $<fval>3;
    YACC_VPRINT("Evaluating term: %f * %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
  | term DIV power { 
    $<fval>$ = $<fval>1 / $<fval>3; 
    YACC_VPRINT("Evaluating term: %f / %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }

power:
  factor { 
    $<fval>$ = $<fval>1; 
    YACC_VPRINT("Evaluating power: %f = %f \n", $<fval>$, $<fval>1);
  }
  | power POW factor {
    $<fval>$ = pow($<fval>1, $<fval>3);
    YACC_VPRINT("Evaluating power: %f ^ %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }

factor: 
  OPEN_BR_CRVD expr CLOS_BR_CRVD { 
    $<fval>$ = $<fval>2;
    YACC_VPRINT("Evaluating factor: %f = (%f) \n", $<fval>$, $<fval>2);
  }
  | VAR_ID { 
    YACC_VPRINT("Evaluating factor: name %s \n", $<sval>1);
    $<fval>$ = calc_get_var_value($<sval>1); 
    YACC_VPRINT("Evaluated factor: %f \n", $<fval>$);
  }
  | constant { 
    $<fval>$ = $<fval>1; 
    YACC_VPRINT("Evaluating factor: %f = %f \n", $<fval>$, $<fval>1);
  }
  | std_func { 
    $<fval>$ = $<fval>1;
    YACC_VPRINT("Evaluating factor: %f = %f \n", $<fval>$, $<fval>1);
  }
  | unary { 
    $<fval>$ = $<fval>1;
    YACC_VPRINT("Evaluating factor: %f = %f \n", $<fval>$, $<fval>1); 
  }

unary: 
  SUB factor { 
    $<fval>$ = -$<fval>2; 
    YACC_VPRINT("Evaluating unary: %f = - %f \n", $<fval>$, $<fval>1);
  }
  | ADD factor {
    $<fval>$ = $<fval>2;
    YACC_VPRINT("Evaluating unary: %f = + %f \n", $<fval>$, $<fval>1);
  }
  | NOT factor {
    $<fval>$ = float_is_zero_with_prec($<fval>2);
    YACC_VPRINT("Evaluating unary: %f = + %f \n", $<fval>$, $<fval>1);
  }

constant:  
  STD_CONST { 
    YACC_VPRINT("Evaluating constant: code %d \n", $<ival>1);
    $<fval>$ = std_const_value($<ival>1); 
    YACC_VPRINT("Evaluated constant: %f \n", $<fval>$);
  }
  | NUMINT { 
    $<fval>$ = $<ival>1; 
    YACC_VPRINT("Evaluating constant: %f = %d \n", $<fval>$, $<ival>1);
  }
  | NUMFLT { 
    $<fval>$ = $<fval>1; 
    YACC_VPRINT("Evaluating constant: %f = %f \n", $<fval>$, $<fval>1);
  }

std_func: STD_FUNC OPEN_BR_RND expr CLOS_BR_RND {
  YACC_VPRINT("Evaluating std_func: code %d arg %f \n", $<ival>1, $<fval>3);
  $<fval>$ = std_func_evaluate($<ival>1, $<fval>3);
  YACC_VPRINT("Evaluated std_func: %f \n", $<fval>$);  
}
