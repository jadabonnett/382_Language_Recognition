// lexical analyzer suitable for Scripture Reference Parser assignment
//
// returns tokens D (sequence of digits), N (sequence of letters), EOF
// individual characters ';', ':', ','. '(', ')', '-'
// also return '\n' and '\r'
// all other characters do not fit grammar and are returned as ERR

#include "tokens.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int lookahead;
char value[20];
FILE *file;

int next() {
    int t;
    int ctr=0;
    t = getc(file);
    if (t != EOF) {
        while(t==' ' || t=='\t') t = getc(file);
        if(isalpha(t)) {
            // have N - get rest
            value[ctr++]=t;
            t=getc(file);
            while(isalpha(t)) {
                value[ctr++]=t;
                t=getc(file);
            }
            value[ctr]='\0';
            ungetc(t,file);
            return N;
        }
        if(isdigit(t)) {
            value[ctr++]=t;
            t=getc(file);
            while(isdigit(t)) {
                value[ctr++]=t;
                t=getc(file);
            }
            value[ctr]='\0';
            ungetc(t,file);
            return D;
        }
        if (t==';' || t==':' || t==',' || t=='(' || t==')' || t=='-' ||
            t=='\n' || t=='\r') return t;
        return ERR;


    }
    else return EOF;

}

bool d(){
    if(lookahead == 2){
        lookahead = next();
        return true;
    }return false;
}
bool T(){
    if(lookahead == '(' ){
        lookahead = next();
        if(lookahead == N){
            lookahead = next();
            if(lookahead == ')'){
                return true;
            }return false;
        }return false;
    }return true;
    // check if (N) || NULL
}
bool L(){
    if(d()){
        lookahead = next();
        if(lookahead == '-'){
            lookahead = next();
            if(d()){
                return true;
            }return false;
        }return false;
    }return true;
    //check if D-D
}
bool V(){
    if(L() && (next()==',')){
        lookahead = next();
        if(V()){
            return true;
        }return false;
    }return false;
}
bool C(){
    return d();
}
bool X(){
    if(C()) {
        if (next() == ':') {
            lookahead = next();
            if (V()) {
                return true;
            }return false;
        }return true;
    }return false;
}
bool R(){
    if(X() && next() == ';'){
        lookahead = next();
        if(R()){
            return true;
        }return false;
    }return true;
    //check if X;R HERE
}
bool n(){
    return(lookahead == N);
}
bool O(){
    if (lookahead == 2) {
        if (value[1] == '\0') {
            return true;
        }return false;
    }return false;
    //check if digit or null
}
bool B(){
    if(O() && n()){
        return true;
    }return false;
}
bool S(){
    if(B() && R() && T()){
        return true;
    }return false;
}

int main(){
    file = fopen("/src/test.txt", "r");
    //printf(file);
    lookahead = next();
    while(!EOF){
        if(S()){
            printf("Valid statement");
        }else{ printf("Not valid statement");}
    }

    fclose(file);
    return 0;
}

// main function for testing only - remove before use

//int main() {
//  int lookahead;
//
//  while((lookahead=next())!=EOF) {
//    if(lookahead==D) printf("D{%s}",value);
//    else {
//      if(lookahead==N) printf("N{%s}",value);
//      else {
//        if(lookahead==ERR) printf("*ERR*");
//	else printf("%c",lookahead);
//      }
//    }
//
//  }
//  printf("\n");
//}



