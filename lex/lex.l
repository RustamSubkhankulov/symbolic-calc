/* Options. */
%option noyywrap nounput noinput

/* Includes. */
%top {
  #include <stdio.h>
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
#define VERBOSE_LEX_PRINT(...) do { printf(__VA_ARGS__); } while(0);
#else
#define VERBOSE_LEX_PRINT(...)
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

sin|cos|tg|ctg|sqrt { VERBOSE_LEX_PRINT("STD_FUNC discovered: %s \n", yytext); return STD_FUNC; }

PI|EXP { VERBOSE_LEX_PRINT("STD_CONST discovered: %s \n", yytext); return STD_CONST; }

{NUMINT} { VERBOSE_LEX_PRINT("NUMINT discovered: %s \n", yytext); return NUMINT; }
{NUMFLT} { VERBOSE_LEX_PRINT("NUMFLT discovered: %s \n", yytext); return NUMFLT; } 

{VAR_ID} { VERBOSE_LEX_PRINT("VAR_ID discovered: %s \n", yytext); return VAR_ID; }

\+       { VERBOSE_LEX_PRINT("ADD discovered \n"); return ADD; }
\-       { VERBOSE_LEX_PRINT("SUB discovered \n"); return SUB; }
\/       { VERBOSE_LEX_PRINT("DIV discovered \n"); return DIV; }
\*       { VERBOSE_LEX_PRINT("MUL discovered \n"); return MUL; }
\&       { VERBOSE_LEX_PRINT("AND discovered \n"); return AND; }
\^       { VERBOSE_LEX_PRINT("XOR discovered \n"); return XOR; }
\~       { VERBOSE_LEX_PRINT("NOT discovered \n"); return NOT; }
\|       { VERBOSE_LEX_PRINT("OR discovered \n"); return OR; }

\(       { VERBOSE_LEX_PRINT("OPEN_BR_RND discovered \n"); return OPEN_BR_RND; }
\)       { VERBOSE_LEX_PRINT("CLOS_BR_RND discovered \n"); return CLOS_BR_RND; }

\{       { VERBOSE_LEX_PRINT("OPEN_BR_CRVD discovered \n"); return OPEN_BR_CRVD; }
\}       { VERBOSE_LEX_PRINT("CLOS_BR_CRVD discovered \n"); return CLOS_BR_CRVD; }

[[:space:]]+ {} /* Ignore whitespaces. */
\\n lexical_error(yytext);

%%
