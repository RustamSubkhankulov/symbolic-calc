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

__attribute((noreturn)) static void lexical_error(const char* yytext)
{
  fprintf(stderr, "Lexical error. Unexpected token: %s \n", yytext);
  exit(EXIT_FAILURE);
}

#ifdef VERBOSE_LEX
#define LEX_VERBOSE_PRINT(...) do { fprintf(stderr, __VA_ARGS__); } while(0);
#else
#define LEX_VERBOSE_PRINT(...)
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

sin  { LEX_VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = SIN;  return STD_FUNC; }
cos  { LEX_VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = COS;  return STD_FUNC; }
tg   { LEX_VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = TG;   return STD_FUNC; }
ctg  { LEX_VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = CTG;  return STD_FUNC; }
sqrt { LEX_VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = SQRT; return STD_FUNC; }

PI  { LEX_VERBOSE_PRINT("STD_CONST: %s \n", yytext); yylval.ival = PI;  return STD_CONST; }
EXP { LEX_VERBOSE_PRINT("STD_CONST: %s \n", yytext); yylval.ival = EXP; return STD_CONST; }

{NUMINT} { 

  LEX_VERBOSE_PRINT("NUMINT: %s \n", yytext); 
  yylval.ival = atoi(yytext);
  return NUMINT; 
}

{NUMFLT} { 

  LEX_VERBOSE_PRINT("NUMFLT: %s \n", yytext); 
  yylval.fval = atof(yytext);
  return NUMFLT; 
}

{VAR_ID} { 

  LEX_VERBOSE_PRINT("VAR_ID: %s \n", yytext);
  yylval.sval = yytext;
  return VAR_ID; 
}

\+  { LEX_VERBOSE_PRINT("ADD \n"); return ADD; }
\-  { LEX_VERBOSE_PRINT("SUB \n"); return SUB; }
\/  { LEX_VERBOSE_PRINT("DIV \n"); return DIV; }
\*  { LEX_VERBOSE_PRINT("MUL \n"); return MUL; }

\(  { LEX_VERBOSE_PRINT("OPEN_BR_RND \n"); return OPEN_BR_RND; }
\)  { LEX_VERBOSE_PRINT("CLOS_BR_RND \n"); return CLOS_BR_RND; }

\{  { LEX_VERBOSE_PRINT("OPEN_BR_CRVD \n"); return OPEN_BR_CRVD; }
\}  { LEX_VERBOSE_PRINT("CLOS_BR_CRVD \n"); return CLOS_BR_CRVD; }

[[:space:]]+ {} /* Ignore whitespaces. */
\\n lexical_error(yytext);

%%
