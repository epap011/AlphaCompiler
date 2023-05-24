#include "avm_stack.h"
#include "instructions.h"
#include "parse_binfile.h"

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;

int main(int argc, char** argv){

    FILE* bin_file = NULL;

    if(argc != 2){
        printf("Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }
    else if(!(bin_file = fopen(argv[1], "rb"))){
          fprintf(stderr, "Could not open input file: %s\n", argv[1]);
          exit(EXIT_FAILURE);
    }

    parse_bin_file(bin_file);

    avm_initstack();
}

