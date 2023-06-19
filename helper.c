#include "helper.h"
#include <assert.h>


int set_variable(char* name, Variable *variables, int num_variables) {
    //printf("set_variable function activated\n");
    if (num_variables == 30){
        fprintf(stderr,"error: number of variables exceeds 30\n");
        exit(0);
    }
    for (int i = 0; i < num_variables; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            fprintf(stderr,"error: redefinition of variable %s\n",name);
            exit(0);
        }
    }
    variables[num_variables++].name = strdup(name);
    return num_variables;
}

int evaluate_expression(Node* node, Variable *variables, int num_variables) {
    if(!node){
        exit(0);
    }
    if (node->left == NULL && node->right == NULL) {
        for (int i = 0; i < num_variables; i++) {
            if (strcmp(variables[i].name, node->value) == 0) {
                return variables[i].value;
            }            
        }        
    }

    int left_value = 0;
    int right_value = 0;    
    if (node->left){
        left_value = evaluate_expression(node->left, variables, num_variables);
    }
    if (node->right){
        right_value = evaluate_expression(node->right, variables, num_variables);
    }

    if (strcmp(node->value, "+") == 0) {
        return left_value || right_value;
    } else if (strcmp(node->value, "*") == 0) {
        return left_value && right_value;
    } else if (strcmp(node->value, "'") == 0) {
        return !left_value;
    }
    assert(false);
    return 0;
}

Node* create_node(char* value, Node* left, Node* right){    
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = strdup(value);
    node->left = left;
    node->right = right;
    return node;
}

void print_solution(Variable *variables, int num_variables) {    
    for (int i = 0; i < num_variables; i++) {
        printf("%s=%c", variables[i].name, variables[i].value ? 'T' : 'F');
        if(i!=num_variables-1){
          printf(", ");
        }
    }
    printf("\n");
}

int set_permutations(Variable *variable_table, int num_variables, Node* root){    
    int totalPermutations = 1 << num_variables;
    int num_solutions = 0;
    
    if (num_variables == 0){
        printf("\n");
        return 1;
    }
    if (!root){        
        num_solutions = totalPermutations;        
    }
    
    for (int i = 0; i < totalPermutations; i++) {
        int temp = i;
        for (int j = 0; j < num_variables; j++) {
            variable_table[j].value = temp & 1;
            temp >>= 1;            
        }
        if (num_solutions == totalPermutations){
            print_solution(variable_table, num_variables);
        }
        else if (evaluate_expression(root, variable_table, num_variables)) {
            num_solutions++;
            print_solution(variable_table, num_variables);
        }
    }
    return num_solutions;
}


void print_tree(Node* tree){    
    if (!tree){
        return;
    }
    
    print_tree(tree->left);
    printf("%s ", tree->value);
    print_tree(tree->right);    
}
