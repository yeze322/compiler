%option noyywrap
%{
#include <stdio.h>
#include <string.h>
int lineno = 1;
%}

RESERVED_KW "read"|"write"|"repeat"|"end"|"until"|"if"|"else"|"then"
OPT ">"|"<"|":="|"<="|"="|";"|"*"|"-"|"+"

NUM [0-9]+
ID [a-zA-Z]+
COMM "{"[^}]*"}"
BLANK [' ''\t']
%%
{RESERVED_KW} {printf("	%d: ",lineno); printf("reserved word : %s\n", yytext);}
{ID} {printf("	%d: ",lineno); printf("ID, name = %s\n", yytext);}
{OPT} {printf("	%d: ",lineno); printf("operator: %s\n", yytext);}
{NUM} {printf("	%d: ",lineno); printf("NUM, val = %s\n", yytext);}
{COMM} {
    int len = strlen(yytext);
    int i;
    for(i=0;i<len;i++){
        if(yytext[i] == '\n') lineno++;
    }
}
{BLANK} {printf("");}
"\n" printf("%d :\n", ++lineno);
%%
main()
{yylex(); return 0;}
