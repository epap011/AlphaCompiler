#include "avm_stack.h"
#include "instructions.h"
#include "parse_binfile.h"

int main(int argc, char** argv){

    if(argc != 2){
        printf("Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }

    FILE* bin_file = fopen(argv[1], "rb");
    parse_bin_file(bin_file);

    avm_initstack();
}
