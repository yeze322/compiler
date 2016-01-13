%option noyywrap
%{
#include <stdio.h>
#include <string.h>
int count = 0;
void addCount(){++count;}
%}

alpha [a-zA-Z]
digit [0-9]
word ({alpha}|{digit})+
%%
{word} {
    addCount();
    printf("======[%s]======",yytext);
    }
%%
main()
{yylex();printf("total words = [%d]\n",count);return 0;}
