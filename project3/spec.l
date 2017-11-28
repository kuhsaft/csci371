/*
 * Peter Nguyen
 * CSCI 371 - Project 3
 * Due:Dec. 4, 2017
 * Lexer for a Mini-Language
 */

%{
#include <stdio.h>
#include <stdlib.h>
%}

digit         [0-9]
letter        [a-zA-Z]

%%

"PROGRAM" { return 501; }
"BEGIN"   { return 502; }
"END"     { return 503; }
"IF"      { return 504; }
"THEN"    { return 505; }
"ELSE"    { return 506; }
"WHILE"   { return 507; }
"INTEGER" { return 508; }
"REAL"    { return 509; }
"FOR"     { return 510; }

{letter}({letter}|{digit}|_|%|&)* { return 100; }

{digit}+           |
{digit}+\.{digit}+ { return 200; }

"+"  { return 301; }
"-"  { return 302; }
"<"  { return 303; }
">"  { return 304; }
"="  { return 305; }
"!=" { return 306; }
"<=" { return 307; }
">=" { return 308; }
"&&" { return 309; }
"||" { return 310; }

";"  { return 401; }
","  { return 402; }
":=" { return 403; }
":"  { return 404; }
"?"  { return 405; }
"^"  { return 406; }


[ \n\t\r]+ ;

. { return 600; }

%%

void main() {
    int tokentype;
    while (tokentype = yylex())
        printf("%d\n", tokentype);
}
