%{
#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"

void yyerror(const char *s);
%}

%%

[0-9]+ { addToken(OPERAND, yytext, yylineno); }
"+"    { addToken(ADD, yytext, yylineno); }
"-"    { addToken(SUBTRACT, yytext, yylineno); }
"*"    { addToken(MULTIPLY, yytext, yylineno); }
"/"    { addToken(DIVIDE, yytext, yylineno); }
[ \t\n]   ; // Ignore whitespace
.      { addToken(ERROR, yytext, yylineno); }

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    YY_BUFFER_STATE buffer = yy_scan_string(argv[1]);
    yylex();
    yy_delete_buffer(buffer);

    printTokens();
    if (checkSyntax()) {
        printf("Valid expression\n");
        printSyntaxTree();
    } else {
        printf("Invalid expression\n");
    }

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
