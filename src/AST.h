#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tipos de nós da árvore sintática abstrata (AST) */
typedef enum {
    /* Programa */
    AST_PROGRAM,
    
    /* Declarações */
    AST_VAR_DECL,
    AST_VAR_LIST,
    AST_FUNC_DECL,
    AST_PROC_DECL,
    AST_PARAM,
    AST_PARAM_LIST,
    
    /* Comandos */
    AST_STMT_LIST,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_REPEAT,
    AST_FOR,
    AST_FOR_STEP,
    AST_SWITCH,
    AST_CASE,
    AST_CASE_LIST,
    AST_DEFAULT_CASE,
    AST_RETURN,
    AST_BREAK,
    AST_ASSIGN,
    
    /* I/O */
    AST_READ,
    AST_WRITE,
    AST_WRITELN,
    AST_WRITE_PARAM,
    
    /* Expressões binárias */
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_INT_DIV,
    AST_POWER,
    AST_AND,
    AST_OR,
    AST_XOR,
    AST_EQ,
    AST_NEQ,
    AST_LT,
    AST_GT,
    AST_LTE,
    AST_GTE,
    
    /* Expressões unárias */
    AST_NEG,
    AST_NOT,
    
    /* Chamada de função */
    AST_FUNC_CALL,
    AST_ARG_LIST,
    
    /* Literais e identificadores */
    AST_NUMBER,
    AST_FLOAT,
    AST_STRING,
    AST_CHAR,
    AST_BOOLEAN,
    AST_IDENTIFIER,
    
    /* Tipos */
    AST_TYPE
} ASTNodeType;

/* Estrutura do nó da AST */
typedef struct ASTNode {
    ASTNodeType type;
    int line;  /* linha do código fonte */
    
    union {
        /* Para literais */
        int int_value;
        float float_value;
        char *string_value;
        char char_value;
        int bool_value;
        
        /* Para tipos e identificadores */
        struct {
            int type_token;  /* INTEIRO, REAL, etc */
        } type_spec;
        
        struct {
            char *name;
        } identifier;
        
        /* Para declaração de variável */
        struct {
            struct ASTNode *id_list;  /* lista de identificadores */
            struct ASTNode *type;     /* tipo */
        } var_decl;
        
        /* Para lista de identificadores ou variáveis */
        struct {
            char *name;
            struct ASTNode *next;
        } var_list;
        
        /* Para parâmetro */
        struct {
            char *name;
            struct ASTNode *type;
            struct ASTNode *next;
        } param;
        
        /* Para função/procedimento */
        struct {
            char *name;
            struct ASTNode *params;
            struct ASTNode *return_type;  /* NULL para procedimento */
            struct ASTNode *var_decls;
            struct ASTNode *body;
        } func_decl;
        
        /* Para atribuição */
        struct {
            char *var_name;
            struct ASTNode *expr;
        } assign;
        
        /* Para operações binárias */
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;
        
        /* Para operações unárias */
        struct {
            struct ASTNode *operand;
        } unary;
        
        /* Para IF */
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_body;
            struct ASTNode *else_body;  /* NULL se não houver SENAO */
        } if_stmt;
        
        /* Para WHILE */
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_stmt;
        
        /* Para REPEAT */
        struct {
            struct ASTNode *body;
            struct ASTNode *condition;
        } repeat_stmt;
        
        /* Para FOR */
        struct {
            char *var;
            struct ASTNode *start;
            struct ASTNode *end;
            struct ASTNode *step;  /* NULL se não houver PASSO */
            struct ASTNode *body;
        } for_stmt;
        
        /* Para SWITCH */
        struct {
            struct ASTNode *expr;
            struct ASTNode *cases;
            struct ASTNode *default_case;
        } switch_stmt;
        
        /* Para CASE */
        struct {
            struct ASTNode *value;
            struct ASTNode *stmts;
            struct ASTNode *next;  /* próximo case */
        } case_stmt;
        
        /* Para chamada de função */
        struct {
            char *name;
            struct ASTNode *args;
        } func_call;
        
        /* Para READ */
        struct {
            struct ASTNode *var_list;
        } read_stmt;
        
        /* Para WRITE/WRITELN */
        struct {
            struct ASTNode *expr_list;
        } write_stmt;
        
        /* Para parâmetro de WRITE com formatação */
        struct {
            struct ASTNode *expr;
            int width;         /* -1 se não especificado */
            int precision;     /* -1 se não especificado */
            struct ASTNode *next;
        } write_param;
        
        /* Para lista de expressões */
        struct {
            struct ASTNode *expr;
            struct ASTNode *next;
        } expr_list;
        
        /* Para lista de comandos */
        struct {
            struct ASTNode *stmt;
            struct ASTNode *next;
        } stmt_list;
        
        /* Para programa */
        struct {
            char *name;
            struct ASTNode *var_decls;
            struct ASTNode *func_decls;
            struct ASTNode *body;
        } program;
        
    } data;
} ASTNode;

/* Funções de criação de nós */

/* Programa */
ASTNode *ast_create_program(char *name, ASTNode *var_decls, ASTNode *func_decls, ASTNode *body);

/* Declarações */
ASTNode *ast_create_var_decl(ASTNode *id_list, ASTNode *type);
ASTNode *ast_create_var_list(char *name, ASTNode *next);
ASTNode *ast_create_func_decl(char *name, ASTNode *params, ASTNode *return_type, ASTNode *var_decls, ASTNode *body);
ASTNode *ast_create_param(char *name, ASTNode *type, ASTNode *next);
ASTNode *ast_create_type(int type_token);

/* Comandos */
ASTNode *ast_create_stmt_list(ASTNode *stmt, ASTNode *next);
ASTNode *ast_create_if(ASTNode *condition, ASTNode *then_body, ASTNode *else_body);
ASTNode *ast_create_while(ASTNode *condition, ASTNode *body);
ASTNode *ast_create_repeat(ASTNode *body, ASTNode *condition);
ASTNode *ast_create_for(char *var, ASTNode *start, ASTNode *end, ASTNode *step, ASTNode *body);
ASTNode *ast_create_switch(ASTNode *expr, ASTNode *cases, ASTNode *default_case);
ASTNode *ast_create_case(ASTNode *value, ASTNode *stmts, ASTNode *next);
ASTNode *ast_create_return(ASTNode *expr);
ASTNode *ast_create_break(void);
ASTNode *ast_create_assign(char *var_name, ASTNode *expr);

/* I/O */
ASTNode *ast_create_read(ASTNode *var_list);
ASTNode *ast_create_write(ASTNode *expr_list, int is_writeln);
ASTNode *ast_create_write_param(ASTNode *expr, int width, int precision, ASTNode *next);

/* Expressões */
ASTNode *ast_create_binary_op(ASTNodeType op_type, ASTNode *left, ASTNode *right);
ASTNode *ast_create_unary_op(ASTNodeType op_type, ASTNode *operand);
ASTNode *ast_create_func_call(char *name, ASTNode *args);
ASTNode *ast_create_expr_list(ASTNode *expr, ASTNode *next);

/* Literais */
ASTNode *ast_create_number(int value);
ASTNode *ast_create_float(float value);
ASTNode *ast_create_string(char *value);
ASTNode *ast_create_char(char value);
ASTNode *ast_create_boolean(int value);
ASTNode *ast_create_identifier(char *name);

/* Utilitários */
void ast_print(ASTNode *node, int indent);
void ast_free(ASTNode *node);

/* Variável global para armazenar a raiz da AST */
extern ASTNode *ast_root;
extern int yylineno;

#endif /* AST_H */
