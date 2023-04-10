#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define bool  int
#define true  1
#define false 0


void open(char * filename);
void close();
int  get();
void unget();

int  peek_token();
void next_token();
bool match_token(int expect);
void match_any_token();
void match_all_to_end_of_line();

bool atom();
bool multexpr();
bool expr();
bool stat();
void prog();

///////////////////////////////////////////
//  FILE-RELATED FUNCTIONS

FILE *fp;
void open(char * filename) {
    fp = fopen(filename, "rt");
    next_token(); // prime lexer
}
void close() {
    fclose(fp);
}
int get() {
    return fgetc(fp);
}
void unget() {
    fseek(fp, -1, SEEK_CUR);
}


///////////////////////////////////////////
//  LEXER DATA AND FUNCTIONS

#define MAX_TOKEN  20

#define TOKEN_ERR  -2
#define TOKEN_EOF  -1
#define TOKEN_ID    1
#define TOKEN_INT   2
#define TOKEN_NL    3

int line = 1;

int lookahead;
char value[MAX_TOKEN + 1] = {0};

int peek_token() {
    return lookahead;
}

void next() {
    int t;
    int ctr = 0;

    value[0] = '\0';

    do {
        t = get();
    } while(t == ' ' || t == '\t');

    if(t == EOF) {
        lookahead = TOKEN_EOF;
        return;
    }

    if(isalpha(t)) {
        lookahead = TOKEN_ID;
        while(isalpha(t)) {
            value[ctr++] = t;
            t = get();
        }
        value[ctr] = '\0';
        if(t != EOF) unget();
        return;
    }

    if(isdigit(t)) {
        lookahead = TOKEN_INT;
        while(isdigit(t)) {
            value[ctr++] = t;
            t = get();
        }
        value[ctr] = '\0';
        if(t != EOF) unget();
        return;
    }

    if(t == '\r') {
        t = get();
        if(t == '\n') {
            lookahead = TOKEN_NL;
        } else {
            lookahead = TOKEN_ERR;
            if(t != EOF) unget();
        }
        return;
    }
    if(t == '\n') {
        lookahead = TOKEN_NL;
        return;
    }

    if(t == '=' || t == '+' || t == '-' || t == '*' || t == '(' || t == ')') {
        lookahead = t;
        return;
    }

    lookahead = TOKEN_ERR;
}

bool match_token(int expect) {
    if(expect != peek_token()) {
        printf("Syntax error on line %d: expected %d but saw %d\n", line, expect, peek_token());
        return false;
    }
    if(expect == TOKEN_NL) line++;
    // printf("Matched token: line=%d type=%d char=%c value=%s\n", line, expect, expect, value);
    next_token();
    return true;
}

void match_any_token() {
    match_token(peek_token());
}

void match_all_to_end_of_line() {
    // printf("Burning the rest of tokens until end of line or file...\n");
    while(peek_token() != TOKEN_NL && peek_token() != TOKEN_EOF) {
        match_any_token();
    }
}



///////////////////////////////////////////
//  PARSER FUNCTIONS

bool d(){
    if(lookahead == 2){
        lookahead = next();
        return true;
    }return false;
}
bool T(){
    if(lookahead == '(' ){
        lookahead = next();
        if(lookahead == 1){
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
    return(lookahead == 1);
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

// bool atom() {
//     // printf("matching atom... %d\n", peek_token());
//     if(peek_token() == TOKEN_INT) {
//         match_token(TOKEN_INT);
//     } else if(peek_token() == TOKEN_ID) {
//         match_token(TOKEN_ID);
//     } else {
//         if(!match_token('(')) return false;
//         if(!expr())     return false;
//         if(!match_token(')')) return false;
//     }
//     return true;
// }

// bool multexpr() {
//     // printf("matching multexpr... %d\n", peek_token());
//     if(!atom()) return false;
//     while(peek_token() == '*') {
//         match_token('*');
//         if(!atom()) return false;
//     }
//     return true;
// }

// bool expr() {
//     // printf("matching expr... %d\n", peek_token());
//     if(!multexpr()) return false;
//     while(peek_token() == '+' || peek_token() == '-') {
//         match_any_token();
//         if(!multexpr()) return false;
//     }
//     return true;
// }

// bool stat() {
//     // printf("matching stat... %d\n", peek_token());
//     if(peek_token() == TOKEN_ID) {
//         if(!match_token(TOKEN_ID)) return false;
//         if(!match_token('=')) return false;
//         if(!expr()) return false;
//     } else {
//         if(!expr()) return false;
//     }
//     return true;
// }

// void prog() {
//     if(!stat()) {
//         printf("Error on line %d\n", line);
//         match_all_to_end_of_line();
//     } else {
//         printf("Line %d is good\n", line);
//     }
//     while(peek_token() == TOKEN_NL) {
//         match_token(TOKEN_NL);
//         if(!stat()) {
//             printf("Error on line %d\n", line);
//             match_all_to_end_of_line();
//         } else {
//            printf("Line %d is good\n", line);
//         }
//     }
//     if(!match_token(TOKEN_EOF)) {
//         printf("Error on line %d\n", line);
//         printf("  Expected EOF\n");
//         printf("  Exiting!\n");
//     }
// }


///////////////////////////////////////////
//  MAIN

int main(int argc, char ** argv) {
    open("inputs/test.txt");
    S();
    close();
}