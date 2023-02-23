#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tokens.h"

#define MAX_LEXEME  1024
#define MAX_STATE   6
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define ISTOKEN(s)  ((s) >= TOKEN_STATE)

FILE* inputFile   = (FILE*)0;

int state         = 0;
int useLookAhead  = 0;

unsigned curr     = 0;
unsigned lineNo   = 0;

char lexeme[MAX_LEXEME];
char lookAhead = '\0';

int sf0 (char c); int sf1 (char c); int sf2 (char c); int sf3 (char c); int sf4 (char c); 
int sf5 (char c); int sf6 (char c); int sf7 (char c); int sf8 (char c); int sf9 (char c);
int sf10(char c); int sf11(char c); int sf12(char c);

void     resetLexeme(void); void checkLine(char c);
char     getNextChar(void); void retrack(char c);
unsigned gettoken2(void);   void extendLexeme(char c);
char*    getLexeme(void);   int  isAlpha(char c);
int      isSpace(char c);   int  isPancuation(char c);
int      isDigit(char c); 

int (*state_funcs[MAX_STATE+1])(char) = {&sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6, &sf7, &sf8, &sf9, &sf10, &sf11, &sf12};

int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "Error: wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    if((inputFile = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Error: can't open file \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    unsigned token;
    while((token = gettoken2()) != END_OF_FILE) {
        
    }
}

/* start state */
int sf0 (char c) {
    if(c == '<')   return STATE(1);
    if(c == '!')   return STATE(2);
    if(c == '=')   return STATE(3);
    if(c == '>')   return STATE(4);
    if(c == '+')   return STATE(5);
    if(c == '-')   return STATE(6);
    if(c == '*')   return STATE(7);
    if(c == '/')   return STATE(8);
    if(c == '%')   return STATE(9);
    if(isAlpha(c) || isDigit(c)) return STATE(10);
    if(isPancuation(c))          return STATE(11);
    if(isSpace(c)) {
        checkLine(c);
        return STATE(12);
    }
    return STATE(-1);
}

/* read < */
int sf1(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(LTE);
    }
    retrack(c);
    return TOKEN(LT);
}

/* read ! */
int sf2(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(NEQ);
    }
    retrack(c);
    return TOKEN(NOT);
}

/* read = */
int sf3(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(EQ);
    }
    retrack(c);
    return TOKEN(ASSIGN);
}

/* read > */
int sf4(char c) {
    if(c == '=') { 
        extendLexeme(c);
        return TOKEN(GTE);
    }
    retrack(c);
    return TOKEN(GT);
}

/* read + */
int sf5(char c) {
    if(c == '+') { 
        extendLexeme(c);
        return TOKEN(INC);
    }
    retrack(c);
    return TOKEN(PLUS);
}

/* read - */
int sf6(char c) {
    if(c == '-') { 
        extendLexeme(c);
        return TOKEN(DEC);
    }
    retrack(c);
    return TOKEN(MINUS);
}

/* read * */
int sf7(char c) {
    extendLexeme(c);
    return TOKEN(MUL);
}

/* read / */
int sf8(char c) {
    /* signle line comment OR block comment or division */
}

/* read % */
int sf9(char c) {
    extendLexeme(c);
    return TOKEN(MOD);
}

/* read identifier or number */
int sf10(char c) {
    if(isalpha(c) || isdigit(c)) {
        extendLexeme(c);
        return STATE(10);
    }
    retrack(c);
    return TOKEN(IDENT);
}

int sf11(char c) {
    if(isPancuation(c)) {
        extendLexeme(c);
        return STATE(11);
    }
    retrack(c);
    return TOKEN(PUNCTUATION);
}

/* read whitespace */
int sf12(char c) {
    if(isspace(c)) {
        checkLine(c);
        return STATE(11);
    }
    retrack(c);
    return STATE(0);
}

unsigned gettoken2() {
    state = 0;
    reserLexeme();
    while(1) {
        if(feof(inputFile)) return END_OF_FILE;

        char c  = getNextChar();
        
        state = (*state_funcs[state])(c);

        if(state == -1)    return NOSTYPE;           else
        if(istoken(state)) return state-TOKEN_SHIFT; else
        extendLexeme(c);
    }
}

char getNextChar() {
    if (useLookAhead) {
        useLookAhead = 0;
        return lookAhead;
    } else {
        assert(!feof(inputFile));
        return fgetc(inputFile);
    }
}

void resetLexeme(void) { curr = 0; }

char* getLexeme(void) {
    lexeme[curr] = '\0';
    return lexeme;
}

char getNextChar(FILE *inputFile) {
    if (useLookAhead) {
        useLookAhead = 0;
        return lookAhead;
    } else {
        assert(!feof(inputFile));
        return fgetc(inputFile);
    }
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

int isAlpha(char c) {
    return 1;
}

int isDigit(char c) {
    return 1;
}

int isSpace(char c) {
    return 1;
}

int isPunctuation(char c) {
    return 1;
}