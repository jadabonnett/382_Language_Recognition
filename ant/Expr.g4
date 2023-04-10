grammar Expr;


s   : b r t ;
b   : o n;
r   : (x
    | x ';' r)?
    ;
x   : c
    |c ':' v
    ;
c   : d;
v   : l
    |l ',' v
    ;
l   : d
    | d '-' d
    ;
t   : ('('n')')?
    ;
o   : DIGIT?;
d   : DIGIT
    | DIGIT+
    ;
n   : LETTER
    | LETTER+
    ;

DIGIT: [0-9];
LETTER: [a-zA-Z]+;
WS      : [ \t]+ -> skip;
NEWLINE : '\r'? '\n' ;
//
//prog: stat+ EOF;
//
//stat: expr NEWLINE
//    | ID '=' expr NEWLINE
//    | NEWLINE
//    ;
//
//expr: multExpr (('+' | '-') multExpr)*
//    ;
//multExpr
//    : atom ('*' atom)*
//    ;
//atom: INT
//    | ID
//    | '(' expr ')'
//    ;
//
//ID      : [a-zA-Z]+ ;
//INT     : [0-9]+ ;
//NEWLINE : '\r'? '\n' ;
//WS      : [ \t]+ -> skip;