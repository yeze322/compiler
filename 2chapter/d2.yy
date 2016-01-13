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

nestbegin "/*"
nestend "*/"
asterisk "*"
backslash "/"
notas [^"*"]
notab [^"*""/"]

trap {notas}*{asterisk}+{notab}
traploop {trap}*
trapend {asterisk}+{backslash}
comm_nest {nestbegin}{traploop}*{trapend}|{notas}*{trapend}

reserved "if"|"else"|"then"|"while"|"include"|"return"
%%
{comm1} {transUpper(yytext);printf("[catch]:%s", yytext);}
{comm_nest} printf("[CATCH=%s]\n",yytext);

%%
main()
{yylex();return 0;}
