#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[]){
    
    // Check arguments and show usage
    if(argc < 2){
        printf("Usage: ./parser filename\n");
        exit(1);
    }

    // Parse input file
    parse(argv[1]);

    return 0;
}