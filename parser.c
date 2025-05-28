// parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define LTD_VALUE 123  // Replace with your actual last three digits of ID

// Token types
typedef enum {
    T_IF, T_ELSE, T_WHILE,
    T_LBRACE, T_RBRACE, T_LPAREN, T_RPAREN,
    T_SEMICOLON, T_PLUS, T_MINUS, T_MUL, T_DIV,
    T_EQ, T_NEQ, T_LT, T_GT, T_LE, T_GE,
    T_NUMBER, T_IDENTIFIER, T_LTD, T_END, T_INVALID
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char text[MAX_TOKEN_LENGTH];
} Token;

// Lexer globals
const char* input;
int pos = 0;
Token currentToken;

void syntax_error(const char* message) {
    fprintf(stderr, "Syntax Error: %s at position %d\n", message, pos);
    exit(1);
}

char peek() {
    return input[pos];
}

char get() {
    return input[pos++];
}

void skip_whitespace() {
    while (isspace(peek())) get();
}

Token get_next_token() {
    skip_whitespace();

    char ch = peek();
    if (ch == '\0') return (Token){T_END, ""};

    if (isalpha(ch)) {
        char buffer[MAX_TOKEN_LENGTH] = {0};
        int i = 0;
        while (isalnum(peek())) buffer[i++] = get();
        buffer[i] = '\0';

        if (strcmp(buffer, "if") == 0) return (Token){T_IF, "if"};
        if (strcmp(buffer, "else") == 0) return (Token){T_ELSE, "else"};
        if (strcmp(buffer, "while") == 0) return (Token){T_WHILE, "while"};
        if (strcmp(buffer, "LTD") == 0) return (Token){T_LTD, "LTD"};

        return (Token){T_IDENTIFIER, strdup(buffer)};
    }

    if (isdigit(ch)) {
        char buffer[MAX_TOKEN_LENGTH] = {0};
        int i = 0;
        while (isdigit(peek())) buffer[i++] = get();
        buffer[i] = '\0';
        return (Token){T_NUMBER, strdup(buffer)};
    }

    get();
    switch (ch) {
        case '{': return (Token){T_LBRACE, "{"};
        case '}': return (Token){T_RBRACE, "}"};
        case '(': return (Token){T_LPAREN, "("};
        case ')': return (Token){T_RPAREN, ")"};
        case ';': return (Token){T_SEMICOLON, ";"};
        case '+': return (Token){T_PLUS, "+"};
        case '-': return (Token){T_MINUS, "-"};
        case '*': return (Token){T_MUL, "*"};
        case '/': return (Token){T_DIV, "/"};
        case '=': if (peek() == '=') { get(); return (Token){T_EQ, "=="}; }
                  break;
        case '!': if (peek() == '=') { get(); return (Token){T_NEQ, "!="}; }
                  break;
        case '<': if (peek() == '=') { get(); return (Token){T_LE, "<="}; }
                  else return (Token){T_LT, "<"};
        case '>': if (peek() == '=') { get(); return (Token){T_GE, ">="}; }
                  else return (Token){T_GT, ">"};
    }

    return (Token){T_INVALID, ""};
}

void match(TokenType expected) {
    if (currentToken.type == expected) {
        currentToken = get_next_token();
    } else {
        syntax_error("Unexpected token");
    }
}

// Forward declarations
void program();
void block();
void statement();
void if_statement();
void while_statement();
void condition();
void expression();
void term();
void factor();

void program() {
    block();
    if (currentToken.type != T_END) syntax_error("Extra content after program");
    printf("Valid: Program parsed successfully.\n");
}

void block() {
    match(T_LBRACE);
    while (currentToken.type != T_RBRACE) {
        statement();
    }
    match(T_RBRACE);
}

void statement() {
    if (currentToken.type == T_IF) {
        if_statement();
    } else if (currentToken.type == T_WHILE) {
        while_statement();
    } else {
        expression();
        match(T_SEMICOLON);
    }
}

void if_statement() {
    match(T_IF);
    match(T_LPAREN);
    condition();
    match(T_RPAREN);
    block();
    if (currentToken.type == T_ELSE) {
        match(T_ELSE);
        block();
    }
}

void while_statement() {
    match(T_WHILE);
    match(T_LPAREN);
    condition();
    match(T_RPAREN);
    block();
}

void condition() {
    expression();
    switch (currentToken.type) {
        case T_EQ: case T_NEQ: case T_LT: case T_GT: case T_LE: case T_GE:
            match(currentToken.type);
            break;
        default:
            syntax_error("Expected relational operator");
    }
    expression();
}

void expression() {
    term();
    while (currentToken.type == T_PLUS || currentToken.type == T_MINUS) {
        match(currentToken.type);
        term();
    }
}

void term() {
    factor();
    while (currentToken.type == T_MUL || currentToken.type == T_DIV) {
        match(currentToken.type);
        factor();
    }
}

void factor() {
    switch (currentToken.type) {
        case T_NUMBER:
            match(T_NUMBER);
            break;
        case T_IDENTIFIER:
            match(T_IDENTIFIER);
            break;
        case T_LTD:
            match(T_LTD);
            break;
        case T_LPAREN:
            match(T_LPAREN);
            expression();
            match(T_RPAREN);
            break;
        default:
            syntax_error("Expected number, identifier, LTD, or (expression)");
    }
}

int main() {
    // Sample input; replace or read from file as needed
    const char* sample_input =
        "{\n"
        "    if (a == LTD) {\n"
        "        while (b < 100) {\n"
        "            (a + b) * (b - LTD);\n"
        "        }\n"
        "    } else {\n"
        "        (x + y) * (a - b);\n"
        "    }\n"
        "}";
    input = sample_input;
    currentToken = get_next_token();
    program();
    return 0;
}
