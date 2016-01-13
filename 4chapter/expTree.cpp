/*
To construct a expression tree.
Using the same theory : Top-down Parsing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
/* Node defination */
enum NodeType{ NUM, OPT,};
struct Node{
    Node *left;
    Node *right;
    char opt;
    int value;
    NodeType attri;
    bool showBraket;
    Node(): left(NULL), right(NULL), opt(0), value(0), attri(NUM), showBraket(false){}
};

void test(){
    Node* root = new Node();
    Node* child = new Node();
    root->left = child;
    root->right = child;
    root->attri = OPT;
    root->left->value = 1;
}
/*===== end =====*/

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
/*Functon Declaration*/
Node* exp();
Node* term();
Node* factor();
/*====Declaration End====*/

/*exp = term {addop term}*/
Node* exp(){
    Node* ret = term();
    while(token == '+' || token == '-'){
        Node *optRoot = new Node();
        optRoot->attri = OPT;
        optRoot->opt = token;
        optRoot->left = ret;

        match(token);
        optRoot->right = term();

        int lv = optRoot->left->value, rv = optRoot->right->value;
        switch(optRoot->opt){
        case '+' : optRoot->value = lv + rv; break;
        case '-' : optRoot->value = lv - rv; break;
        }
        ret = optRoot;
    }
    return ret;
}
/*term = factor {multiop factor}*/
Node* term(){
    Node *ret = factor();
    while(token == '*' || token == '/'){
        Node *optRoot = new Node();
        optRoot->attri = OPT;
        optRoot->opt = token;
        optRoot->left = ret;

        match(token);
        optRoot->right = factor();

        int lv = optRoot->left->value, rv = optRoot->right->value;
        switch(optRoot->opt){
        case '*' : optRoot->value = lv * rv; break;
        case '/' : optRoot->value = lv / rv; break;
        }
        ret = optRoot;
    }
    return ret;
}

/*factor = (exp) | number*/
Node *factor(){
    Node *ret = NULL;
    if(token == '('){
        match('(');
        ret = exp();
        ret->showBraket = true;
        match(')');
    }else if(token <= '9' && token >= '0'){
        ungetc(token, stdin);
        ret = new Node();
        ret->attri = NUM;
        scanf("%d", & ret->value);
        token = getchar();
    }else{
        error();
    }
    return ret;
}
void dfsPrint(Node *root){
    if(root == NULL) return;
    if(root->showBraket) putchar('(');

    dfsPrint(root->left);
    switch(root->attri){
        case OPT: putchar(root->opt);break;
        case NUM: printf("%d", root->value);break;
        default: error();
    }
    printf("(%d)", root->value);
    dfsPrint(root->right);

    if(root->showBraket) putchar(')');
}
int main(){
    token = getchar();
    Node* root = exp();
    dfsPrint(root);
    putchar('\n');
    printf("value = %d\n", root->value);
    return 0;
}












