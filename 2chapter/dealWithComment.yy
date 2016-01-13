%option noyywrap
%{
/* You Looks Like Shit!
example 2.20 in page 84.
*/
#include <stdio.h>
#include <string.h>
void transUpper(char* s){
    int len = strlen(s);
    int i;
    for(i=0;i<len;i++){
        if(s[i]>='a' && s[i]<='z') s[i] += 'A'-'a';
    }
}
%}
comm1  {cmm1kw}.*\n
cmm1kw "//"

comm2 {cmbegin}(.|\n)*{cmend}
cmbegin "/*"
cmend "*/"

a "*"
b "/"

comm_nest {b}*({a}*~({a}|{b}){b}*)*{a}*

reserved "if"|"else"|"then"|"while"|"include"|"return"
%%
{comm1} {
    transUpper(yytext);
    printf("[catch]:%s", yytext);
    }
{comm2} {
    printf("===This para was eaten by me!===");
}
{comm_nest} {printf("+++NEST+++");}
{reserved} {transUpper(yytext);printf("%s",yytext);}
%%
main()
{yylex();return 0;}
