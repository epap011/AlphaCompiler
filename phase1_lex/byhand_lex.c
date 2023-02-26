#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "tokens.h"

#define MAX_LEXEME  1024
#define MAX_STATE   17
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define ISTOKEN(s)  ((s) >= MAX_STATE)

#define END_OF_FILE 46
#define LETTER 47
#define DIGIT  48
#define SPACE  50

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

FILE* yyin  = (FILE*)0;
FILE* yyout = (FILE*)0;

int state        = 0;
int useLookAhead = 0;

unsigned curr    = 0;
unsigned lineNo  = 0;
unsigned tokenNo = 0;

char lexeme[MAX_LEXEME];
char lookAhead = '\0';

int sf0 (char c); int sf1 (char c); int sf2 (char c); int sf3 (char c); int sf4 (char c); 
int sf5 (char c); int sf6 (char c); int sf7 (char c); int sf8 (char c); int sf9 (char c);
int sf10(char c); int sf11(char c); int sf12(char c); int sf13(char c); int sf14(char c);
int sf15(char c); int sf16(char c);

void     resetLexeme(void); void checkLine(char c);
char     getNextChar(void); void retrack(char c);
unsigned gettoken2(void);   void extendLexeme(char c);
char*    getLexeme(void);   int  isPunctuation(char c);
int      isKeyword(char* s);

int (*state_funcs[MAX_STATE+1])(char) = {&sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6, &sf7, &sf8, &sf9, &sf10, &sf11, &sf12, &sf13, &sf14, &sf15, &sf16};

/*
int main(int argc, char** argv) {
    if(argc < 2) {
        //fprintf(stderr, "Error: wrong number of arguments\n");
        //exit(EXIT_FAILURE);
        yyin = stdin;
    }

    else if((yyin = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: can't open file \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    unsigned token;
    while((token = gettoken2()) != END_OF_FILE) {
        //printf();
    }
}
*/

int alpha_yylex(void *yylval){
    unsigned token;
    while((token = gettoken2()) != END_OF_FILE) {
        insert_token(yylval,lineNo,++tokenNo,lexeme,token,get_subtype(token,lexeme));
    }
    return 0;
}

/* start state */
int sf0 (char c) {
    if(c == '<')   return STATE(1);
    if(c == '!')   return STATE(2);
    if(c == '=')   return STATE(3);
    if(c == '>')   return STATE(4);
    if(c == '+')   return STATE(5);
    if(c == '-')   return STATE(6);
    if(c == '*') {
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    if(c == '%')   {
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    if(c == '/')   return STATE(7);
    if(isalpha(c)) return STATE(8);
    if(isdigit(c)) return STATE(9);
    if(c == '"')   return STATE(12);
    if(isPunctuation(c)) return STATE(10);
    if(isspace(c)) {
        checkLine(c);
        if(c == ' ' || c == '\n') return STATE(-1);
        return STATE(11);
    }
    return STATE(-1);
}

/* read < */
int sf1(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read ! */
int sf2(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read = */
int sf3(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read > */
int sf4(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read + */
int sf5(char c) {
    if(c == '+') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read - */
int sf6(char c) {
    if(c == '-') { 
        extendLexeme(c);
        return TOKEN(OPERATOR);
    }
    retrack(c);
    return TOKEN(OPERATOR);
}

/* read / */
int sf7(char c) {
    /* signle line */
    if(c == '/') {
        return STATE(13);
    }
    /* devision*/
    else if(c != '*') {
        retrack(c);
        return TOKEN(OPERATOR);
    }
    /* block comment */
    else {
        return STATE(14);
    }
    return -1;
}

/* read letter | digit */
int sf8(char c) {
    if(isalpha(c) || isdigit(c)) {
        return STATE(8);
    }
    retrack(c);
    if(isKeyword(getLexeme()) != -1) {
        return TOKEN(KEYWORD);
    }
    return TOKEN(IDENT);
}

/* read Digit */
int sf9(char c) {
    if(isdigit(c)) {
        return STATE(9);
    }
    else if(c == '.') {
        return STATE(16);
    }
    retrack(c);
    return TOKEN(NUMBER);
}

/* read punctuation */
int sf10(char c) {
    if(isPunctuation(c)) {
        retrack(c);
        return TOKEN(PUNCTUATION);
    }
    retrack(c);
    return TOKEN(PUNCTUATION);
}

/* read whitespace */
int sf11(char c) {
    if(isspace(c)) {
        checkLine(c);
        return STATE(11);
    }
    retrack(c);
    return STATE(0);
}

/* read " */
int sf12(char c) {
    if(c == '"' && lexeme[curr-1] != '\\') {
        return TOKEN(STRING);
    }
    return STATE(12);
}

int sf13(char c) {
    if(c == '\n') {
        return TOKEN(COMMENT);
    }
    return STATE(13);
}

int sf14(char c) {
    if(c == '*') {
        return STATE(15);
    }
    return STATE(14);
}

int sf15(char c) {
    if(c == '/') {
        return TOKEN(COMMENT);
    }
    else {
        return STATE(14);
    }
}

int sf16(char c) {
    if(isdigit(c)) {
        return STATE(16);
    }
    return TOKEN(NUMBER);
}

unsigned gettoken2() {
    state = 0;
    resetLexeme();
    while(1) {
        if(feof(yyin)) return END_OF_FILE;

        char c = getNextChar();
        //printf("[Before]state: %d | char: '%c'\n", state, c);
        state  = (*state_funcs[state])(c);
        //printf("[After]state: %d | char: '%c'\n", state, c);

        if(state == -1)         return NOSTYPE;          
        else if(ISTOKEN(state)) {
            if(state-TOKEN_SHIFT!=-1)printf(ANSI_COLOR_YELLOW "Recognized token: '%s' | token: %d\n" ANSI_COLOR_RESET, getLexeme(), state-TOKEN_SHIFT);
            return state-TOKEN_SHIFT;
        }
        else {
            if(state == 12 && curr > 0 && c == '"' && lexeme[curr-1] == '\\')
                extendLexeme(c);
            else if((state == 12 || state == 0) && c == '"') {
                continue;
            }
            else if(state == 13 && c == '/') {
                resetLexeme();
            }
            else if(state == 14 && c == '*') {
                resetLexeme();
            }
            else if(state == 15 && c == '*') {
                continue;
            }
            else if(state != 11) 
                extendLexeme(c);
        }
    }
}

char getNextChar() {
    if (useLookAhead) {
        useLookAhead = 0;
        return lookAhead;
    } else {
        assert(!feof(yyin));
        return fgetc(yyin);
    }
}

void resetLexeme(void) { curr = 0; }

char* getLexeme(void) {
    lexeme[curr] = '\0';
    return lexeme;
}

void retrack(char c) {
    assert(!useLookAhead);
    useLookAhead = 1;
    lookAhead    = c;
}

void checkLine(char c) {
    if (c == '\n') ++lineNo;
}

void extendLexeme(char c) {
    assert(curr < MAX_LEXEME-1);
    lexeme[curr++] = c;
}

int isPunctuation(char c) {
    if(c == 33 || c == 34 || c == 35 || c == 36 || c == 37 || c == 38 
    || c == 39 || c == 40 || c == 41 || c == 42 || c == 43 || c == 44 
    || c == 45 || c == 46 || c == 47 || c == 58 || c == 59 || c == 60 
    || c == 61 || c == 62 || c == 63 || c == 64 || c == 91 || c == 92 
    || c == 93 || c == 94 || c == 95 || c == 96 || c == 123 || c == 124 
    || c == 125 || c == 126)     
       return PUNCTUATION;
    return 0;
}

int isKeyword(char* string) {
    if(strcmp(string, "if") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "else") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "while") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "for") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "function") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "return") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "break") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "continue") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "and") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "not") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "or") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "local") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "true") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "false") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "return") == 0) {
        return KEYWORD;
    }
    if(strcmp(string, "nil") == 0) {
        return KEYWORD;
    }

    return -1;
}