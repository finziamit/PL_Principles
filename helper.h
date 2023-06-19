#ifndef HELPER_H
#define HELPER_H
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct variable{
    char* name;
    bool value;
}Variable;

typedef struct node {
    char* value;
    struct node* left;
    struct node* right;
}Node;

int set_variable(char* name, Variable *variables, int num_variables);

int evaluate_expression(Node* node, Variable *variables, int num_variables);

Node* create_node(char* value, Node* left, Node* right);

void print_solution(Variable *variables, int num_variables);

int set_permutations(Variable *variable_table, int num_variables, Node* root);

void print_tree(Node* tree);
#endif
