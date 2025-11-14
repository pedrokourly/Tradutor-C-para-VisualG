
%{
  #define DEBUG 1  // habilita ( 1 ) ou desabilita ( 0 ) as mensagens de depuração

  // inclusao de bibliotecas C-ANSI
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <math.h>

  // Protótipo de yylex
  int yylex(void);
  // Protótipo de yyerror
  void yyerror(char *s);

  typedef unsigned long long ULONG; // definição de tipo para uso na função fatorial
  ULONG fatorial(long n);
%}


// redefinindo tipo da variavel global yylval (de int para double)
// %define api.value.type { double }

// forma alternativa de redefinir yylval, mas com mais possibilidades
%union {
  double d;
  // listar outros tipos permitidos para yylval
}

// definicao dos tokens
%token <d> NUM              // constante numerica
%token ADD 
%token SUB 
%token MUL
%token DIV 
%token POW                  // exponenciação ("^")
%token SQRT                 // raiz quadrada
%token FATORIAL
%token EOL                  // final de linha
%token OPAR CPAR            // parenteses
%token QUIT                 // finalizacao do programa

// definição de associatividade e nível de precedencia dos operadores
%left ADD SUB       // menor precedência
%left MUL DIV
%right POW 
%right SQRT        
%right FATORIAL     // maior precedencia

%type <d> exp fator termo // associando tipo aos não terminais das regras gramaticais

%start calcline

%%

calcline : 
         | calcline exp EOL    { printf("= %lf\n> ", $2); } // resultado da expressao digitada
         | calcline EOL        { printf("> "); }            // usuario pressiona tecla ENTER
         | calcline QUIT EOL   { return 0; }                // usuario informa comando de saida da calculadora
         | error EOL           { // expressao incorreta informada pelo usuario
                                 yyerror("redigite a ultima linha : ");
                                 yyerrok; /* recoloca o parser em modo normal de operacao */
                               }
         ;

exp : fator /* default : $$ = $1 */ 
    | exp ADD fator   { $$ = $1 + $3; if (DEBUG) printf("[DEBUG] soma\n"); } 
    | exp SUB fator   { $$ = $1 - $3; if (DEBUG) printf("[DEBUG] subtracao\n");} 
    | exp FATORIAL    { $$ = fatorial( $1 );  }
    ;

fator: termo       /* default : $$ = $1 */
     | fator MUL termo { $$ = $1 * $3; }
     | fator DIV termo { if ( $3 == 0 ) {
                            yyerror("divisao por zero!\nInforme outro valor");
                            yyerrok;
                         } else {
                            $$ = $1 / $3;
                         }
                       }
     | fator POW termo { $$ = pow($1, $3); }
     ;

termo: NUM                 { $$ = $1; }
     | OPAR exp CPAR       { $$ = $2; }
     | SQRT exp            { $$ = sqrt($2);  }
     ;

%%

/* Declaração de funções auxiliares */

int main(int argc, char **argv) {
     
     printf("Calculadora interativa\n");
     printf("> Para sair, digite: sair, quit, fim, halt, fui, exit\n");
     printf("> ");
     
     int r = yyparse();

     printf("Finalizando a calculadora!\n");

     return r;
}

void yyerror(char *s) {
   fprintf(stderr, "error: %s\n", s);
   //return 0;
}

ULONG fatorial(long n) {
     
     ULONG f = 1;
     int i;
     for(i = 1; i <= n; i++) {
          f = f * (ULONG) i;
     }
     return f;
}

