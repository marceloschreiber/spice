#define LINE_SIZE 256
#define STRING_SIZE 100
#define ARRAY_SIZE 300

// Struct to link the int value of a node to its label
typedef struct circuit_node_tt{
    int index;
    char label[STRING_SIZE];
} circuit_node_t;

void parse(char *file);
int link_node_label(circuit_node_t *circuit_nodes, int length, char *terminal);
int get_label_id(circuit_node_t *circuit_nodes, int length, char *label);
double convert_to_double(char *str_value);