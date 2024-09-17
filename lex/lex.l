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
#define VERBOSE_PRINT(...) do { printf(__VA_ARGS__); } while(0);
#else
#define VERBOSE_PRINT(...)
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

sin  { VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = SIN;  return STD_FUNC; }
cos  { VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = COS;  return STD_FUNC; }
tg   { VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = TG;   return STD_FUNC; }
ctg  { VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = CTG;  return STD_FUNC; }
sqrt { VERBOSE_PRINT("STD_FUNC: %s \n", yytext); yylval.ival = SQRT; return STD_FUNC; }

PI  { VERBOSE_PRINT("STD_CONST: %s \n", yytext); yylval.ival = PI;  return STD_CONST; }
EXP { VERBOSE_PRINT("STD_CONST: %s \n", yytext); yylval.ival = EXP; return STD_CONST; }

{NUMINT} { 

  VERBOSE_PRINT("NUMINT: %s \n", yytext); 
  yylval.ival = atoi(yytext);
  return NUMINT; 
}

{NUMFLT} { 

  VERBOSE_PRINT("NUMFLT: %s \n", yytext); 
  yylval.fval = atof(yytext);
  return NUMFLT; 
}

{VAR_ID} { 

  VERBOSE_PRINT("VAR_ID: %s \n", yytext);
  yylval.sval = yytext;
  return VAR_ID; 
}

\+  { VERBOSE_PRINT("ADD \n"); return ADD; }
\-  { VERBOSE_PRINT("SUB \n"); return SUB; }
\/  { VERBOSE_PRINT("DIV \n"); return DIV; }
\*  { VERBOSE_PRINT("MUL \n"); return MUL; }

\(  { VERBOSE_PRINT("OPEN_BR_RND \n"); return OPEN_BR_RND; }
\)  { VERBOSE_PRINT("CLOS_BR_RND \n"); return CLOS_BR_RND; }

\{  { VERBOSE_PRINT("OPEN_BR_CRVD \n"); return OPEN_BR_CRVD; }
\}  { VERBOSE_PRINT("CLOS_BR_CRVD \n"); return CLOS_BR_CRVD; }

[[:space:]]+ {} /* Ignore whitespaces. */
\\n lexical_error(yytext);

%%
