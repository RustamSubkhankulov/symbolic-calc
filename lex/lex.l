/* Options. */
%option noyywrap nounput noinput

/* Includes. */
%top {
  #include <stdio.h>
  #include <string.h>
  #include "standard.h"
  #include "yacc.h"
}

/* Definitions. */
%{

/* Current symbol position. */
extern int gCur_pos;

/* Helper function for displaying parsing errors. */
extern void underline_print_error(int cur_pos);

__attribute__((noreturn)) static void lexical_error(const char* yytext)
{
  fprintf(stderr, "Lexical error. Unexpected token: [%s] \n", yytext);
  underline_print_error(gCur_pos);

  exit(EXIT_FAILURE);
}

#ifdef VERBOSE_LEX
#define LEX_VPRINT(...) do { fprintf(stderr, __VA_ARGS__); } while(0);
#else
#define LEX_VPRINT(...)
#endif

%}

/* Categories. */

DIGIT0  [0-9]
DIGIT1  [1-9]
ALPHALC [a-z]
ALPHAUC [A-Z]
ALPHA   {ALPHALC}|{ALPHAUC}

DECINT  {DIGIT0}|({DIGIT1}{DIGIT0}*)
NUMINT  [-+]?{DECINT}

DECFLT  ({DECINT}?[.]{DIGIT0}{1,6})|({DECINT}[.]({DIGIT0}{0,6})?)
NUMFLT  [-+]?{DECFLT}

NM_TAIL ({ALPHA}|{DECINT})*
NAMEUC  {ALPHAUC}{NM_TAIL}
NAMELC  {ALPHALC}{NM_TAIL}
NAME    {NAMEUC}|{NAMELC}

ID_TAIL (_|{NAME}|{DECINT}|\$)*
VAR_ID  {NAME}{ID_TAIL}

/* Rules section. */
%%

sin  { LEX_VPRINT("STD_FUNC: %s \n", yytext); gCur_pos += yyleng; yylval.ival = SIN;  return STD_FUNC; }
cos  { LEX_VPRINT("STD_FUNC: %s \n", yytext); gCur_pos += yyleng; yylval.ival = COS;  return STD_FUNC; }
tg   { LEX_VPRINT("STD_FUNC: %s \n", yytext); gCur_pos += yyleng; yylval.ival = TG;   return STD_FUNC; }
ctg  { LEX_VPRINT("STD_FUNC: %s \n", yytext); gCur_pos += yyleng; yylval.ival = CTG;  return STD_FUNC; }
sqrt { LEX_VPRINT("STD_FUNC: %s \n", yytext); gCur_pos += yyleng; yylval.ival = SQRT; return STD_FUNC; }

PI  { LEX_VPRINT("STD_CONST: %s \n", yytext); gCur_pos += yyleng; yylval.ival = PI;  return STD_CONST; }
EXP { LEX_VPRINT("STD_CONST: %s \n", yytext); gCur_pos += yyleng; yylval.ival = EXP; return STD_CONST; }

{NUMINT} { 

  LEX_VPRINT("NUMINT: %s \n", yytext); 

  gCur_pos += yyleng;
  yylval.ival = atoi(yytext);
  
  return NUMINT; 
}

{NUMFLT} { 

  LEX_VPRINT("NUMFLT: %s \n", yytext); 

  gCur_pos += yyleng;
  yylval.fval = atof(yytext);
  
  return NUMFLT; 
}

{VAR_ID} { 

  LEX_VPRINT("VAR_ID: %s \n", yytext);

  gCur_pos += yyleng;
  yylval.sval = yytext;
  
  return VAR_ID; 
}

\+  { LEX_VPRINT("ADD \n"); gCur_pos += yyleng; return ADD; }
\-  { LEX_VPRINT("SUB \n"); gCur_pos += yyleng; return SUB; }
\/  { LEX_VPRINT("DIV \n"); gCur_pos += yyleng; return DIV; }
\*  { LEX_VPRINT("MUL \n"); gCur_pos += yyleng; return MUL; }

\(  { LEX_VPRINT("OPEN_BR_RND \n"); gCur_pos += yyleng; return OPEN_BR_RND; }
\)  { LEX_VPRINT("CLOS_BR_RND \n"); gCur_pos += yyleng; return CLOS_BR_RND; }

\{  { LEX_VPRINT("OPEN_BR_CRVD \n"); gCur_pos += yyleng; return OPEN_BR_CRVD; }
\}  { LEX_VPRINT("CLOS_BR_CRVD \n"); gCur_pos += yyleng; return CLOS_BR_CRVD; }

[[:space:]]+ { gCur_pos += yyleng; } /* Ignore whitespaces. */
.|\\n lexical_error(yytext);

%%
