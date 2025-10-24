%{
    #include "symbol.h" // Inclua o arquivo de cabeçalho para a tabela de símbolos

    // Definição da estrutura para a tabela de símbolos
    Simbolo * symbol_table = NULL; // Ponteiro para a tabela de símbolos

    int current_scope = 0; // 0 = global, 1 = local
    
    void yyerror(const char *s); // Declaração da função de erro do Bison
    extern int yylex(void); // Declaração da função do scanner, gerada pelo Flex
    extern FILE *yyin;      // Para definir o arquivo de entrada
    extern char *yytext;    // Para acessar o texto do token atual
    extern int yylineno;    // Para rastrear o número da linha
    
    // Funções que são usadas antes de serem definidas no final do arquivo
    Simbolo* create_param(char *name, int type);
    void insert_function(char *name, int return_type, Simbolo *params);
    void insert_symbol(char *name, int type);
    Simbolo *find_symbol(char *name);
    Simbolo *find_symbol_in_scope(char *name, int scope);
    const char* type_to_string(int type);
    void print_symbol_table();
%}

// Definições de tipos de valores semânticos

%union {
    int      ival;       // Para números inteiros e tipos
    float    fval;       // Para valores float 
    char   * sval;       // Para identificadores e strings
    char     cval;       // Para caracteres
    // outros tipos que você usar
    Simbolo * sym;        // Para parâmetros individuais
    Simbolo * symlist;    // Para listas de parâmetros
}

 // Seção de definições de token.
 // O Bison precisa saber quais tokens ele pode receber do Flex.
%token <sval> IDENTIFIER
%token <ival> NUMBER
%token <fval> FLOAT_LITERAL
%token <cval> CHAR_LITERAL
%token <sval> STRING_LITERAL

/* --- TOKENS DE TIPO VISUALG --- */
%token INTEIRO
%token REAL
%token CARACTER
%token LITERAL
%token LOGICO
%token VERDADEIRO FALSO

/* --- TOKENS DE CONTROLE VISUALG --- */
%token SE ENTAO SENAO FIMSE
%token ENQUANTO FACA FIMENQUANTO
%token REPITA ATE
%token PARA DE PASSO FIMPARA
%token ESCOLHA CASO OUTROCASO FIMESCOLHA
%token INTERROMPA
%token RETORNE

/* --- OPERADORES VISUALG --- */
%token PLUS MINUS TIMES DIVIDE ASSIGN EQUAL NEQ LT GT LTE GTE
%token INT_DIVIDE POWER
%token E OU NAO XOU

/* --- ESTRUTURA E PONTUAÇÃO --- */
%token LPAREN RPAREN LBRACKET RBRACKET COMMA COLON
%token ALGORITMO FIMALGORITMO VAR INICIO
%token FUNCAO FIMFUNCAO PROCEDIMENTO FIMPROCEDIMENTO

/* --- I/O --- */
%token LEIA ESCREVA ESCREVAL

/* --- FUNÇÕES INTERNAS (Declaradas, mas não usadas na gramática de expressão) --- */
%token ALEATORIO ABS ARCCOS ARCSEN ARCTAN ARQUIVO ASC
%token COMPR COPIA COS COTAN CRONOMETRO DEBUG ECO EXP
%token GRAUPRAD INT_FUNC LOG LOGN MAIUSC MINUSC
%token NUMPCARAC PAUSA PI POS QUAD RADPGRAU RAIZQ
%token RAND RANDI SEN TIMER TAN

// Definição dos tipos de valores semânticos para as regras
%type <ival> type_specifier // Tipo de dado (int, float, etc.)
%type <sym> parameter_declaration
%type <symlist> parameter_list
%type <symlist> identifier_list // Para "id1, id2: tipo"

// Seção de precedência de operadores (do menor para o maior)
%right ASSIGN
%left OU XOU
%left E
%nonassoc EQUAL NEQ LT GT LTE GTE // não-associativo
%left PLUS MINUS
%left TIMES DIVIDE INT_DIVIDE
%right POWER
%right NAO UMINUS // Operadores unários (precedência alta)


 // Definição da gramática
%%

 // A regra de início da gramática.
program: 
    ALGORITMO STRING_LITERAL
    declaracao_variaveis
    declaracao_subrotinas
    INICIO
    statement_list
    FIMALGORITMO
;

// Bloco de declaração de variáveis (VAR)
declaracao_variaveis:
    /* vazio */
    | VAR variable_declaration_list
;

variable_declaration_list:
    variable_declaration
    | variable_declaration_list variable_declaration
;

// Declaração de variável no formato VisuAlg: id1, id2 : tipo
variable_declaration:
    identifier_list COLON type_specifier {
        // Itera a lista de identificadores ($1) e insere cada um
        // com o tipo especificado ($3)
        Simbolo* current = $1;
        while(current) {
            insert_symbol(current->name, $3); 
            
            Simbolo* temp = current;
            current = current->next;
            free(temp->name); // Libera o nome duplicado
            free(temp);       // Libera o nó da lista
        }
    }
;

// Lista de identificadores (para declaração)
identifier_list:
    IDENTIFIER { 
        $$ = create_param($1, 0); // Reutiliza create_param para criar um nó
        free($1); 
    }
    | identifier_list COMMA IDENTIFIER {
        Simbolo* newNode = create_param($3, 0);
        free($3);
        
        Simbolo* list = $1;
        while(list->next) list = list->next; // Vai até o fim da lista
        list->next = newNode;
        $$ = $1; // Retorna o início da lista
    }
;

// Bloco de declaração de funções e procedimentos
declaracao_subrotinas:
    /* vazio */
    | declaracao_subrotinas function_declaration
    | declaracao_subrotinas procedure_declaration
;

// Especificador de tipo
type_specifier:
      INTEIRO     { $$ = INTEIRO; }
    | REAL        { $$ = REAL; }
    | CARACTER    { $$ = CARACTER; }
    | LITERAL     { $$ = LITERAL; }
    | LOGICO      { $$ = LOGICO; }
;

// Lista de parâmetros de função/procedimento
parameter_list:
      /* vazio */ { $$ = NULL; }
    | parameter_declaration { $$ = $1; }
    | parameter_list COMMA parameter_declaration {
        // Adiciona $3 ao final da lista $1
        Simbolo* list = $1;
        while(list->next) list = list->next;
        list->next = $3;
        $$ = $1;
    }
;

// Declaração de parâmetro individual: id : tipo
parameter_declaration:
    IDENTIFIER COLON type_specifier {
        $$ = create_param($1, $3); // Cria o símbolo do parâmetro
        free($1);
        // NÃO insere na tabela de símbolos aqui.
        // A função/procedimento fará isso ao entrar no escopo.
    }
;

// Declaração de função
function_declaration:
    FUNCAO IDENTIFIER LPAREN parameter_list RPAREN COLON type_specifier
    {
        // Ação 1: Inserir a função na tabela (escopo global)
        // e mudar para o escopo local
        insert_function($2, $7, $4); // $2=nome, $7=tipo, $4=params
        current_scope = 1; // Entra no escopo local
        
        // Ação 2: Inserir os parâmetros no escopo local
        Simbolo *p = $4;
        while (p) {
            insert_symbol(p->name, p->type);
            p = p->next;
        }
        free($2);
    }
    declaracao_variaveis // Variáveis locais
    INICIO
    statement_list
    FIMFUNCAO
    {
        current_scope = 0; // Volta para escopo global
        // TODO: Limpar tabela de símbolos do escopo local
    }
;

// Declaração de procedimento
procedure_declaration:
    PROCEDIMENTO IDENTIFIER LPAREN parameter_list RPAREN
    {
        // Ação 1: Inserir procedimento e mudar escopo
        insert_function($2, 0, $4); // Usa tipo 0 (void) para procedimento
        current_scope = 1; // Entra no escopo local
        
        // Ação 2: Inserir parâmetros no escopo local
        Simbolo *p = $4;
        while (p) {
            insert_symbol(p->name, p->type);
            p = p->next;
        }
        free($2);
    }
    declaracao_variaveis // Variáveis locais
    INICIO
    statement_list
    FIMPROCEDIMENTO
    {
        current_scope = 0; // Volta para escopo global
        // TODO: Limpar tabela de símbolos do escopo local
    }
;


 // Lista de comandos (statements)
statement_list:
    /* vazio */
    | statement_list statement
;

statement:
    /* =================================================================== */
    /* === MUDANÇA PRINCIPAL AQUI ===                                    === */
    /* Trocamos 'assignment_statement' por 'expression'.                 */
    /* 'expression' já inclui atribuições, chamadas de função (MUDACOR)   */
    /* e identificadores simples (LIMPATELA).                            */
    /* =================================================================== */
    expression
    | if_statement
    | while_statement
    | repita_statement
    | para_statement
    | escolha_statement
    | io_statement
    | RETORNE expression
    | INTERROMPA
;

// Comandos de I/O
io_statement:
    LEIA LPAREN identifier_list RPAREN
    | ESCREVA LPAREN expression_list RPAREN
    | ESCREVAL LPAREN expression_list RPAREN
;

// Lista de expressões (para escreva, chamadas de função, etc.)
expression_list:
    expression
    | expression_list COMMA expression
;

// Comando 'se' (if)
if_statement:
    SE expression ENTAO
    statement_list
    FIMSE
    | SE expression ENTAO
    statement_list
    SENAO
    statement_list
    FIMSE
;

// Comando 'enquanto' (while)
while_statement:
    ENQUANTO expression FACA
    statement_list
    FIMENQUANTO
;

// Comando 'repita' (repeat-until)
repita_statement:
    REPITA
    statement_list
    ATE expression
;

// Comando 'para' (for)
// NOTA: O seu exemplo usa "DE 1 ATÉ 50", o parser espera um IDENTIFICADOR
// (ex: PARA i DE 1 ATE 50). O seu exemplo 'PARA Celcius DE...' está correto.
para_statement:
    PARA IDENTIFIER DE expression ATE expression FACA
    statement_list
    FIMPARA
    | PARA IDENTIFIER DE expression ATE expression PASSO expression FACA
    statement_list
    FIMPARA
;

// Comando 'escolha' (switch)
escolha_statement:
    ESCOLHA expression
    caso_list
    outrocaso_block
    FIMESCOLHA
;

caso_list:
    /* vazio */
    | caso_list CASO expression
      statement_list
;

outrocaso_block:
    /* vazio */
    | OUTROCASO statement_list
;


 // Expressões
expression:
    assignment_statement
    | logical_or_expression
;

assignment_statement:
    IDENTIFIER ASSIGN expression
    {
        Simbolo *s = find_symbol($1);
        if (s == NULL) {
            char error_msg[100];
            sprintf(error_msg, "Variável '%s' não declarada.", $1);
            yyerror(error_msg);
            YYABORT;
        }
        // TODO: Verificação de tipo
        free($1);
    }
;

logical_or_expression:
    logical_and_expression
    | logical_or_expression OU logical_and_expression
    | logical_or_expression XOU logical_and_expression
;

logical_and_expression:
    relational_expression
    | logical_and_expression E relational_expression
;

relational_expression:
    additive_expression
    | relational_expression EQUAL additive_expression
    | relational_expression NEQ additive_expression
    | relational_expression LT additive_expression
    | relational_expression GT additive_expression
    | relational_expression LTE additive_expression
    | relational_expression GTE additive_expression
;

additive_expression:
    multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
;

multiplicative_expression:
    power_expression
    | multiplicative_expression TIMES power_expression
    | multiplicative_expression DIVIDE power_expression
    | multiplicative_expression INT_DIVIDE power_expression
;

power_expression:
    unary_expression
    | unary_expression POWER power_expression // Certo-associativo
;

unary_expression:
    primary_expression
    | MINUS unary_expression %prec UMINUS
    | NAO unary_expression
;

primary_expression:
      NUMBER
    | FLOAT_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
    | VERDADEIRO
    | FALSO
    | IDENTIFIER {
        // Ação Semântica: Verifica se o identificador já foi declarado.
        Simbolo *sym = find_symbol($1);
        if (sym == NULL) {
            // NOTA: Comandos como LIMPATELA e MUDACOR
            // vão falhar aqui se não estiverem na tabela de símbolos.
            // Precisamos adicionar funções built-in na tabela.
            // Por agora, vamos permitir, mas avisar.
            // fprintf(stderr, "Aviso: Identificador '%s' não declarado (assumindo função built-in).\n", $1);
        }
        free($1);
    }
    | IDENTIFIER LPAREN expression_list RPAREN // Chamada de função
    | IDENTIFIER LPAREN RPAREN // Chamada de função sem args
    | LPAREN expression RPAREN
;


%%

// Funções C de suporte para o parser
int main(int argc, char **argv) {

    #ifdef COMPILER_DEBUG 
    if(COMPILER_DEBUG) printf("[DEBUG] parametros = %d\n", argc);
    #endif
    
    FILE *file = NULL;
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            perror("Não foi possível abrir o arquivo");
            return 1;
        }
        yyin = file;
    }
    
    printf("Iniciando a análise...\n");
    printf("Analisando o arquivo: %s\n", argc > 1 ? argv[1] : "entrada padrão");

    // Inicia o processo de parsing
    if (yyparse() == 0) {
        printf("Análise sintática bem-sucedida!\n");
    } else {
        printf("Análise sintática falhou.\n");
    }

    // Imprime a tabela de símbolos ao final da análise
    printf("\n\nAnálise concluída. Tabela de Símbolos:\n");
    print_symbol_table();

    if (file) {
        fclose(file);
    }

    return 0;
}

// Função de erro para o Bison.
void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s. Próximo a: '%s'\n", yylineno, s, yytext);
}

// Funções para manipulação da Tabela de Símbolos

void insert_symbol(char *name, int type) {
    // Implementação simples de lista encadeada.
    // Verifica se o símbolo já existe no escopo atual
    Simbolo * existing = find_symbol_in_scope(name, current_scope);
    if (existing != NULL) {
        fprintf(stderr, "Erro semântico: Identificador '%s' já declarado neste escopo (linha %d).\n", name, yylineno);
        exit(1);
    }
    
    Simbolo * new_symbol = (Simbolo *) malloc(sizeof(Simbolo));

    if (! new_symbol) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    new_symbol->name = strdup(name);
    if (! new_symbol->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    new_symbol->type = type;
    new_symbol->scope = current_scope; // variavel global/local
    new_symbol->is_function = 0;       // por padrão, é uma variável
    new_symbol->params = NULL;         // não é uma função, então sem parâmetros
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
}

Simbolo *find_symbol(char *name) {
    // Procura primeiro no escopo local, depois no global
    Simbolo *s = find_symbol_in_scope(name, 1); // Local
    if (s) return s;
    s = find_symbol_in_scope(name, 0); // Global
    return s;
}

Simbolo * find_symbol_in_scope(char *name, int scope) {
    Simbolo * current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->scope == scope) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

const char* type_to_string(int type) {
    switch (type) {
        case INTEIRO:   return "INTEIRO";
        case REAL:      return "REAL";
        case CARACTER:  return "CARACTER";
        case LITERAL:   return "LITERAL";
        case LOGICO:    return "LOGICO";
        case 0:         return "PROCEDIMENTO"; // Nosso "void"
        default:        return "desconhecido";
    }
}

void print_symbol_table() {
    Simbolo *current = symbol_table;
    printf("\n\nTabela de Símbolos:\n");
    printf("%-15s\t%-15s\t%s\t%s\t%s\n", "Nome", "Tipo", "Escopo", "Categoria", "Parâmetros");
    printf("--------------------------------------------------------------------------\n");
    while (current != NULL) {
        if (current->is_function) {
            printf("%-15s\t%-15s\t%s\tfunção\t\t", current->name, type_to_string(current->type), current->scope == 0 ? "global" : "local");
            Simbolo *p = current->params;
            while (p) {
                printf("%s:%s ", p->name, type_to_string(p->type));
                p = p->next;
            }
            printf("\n");
        } else {
            printf("%-15s\t%-15s\t%d\tvariavel\n", current->name, type_to_string(current->type), current->scope);
        }
        current = current->next;
    }
}

void insert_function(char *name, int return_type, Simbolo *params) {
    if (find_symbol_in_scope(name, 0)) { // Funções só podem ser globais
        fprintf(stderr, "Erro: função/procedimento '%s' já declarado.\n", name);
        exit(1);
    }
    
    Simbolo *func = malloc(sizeof(Simbolo));
    
    if (! func) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    func->name = strdup(name);
    if (! func->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    func->type = return_type;
    func->scope = current_scope; // Deve ser 0 (global)
    func->is_function = 1;
    func->params = params;
    func->next = symbol_table;
    symbol_table = func;
}

Simbolo* create_param(char *name, int type) {
    Simbolo *param = malloc(sizeof(Simbolo));
    if (! param) { 
        fprintf(stderr, "malloc failed\n"); 
        exit(1); 
    }

    param->name = strdup(name);
    if (! param->name) { 
        fprintf(stderr, "strdup failed\n"); 
        exit(1); 
    }

    param->type = type;
    param->scope = 1; // Parâmetros são sempre escopo local
    param->is_function = 0;
    param->params = NULL;
    param->next = NULL;
    return param;
}