#include <stdio.h>
#include <stdlib.h>    
#include <string.h>
#include "stack.h"

int alpha_yylex(void* yylval);

extern FILE* yyout;
extern FILE* yyin;
extern Stack* stack;

int main(int argc, char** argv){
    if (argc == 2 || argc == 3) {
        if(!(yyin = fopen(argv[1], "r"))) {
          fprintf(stderr, "Could not open input file: %s\n", argv[1]);
          exit(EXIT_FAILURE);
        }
    }
    else if(argc < 2) {
        yyin = stdin;
    }
    else {
        fprintf(stderr, "Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }

    if(argc == 3) {
        if(!(yyout = fopen(argv[2], "w"))) {
          fprintf(stderr, "Could not open output file: %s\n", argv[2]);
          exit(EXIT_FAILURE);
        }
    }
    else {
        yyout = stdout;
    }

    stack = new_stack();
    //TokenList* token_list = new_token_list();
    alpha_yylex(NULL);
    //print_alpha_token_list(token_list, yyout);

    return 0;
}