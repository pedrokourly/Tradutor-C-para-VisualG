%{
   #include <stdio.h>

   // incluindo as definicoes de tokens e tipos usados na gramatica da calculadora
   #include "calculadora.tab.h"
%}

 // definicao de macros para usos repetidos nas expressoes regulares
numero          [0-9]+\.?|[0-9]*\.[0-9]+ 

saida           "sair"|"quit"|"fim"|"halt"|"fui"|"exit"

%%

"+"             { return ADD;  }
"-"             { return SUB;  }
"*"             { return MUL;  }
"/"             { return DIV;  }
"^"             { return POW;  }
"sqrt"|"raizq"  { return SQRT; }
"("             { return OPAR; }
")"             { return CPAR; }
"!"             { return FATORIAL; }

{saida}         { return QUIT; }

{numero}        { yylval.d = atof(yytext);
                  // printf("[DEBUG] %lf\n", yylval); // apenas para depuracao...
                  return NUM;
                }

\n              { // printf("[DEBUG] EOL\n"); // apenas para depuracao...
                  return EOL;
                }

"//".*          { /* ignore comments */ }

[ \t]*          { /* ignore white spaces */}

.               { printf("Caracter desconhecido: %c\n", *yytext); }

%%

