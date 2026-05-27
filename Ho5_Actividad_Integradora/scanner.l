%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"

int line_number = 1;

extern YYSTYPE yylval;
%}

%option noyywrap

%%

"//".*                          { /* Comentario de una línea - ignorar */ }
"\n"                            { line_number++; }
[ \t\r]+                        { /* Espacios en blanco */ }

"#include"                      { return INCLUDE; }
"#define"                       { return DEFINE; }
"int"                           { return INT; }
"func"                          { return FUNC; }
"return"                        { return RETURN; }
"if"                            { return IF; }

"+"                             { return PLUS; }
"-"                             { return MINUS; }
"*"                             { return MULT; }
"/"                             { return DIV; }

"("                             { return LPAREN; }
")"                             { return RPAREN; }
"{"                             { return LBRACE; }
"}"                             { return RBRACE; }
";"                             { return SEMICOLON; }
","                             { return COMMA; }
"="                             { return ASSIGN; }
"<"                             { return LT; }
">"                             { return GT; }
"."                             { return DOT; }

\"[^\"]*\"                      { 
                                  yylval.str = strdup(yytext);
                                  return STRING; 
                                }

[0-9]+                          { 
                                  yylval.num = atoi(yytext);
                                  return NUMBER; 
                                }

[a-zA-Z_][a-zA-Z0-9_]*          { 
                                  yylval.str = strdup(yytext);
                                  return IDENTIFIER; 
                                }

.                               { 
                                  fprintf(stderr, "Error léxico en línea %d: carácter '%s' no reconocido\n", 
                                          line_number, yytext);
                                }

%%
