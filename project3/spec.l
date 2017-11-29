/*
 * Peter Nguyen
 * CSCI 371 - Project 3
 * Due: Dec. 4, 2017
 * Lexer for a Mini-Language
 */

%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

 /* Reserved words */
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

 /* Variables */
[[:alpha:]][[:alnum:]_%&]* { return 100; }

 /* Integers and floats */
[[:digit:]]+   |
\.[[:digit:]]+ |
[[:digit:]]+\. |
[[:digit:]]+\.[[:digit:]]+ { return 200; }

 /* Math and relational operators */
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

 /* Miscellaneous characters */
";"  { return 401; }
","  { return 402; }
":=" { return 403; }
":"  { return 404; }
"?"  { return 405; }
"^"  { return 406; }

 /* Whitespace */
[[:space:]]+ ;

 /* Unknown */
. { return 600; }

%%

void main() {
    int tokentype;
    while (tokentype = yylex())
        printf("%d\n", tokentype);
}
