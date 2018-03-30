#include <stdio.h>
#include "parser.h"

int parse(char *file){
    FILE *f;
    char line[LINE_SIZE];
    char element_type;
    char name[STRING_SIZE], terminal_a[STRING_SIZE], terminal_b[STRING_SIZE], terminal_c[STRING_SIZE];
    int i = 0, line_counter = 0;

    // Open netlist file for reading
    f = fopen(file, "r");

    if(f == NULL){
        fprintf(stderr, "ERROR: Could not open netlist\n");
        return 1;
    }

    // Keep reading the next line
    while(fgets(line, sizeof(line), f) != NULL){
        line_counter++;

        // Ignore the first line because it`s reserved for commentaries
        if(line_counter == 1){
            continue;
        }

        // Check if it's a commentary
        if(line[i] == '*'){
            continue;
        }

        // Since the program is case insensitive convert the first letter to uppercase
        if(line[i] >= 'a' && line[i] <= 'z'){
		    line[i] = line[i] - 'a' + 'A';
        }

        // These elements share the same structure
        if(line[i] == 'R' || line[i] == 'C' || line[i] == 'L' || line[i] == 'V' || line[i] == 'I'){
            element_type = line[i];
        }
        printf(line);
    }

    return 0;
}