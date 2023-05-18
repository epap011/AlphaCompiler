#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "manage_parser.h"
#include "parser.h"
#include "quad.h"
    
extern FILE* yyout;
extern FILE* yyin;
extern int error_flag;
FILE* out_file;
SymbolTable* symTable;

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

    //initialize error file
    out_file = fopen("out_file.txt", "w+");
    fprintf(out_file, "\n-----------------------------\n\n");

    symTable = symbol_table_create();
    insert_lib_functions(symTable);
    yyparse();
    

    //debug
    printf("\n----------- Quads -----------\n");
    if(!error_flag){
        patch_jump_to_jump_labels();
        printQuads();
        quads_to_external_file();
    }

    symbol_table_print(symTable);
    fseek(out_file, 0, SEEK_SET);

    char ch;
    while ((ch = fgetc(out_file)) != EOF) {
        printf("%c", ch);
    }

    fclose(out_file);
}