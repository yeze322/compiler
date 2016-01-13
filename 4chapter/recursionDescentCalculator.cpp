#include <stdio.h>
#include <stdlib.h>
/*Global char for take single word*/
char token;
/*stderr when meeting unruled character*/
void error(){fprintf(stderr, "Unmatch Happend!\n");exit(1);}
/*if single char was matched, take it away*/
void match(char expectToken){
    if(expectToken == token){
        //eat one char
        token = getchar();
    }else{
        error();
    }
}
int exp();
int term();
int factor();

int main(int argc, char**argv){
    int result;

    while(token = getchar()){
        int ret = exp();
        printf("The result is %d\n", ret);
    }
    return 0;
}

/*
#=== BNF type ===#
exp -> exp addop term | term
term -> term mulop factor | factor
factor -> (exp) | number

addop -> + | -
mulop -> *

#=== EBNF type ===#
exp = term {addop term}
term = factor {mulop factor}
factor = (exp) | number
 */

//exp = term {addop term}
int exp(){
    int ret = term();
    while(token == '+' || token == '-'){
        switch(token){
            case '+' :
                match('+');
                ret += term();
                break;
            case '-' : 
                match('-');
                ret -= term();
                break;
            default:
                error();
                break;
        }
    }
    return ret;
}

//term = factor {mulop factor}
int term(){
    int ret = factor();
    while(token == '*' || token == '/'){
        switch(token){
            case '*' :
                match('*');
                ret *= factor();
                break;
            case '/':
                match('/');
                ret /= factor();
                break;
            default :
                error();
                break;
        }
    }
    return ret;
}

//factor = (exp) | number
int factor(){
    int ret;
    if(token == '('){
        match('(');
        ret = exp();
        match(')');
    }else if(token <= '9' && token >= '0'){
        ungetc(token, stdin);
        scanf("%d", &ret);
        token = getchar();
    }else{
        error();
    }
    return ret;
}












