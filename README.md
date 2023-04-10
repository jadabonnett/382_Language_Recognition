# 382_Language_Recognition

This was aimed to help learn some various approaches for parsing sentences. 
The three used here are:
- Recursive Descent Parser (RDP) in C
- ANTLR Code and Java
- Regular Expression in Perl

This specific sentence type is on bible verses. 
The format can vary but the grammar looked like this:
S -> BRT
B -> ON
R -> X|X;R|null
X -> C|C:V
C -> D
V -> L|L,V
L -> D|D-D
T -> (N)|null
O -> digit|null
D -> digit|digit D
N -> letter|letter N
digit -> '0'..'9'
letter -> 'a'..'z''A'..'Z'

The intake is various files or lines of examples, and it will output whether they pass or fail, when there is a fail, it no longer continues through the file. 

