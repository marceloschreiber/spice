#define STRING_SIZE 100

// Struct for a circuit element
typedef struct element_tt{
    char element_type;
    char name[STRING_SIZE];
    int terminal_a;
    int terminal_b;
    int terminal_c;
    int terminal_d;
    double valueDouble;
    char valueString[STRING_SIZE];
} element_t;

// Struct for a linked list node
typedef struct node_st
{
  element_t element;
  struct node_st *prox;
} node_t;

// Struct for the linked list
typedef struct linked_list_st
{
  node_t *ini;
} linked_list_t;

// Function declarations
void initialize(linked_list_t *l);
void destroy(linked_list_t *l);
void insert_at_end(linked_list_t *l, element_t element);

void add_element(linked_list_t *l, char element_type, char *name, int terminal_a, int terminal_b, int terminal_c, int terminal_d, double valueDouble, char *valueString);
void print_netlist(linked_list_t *l);