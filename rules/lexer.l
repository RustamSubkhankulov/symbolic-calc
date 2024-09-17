/* Options. */
%option noyywrap nounput noinput

/* Includes. */
%top {
  #include <stdio.h>
  #include "lexer.h"
}

/* Definitions. */
%{

__attribute((noreturn)) static void lexical_error(const char* yytext)
{
  fprintf(stderr, "Lexical error. Unexpected token: [%s] \n", yytext);
  exit(EXIT_FAILURE);
}

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

sin      printf("STD_FUNC %s \n", yytext);
cos      printf("STD_FUNC %s \n", yytext);
tg       printf("STD_FUNC %s \n", yytext);
ctg      printf("STD_FUNC %s \n", yytext);
sqrt     printf("STD_FUNC %s \n", yytext);

PI       printf("STD_CONST %s \n", yytext);
EXP      printf("STD_CONST %s \n", yytext);

{NUMINT} printf("NUMINT %s \n", yytext);
{NUMFLT} printf("NUMFLT %s \n", yytext); 

{VAR_ID} printf("VAR_ID %s \n", yytext);

\+       printf("ADD \n");
\-       printf("SUB \n");
\/       printf("DIV \n");
\*       printf("MUL \n");
\&       printf("AND \n");
\^       printf("XOR \n");
\~       printf("NEG \n");
\|       printf("OR \n");

\(       printf("PUNCT_SYMB %s \n", yytext);
\)       printf("PUNCT_SYMB %s \n", yytext);
\{       printf("PUNCT_SYMB %s \n", yytext);
\}       printf("PUNCT_SYMB %s \n", yytext);

--.*     { }

[[:space:]]+
.|\n lexical_error(yytext);

%%
