#ifndef POSTFIX_H
#define POSTFIX_H

typedef enum {
    OPERAND,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    ERROR
} TokenType;

typedef struct {
    TokenType type;
    char text[100];
    int lineno;
} Token;

void addToken(TokenType type, const char *text, int lineno);
int checkSyntax();
void printTokens();
void printSyntaxTree();
const char* tokenTypeToString(TokenType type);

#endif // POSTFIX_H
