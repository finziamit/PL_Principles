%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

void yyerror (char *);
int yylex();
int yyparse();

Node* root = NULL;


Variable variables[30];
int num_variables = 0;
%}

%union {
char variable[31];
Node* expr;
}

%start program
%type <expr> expression
%token <variable> VARIABLE
%token VAR
%token NOT AND OR LPAREN RPAREN

%left OR
%left AND
%right NOT

%%
program                 :
                        | statement program
                        ; 

statement               : VAR VARIABLE ';'{
                              num_variables = set_variable($2,variables, num_variables);
                          }
                        | expression ';'{
                            if(!root) root = $1;
                            else{
                                root = create_node("*", root, $1);
                            }
                        }
                        ;

expression              :expression NOT{
                            $$ = create_node("'", (Node*)$1, NULL);
                        }
                        | LPAREN expression RPAREN{
                            $$ = $2;
                        }
                        | expression AND expression{
                            $$ = create_node("*" , (Node*)$1, (Node*)$3);
                        }
                        | expression OR expression{
                            $$ = create_node("+", (Node*)$1, (Node*)$3);
                        }                        
                        | VARIABLE{
                            Node* node = NULL;
                            for (int i=0; i<num_variables;i++){
                                if (strcmp(variables[i].name, $1) == 0){
                                    node = create_node($1, NULL, NULL);
                                    $$ = node;
                                    break;
                                }
                            }
                            if (!node){
                                fprintf(stderr, "error: variable %s not defined\n",$1);
                                exit(0);
                            }   
                        }
                        ;

%%

void yyerror(char* s) {fprintf(stderr, "error: syntax error\n"); exit(0);}

int main(){
    yyparse();    
    //print_tree(root);    // should be deleted. only for testing
    //printf("\n");
    int num_solutions = 0;
    num_solutions = set_permutations(variables, num_variables, root);
    printf("Number of solutions is %d\n", num_solutions);
    return 0;
}
