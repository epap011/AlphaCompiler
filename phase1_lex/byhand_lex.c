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
int  useLookAhead = 0;

unsigned curr     = 0;
unsigned lineNo   = 0;

char lexeme[MAX_LEXEME];
char lookAhead = '\0';

int sf0 (char c); int sf1 (char c); int sf2 (char c);
void     resetLexeme (void); void checkLine   (char c);
char     getNextChar (void); void retrack     (char c);
unsigned gettoken2   (void); void extendLexeme(char c);
char*    getLexeme   (void);

//int isalpha(char c); int isdigit(char c); int isspace(char c);

int (*state_funcs[MAX_STATE+1])(char) = {&sf0, &sf1, &sf2};

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
    while((token = gettoken()) != END_OF_FILE) {
        
    }
}

/* start state */
int sf0 (char c) {
    if(c == '<')   return STATE(1);
    if(c == '!')   return STATE(2);
    if(c == '=')   return STATE(3);
    if(c == '>')   return STATE(4);
    if(isalpha(c)) return STATE(5);
    if(isspace(c)) {
        checkLine(c);
        return STATE(6);
    }

    return STATE(-1);
}

int sf1(char c) {

}

int sf2(char c) {

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

// int isalpha(char c) {
//     return 1;
// }

// int isdigit(char c) {
//     return 1;
// }

// int isspace(char c) {
//     return 1;
// }