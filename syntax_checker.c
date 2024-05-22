#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"

#define MAX_TOKENS 100

Token tokens[MAX_TOKENS];
int tokenIndex = 0;

void addToken(TokenType type, const char *text, int lineno) {
    if (tokenIndex >= MAX_TOKENS) {
        fprintf(stderr, "Too many tokens\n");
        exit(1);
    }
    tokens[tokenIndex].type = type;
    strncpy(tokens[tokenIndex].text, text, 100);
    tokens[tokenIndex].lineno = lineno;
    tokenIndex++;
}

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case OPERAND: return "OPERAND";
        case ADD: return "ADD";
        case SUBTRACT: return "SUBTRACT";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void printTokens() {
    printf("\n\n Tokens:\n");
    for (int i = 0; i < tokenIndex; i++) {
        printf("Token %d: Type: %s, Text: %s, Line: %d\n", i, tokenTypeToString(tokens[i].type), tokens[i].text, tokens[i].lineno);
    }
}

int checkSyntax() {
    int stack = 0;
    printf("\n\n Checking syntax:\n");
    for (int i = 0; i < tokenIndex; i++) {
        printf("Processing token %d: %s\n", i, tokens[i].text);
        switch (tokens[i].type) {
            case OPERAND:
                stack++;
                break;
            case ADD:
            case SUBTRACT:
            case MULTIPLY:
            case DIVIDE:
                if (stack < 2) {
                    printf("Error at token %d (%s): Not enough operands for operator\n", i, tokens[i].text);
                    return 0;
                }
                stack--; 
                break;
            case ERROR:
                printf("Error at token %d (%s): Invalid token in postfix expression\n", i, tokens[i].text);
                return 0;
        }
    }
    if (stack == 1) {
        return 1; // Valid postfix expression
    } else {
        printf("Error: Too many operands\n");
        return 0;
    }
}

void printSyntaxTree() {
    printf("\n\n Syntax Tree:\n");
    for (int i = 0; i < tokenIndex; i++) {
        switch (tokens[i].type) {
            case OPERAND:
                printf("Operand: %s\n", tokens[i].text);
                break;
            case ADD:
                printf("Operator: +\n");
                break;
            case SUBTRACT:
                printf("Operator: -\n");
                break;
            case MULTIPLY:
                printf("Operator: *\n");
                break;
            case DIVIDE:
                printf("Operator: /\n");
                break;
            default:
                break;
        }
    }
}
