%{
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "y.tab.h"
%}

%%
#.*                      ; /* ignore comment lines */
[ \t\n]                  ; /* Ignore whitespace */
var                      return VAR;
[a-zA-Z_][0-9a-zA-Z_]*   strcpy(yylval.variable, yytext); return VARIABLE;
\'                       return NOT;
\*                       return AND;
\+                       return OR;
\(                       return LPAREN;
\)                       return RPAREN;
.                        return yytext[0];
%%

int yywrap() {
    return 1;
}
