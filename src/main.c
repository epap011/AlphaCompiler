#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "symbol_table.h"

extern FILE* yyout;
extern FILE* yyin;

void symbol_table_print(SymbolTable * symTable);
void insert_lib_functions(SymbolTable * symTable);

int main(int argc, char** argv) {
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

    SymbolTable* symTable = symbol_table_create();
    insert_lib_functions(symTable);

    yyparse();

    symbol_table_print(symTable);
}