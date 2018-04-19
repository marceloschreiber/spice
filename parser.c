#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "linked_list.h"

void parse(char *file){
    FILE *f;
    char line[LINE_SIZE];
    char element_type;
    char name[STRING_SIZE], terminal_a[STRING_SIZE], terminal_b[STRING_SIZE], terminal_c[STRING_SIZE], terminal_d[STRING_SIZE], value[STRING_SIZE];
    int i = 0, line_counter = 0;

    linked_list_t elements_linked_list;
    circuit_node_t circuit_nodes[ARRAY_SIZE];
    int circuit_nodes_length = 0;

    // Open netlist file for reading
    f = fopen(file, "r");

    if(f == NULL){
        fprintf(stderr, "ERROR: Could not open netlist\n");
        exit(1);
    }

    // Initialize the linked list with all the elements
    initialize(&elements_linked_list);

    // Keep reading the next line
    while(fgets(line, sizeof(line), f) != NULL){
        line_counter++;

        // Ignore the first line because it`s reserved for commentaries
        if(line_counter == 1){
            continue;
        }

        // Check if it's a commentary
        if(line[i] == '*'){
            //printf("Found a commentary, ignoring it\n");
            continue;
        }

        // Ignore blank lines
        if(line[i] == '\n'){
            continue; 
        }

        // Since the program is case insensitive convert the first letter to uppercase
        if(line[i] >= 'a' && line[i] <= 'z'){
		    line[i] = line[i] - 'a' + 'A';
        }

        // These elements share the same structure
        if(line[i] == 'R' || line[i] == 'C' || line[i] == 'L' || line[i] == 'V' || line[i] == 'I' || line[i] == 'D'){
            //printf("Found a resistor\n");
            element_type = line[i];
            line[i] = ' '; // sscanf will ignore this whitespace
            sscanf(line, "%s %s %s %s", name, terminal_a, terminal_b, value);

            double elementValue = convert_to_double(value);

            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_b);
            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_a);

            int terminal_a_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_a);
            int terminal_b_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_b);

            add_element(&elements_linked_list, element_type, name, terminal_a_ref, terminal_b_ref, -1, -1, elementValue);
        }else if(line[i] == 'E' || line[i] == 'F' || line[i] == 'G' || line[i] == 'H'){
            //printf("Found G\n");
            element_type = line[i];
            line[i] = ' '; // sscanf will ignore this whitespace
            sscanf(line, "%s %s %s %s %s %s", name, terminal_a, terminal_b, terminal_c, terminal_d, value);

            double elementValue = convert_to_double(value);

            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_a);
            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_b);
            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_c);
            circuit_nodes_length = link_node_label(circuit_nodes, circuit_nodes_length, terminal_d);

            int terminal_a_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_a);
            int terminal_b_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_b);
            int terminal_c_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_c);
            int terminal_d_ref = get_label_id(circuit_nodes, circuit_nodes_length, terminal_d);

            add_element(&elements_linked_list, element_type, name, terminal_a_ref, terminal_b_ref, terminal_c_ref, terminal_d_ref, elementValue);
        }else if(line[i] == 'Q' || line[i] == 'M'){
            //printf("Found M\n");
            element_type = line[i];
            line[i] = ' '; // sscanf will ignore this whitespace
            sscanf(line, "%s %s %s %s %s", name, terminal_a, terminal_b, terminal_c, value);
        }else{
            fprintf(stderr, "ERROR: Invalid element type at line %d\n", (line_counter));
            exit(1);
        }
    }

    printf("Lista encadeada de elementos:\n\n");
    print_netlist(&elements_linked_list);

    // Print the index/label list
    printf("\nVetor id do no => rotulo do no:\n\n");
    for(i= 0; i < circuit_nodes_length; i++){
        printf("No %d: %s\n", circuit_nodes[i].index, circuit_nodes[i].label);
    }
}

// Return the new array length after performing the operations
int link_node_label(circuit_node_t *circuit_nodes, int length, char *terminal){
    // Check if the label is already associated to an index
    for(int i = 0; i < length; i++){
        if(strcmp(circuit_nodes[i].label, terminal) == 0){
            return length;
        }
    }
    circuit_node_t new_circuit_node;
    new_circuit_node.index = length;
    strcpy(new_circuit_node.label, terminal);
    circuit_nodes[length] = new_circuit_node;
    return length + 1;
}

int get_label_id(circuit_node_t *circuit_nodes, int length, char *label){
    for(int i = 0; i < length; i++){
        if(strcmp(circuit_nodes[i].label, label) == 0){
            return circuit_nodes[i].index;
        }
    }
    return -1;
}

// Convert a string to double
double convert_to_double(char *s){
    return atof(s);
}