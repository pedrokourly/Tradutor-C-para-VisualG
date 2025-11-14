#include "AST.h"

/* Variável global para armazenar a raiz da AST */
ASTNode *ast_root = NULL;

/* Função auxiliar para criar um nó */
static ASTNode *ast_create_node(ASTNodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó AST\n");
        exit(1);
    }
    node->type = type;
    node->line = yylineno;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

/* Programa */
ASTNode *ast_create_program(char *name, ASTNode *var_decls, ASTNode *func_decls, ASTNode *body) {
    ASTNode *node = ast_create_node(AST_PROGRAM);
    node->data.program.name = name ? strdup(name) : NULL;
    node->data.program.var_decls = var_decls;
    node->data.program.func_decls = func_decls;
    node->data.program.body = body;
    return node;
}

/* Declarações */
ASTNode *ast_create_var_decl(ASTNode *id_list, ASTNode *type) {
    ASTNode *node = ast_create_node(AST_VAR_DECL);
    node->data.var_decl.id_list = id_list;
    node->data.var_decl.type = type;
    return node;
}

ASTNode *ast_create_var_list(char *name, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_VAR_LIST);
    node->data.var_list.name = name ? strdup(name) : NULL;
    node->data.var_list.next = next;
    return node;
}

ASTNode *ast_create_func_decl(char *name, ASTNode *params, ASTNode *return_type, ASTNode *var_decls, ASTNode *body) {
    ASTNode *node = ast_create_node(return_type ? AST_FUNC_DECL : AST_PROC_DECL);
    node->data.func_decl.name = name ? strdup(name) : NULL;
    node->data.func_decl.params = params;
    node->data.func_decl.return_type = return_type;
    node->data.func_decl.var_decls = var_decls;
    node->data.func_decl.body = body;
    return node;
}

ASTNode *ast_create_param(char *name, ASTNode *type, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_PARAM);
    node->data.param.name = name ? strdup(name) : NULL;
    node->data.param.type = type;
    node->data.param.next = next;
    return node;
}

ASTNode *ast_create_type(int type_token) {
    ASTNode *node = ast_create_node(AST_TYPE);
    node->data.type_spec.type_token = type_token;
    return node;
}

/* Comandos */
ASTNode *ast_create_stmt_list(ASTNode *stmt, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_STMT_LIST);
    node->data.stmt_list.stmt = stmt;
    node->data.stmt_list.next = next;
    return node;
}

ASTNode *ast_create_if(ASTNode *condition, ASTNode *then_body, ASTNode *else_body) {
    ASTNode *node = ast_create_node(else_body ? AST_IF_ELSE : AST_IF);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_body = then_body;
    node->data.if_stmt.else_body = else_body;
    return node;
}

ASTNode *ast_create_while(ASTNode *condition, ASTNode *body) {
    ASTNode *node = ast_create_node(AST_WHILE);
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

ASTNode *ast_create_repeat(ASTNode *body, ASTNode *condition) {
    ASTNode *node = ast_create_node(AST_REPEAT);
    node->data.repeat_stmt.body = body;
    node->data.repeat_stmt.condition = condition;
    return node;
}

ASTNode *ast_create_for(char *var, ASTNode *start, ASTNode *end, ASTNode *step, ASTNode *body) {
    ASTNode *node = ast_create_node(step ? AST_FOR_STEP : AST_FOR);
    node->data.for_stmt.var = var ? strdup(var) : NULL;
    node->data.for_stmt.start = start;
    node->data.for_stmt.end = end;
    node->data.for_stmt.step = step;
    node->data.for_stmt.body = body;
    return node;
}

ASTNode *ast_create_switch(ASTNode *expr, ASTNode *cases, ASTNode *default_case) {
    ASTNode *node = ast_create_node(AST_SWITCH);
    node->data.switch_stmt.expr = expr;
    node->data.switch_stmt.cases = cases;
    node->data.switch_stmt.default_case = default_case;
    return node;
}

ASTNode *ast_create_case(ASTNode *value, ASTNode *stmts, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_CASE);
    node->data.case_stmt.value = value;
    node->data.case_stmt.stmts = stmts;
    node->data.case_stmt.next = next;
    return node;
}

ASTNode *ast_create_return(ASTNode *expr) {
    ASTNode *node = ast_create_node(AST_RETURN);
    node->data.unary.operand = expr;
    return node;
}

ASTNode *ast_create_break(void) {
    return ast_create_node(AST_BREAK);
}

ASTNode *ast_create_assign(char *var_name, ASTNode *expr) {
    ASTNode *node = ast_create_node(AST_ASSIGN);
    node->data.assign.var_name = var_name ? strdup(var_name) : NULL;
    node->data.assign.expr = expr;
    return node;
}

/* I/O */
ASTNode *ast_create_read(ASTNode *var_list) {
    ASTNode *node = ast_create_node(AST_READ);
    node->data.read_stmt.var_list = var_list;
    return node;
}

ASTNode *ast_create_write(ASTNode *expr_list, int is_writeln) {
    ASTNode *node = ast_create_node(is_writeln ? AST_WRITELN : AST_WRITE);
    node->data.write_stmt.expr_list = expr_list;
    return node;
}

ASTNode *ast_create_write_param(ASTNode *expr, int width, int precision, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_WRITE_PARAM);
    node->data.write_param.expr = expr;
    node->data.write_param.width = width;
    node->data.write_param.precision = precision;
    node->data.write_param.next = next;
    return node;
}

/* Expressões */
ASTNode *ast_create_binary_op(ASTNodeType op_type, ASTNode *left, ASTNode *right) {
    ASTNode *node = ast_create_node(op_type);
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

ASTNode *ast_create_unary_op(ASTNodeType op_type, ASTNode *operand) {
    ASTNode *node = ast_create_node(op_type);
    node->data.unary.operand = operand;
    return node;
}

ASTNode *ast_create_func_call(char *name, ASTNode *args) {
    ASTNode *node = ast_create_node(AST_FUNC_CALL);
    node->data.func_call.name = name ? strdup(name) : NULL;
    node->data.func_call.args = args;
    return node;
}

ASTNode *ast_create_expr_list(ASTNode *expr, ASTNode *next) {
    ASTNode *node = ast_create_node(AST_ARG_LIST);
    node->data.expr_list.expr = expr;
    node->data.expr_list.next = next;
    return node;
}

/* Literais */
ASTNode *ast_create_number(int value) {
    ASTNode *node = ast_create_node(AST_NUMBER);
    node->data.int_value = value;
    return node;
}

ASTNode *ast_create_float(float value) {
    ASTNode *node = ast_create_node(AST_FLOAT);
    node->data.float_value = value;
    return node;
}

ASTNode *ast_create_string(char *value) {
    ASTNode *node = ast_create_node(AST_STRING);
    node->data.string_value = value ? strdup(value) : NULL;
    return node;
}

ASTNode *ast_create_char(char value) {
    ASTNode *node = ast_create_node(AST_CHAR);
    node->data.char_value = value;
    return node;
}

ASTNode *ast_create_boolean(int value) {
    ASTNode *node = ast_create_node(AST_BOOLEAN);
    node->data.bool_value = value;
    return node;
}

ASTNode *ast_create_identifier(char *name) {
    ASTNode *node = ast_create_node(AST_IDENTIFIER);
    node->data.identifier.name = name ? strdup(name) : NULL;
    return node;
}

/* Utilitários */
static const char *ast_type_to_string(ASTNodeType type) {
    switch (type) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_VAR_DECL: return "VAR_DECL";
        case AST_VAR_LIST: return "VAR_LIST";
        case AST_FUNC_DECL: return "FUNC_DECL";
        case AST_PROC_DECL: return "PROC_DECL";
        case AST_PARAM: return "PARAM";
        case AST_STMT_LIST: return "STMT_LIST";
        case AST_IF: return "IF";
        case AST_IF_ELSE: return "IF_ELSE";
        case AST_WHILE: return "WHILE";
        case AST_REPEAT: return "REPEAT";
        case AST_FOR: return "FOR";
        case AST_FOR_STEP: return "FOR_STEP";
        case AST_SWITCH: return "SWITCH";
        case AST_CASE: return "CASE";
        case AST_DEFAULT_CASE: return "DEFAULT_CASE";
        case AST_RETURN: return "RETURN";
        case AST_BREAK: return "BREAK";
        case AST_ASSIGN: return "ASSIGN";
        case AST_READ: return "READ";
        case AST_WRITE: return "WRITE";
        case AST_WRITELN: return "WRITELN";
        case AST_WRITE_PARAM: return "WRITE_PARAM";
        case AST_ADD: return "ADD";
        case AST_SUB: return "SUB";
        case AST_MUL: return "MUL";
        case AST_DIV: return "DIV";
        case AST_INT_DIV: return "INT_DIV";
        case AST_POWER: return "POWER";
        case AST_AND: return "AND";
        case AST_OR: return "OR";
        case AST_XOR: return "XOR";
        case AST_EQ: return "EQ";
        case AST_NEQ: return "NEQ";
        case AST_LT: return "LT";
        case AST_GT: return "GT";
        case AST_LTE: return "LTE";
        case AST_GTE: return "GTE";
        case AST_NEG: return "NEG";
        case AST_NOT: return "NOT";
        case AST_FUNC_CALL: return "FUNC_CALL";
        case AST_ARG_LIST: return "ARG_LIST";
        case AST_NUMBER: return "NUMBER";
        case AST_FLOAT: return "FLOAT";
        case AST_STRING: return "STRING";
        case AST_CHAR: return "CHAR";
        case AST_BOOLEAN: return "BOOLEAN";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_TYPE: return "TYPE";
        default: return "UNKNOWN";
    }
}

void ast_print(ASTNode *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    printf("%s", ast_type_to_string(node->type));
    
    switch (node->type) {
        case AST_NUMBER:
            printf(": %d\n", node->data.int_value);
            break;
        case AST_FLOAT:
            printf(": %f\n", node->data.float_value);
            break;
        case AST_STRING:
            printf(": \"%s\"\n", node->data.string_value);
            break;
        case AST_CHAR:
            printf(": '%c'\n", node->data.char_value);
            break;
        case AST_BOOLEAN:
            printf(": %s\n", node->data.bool_value ? "VERDADEIRO" : "FALSO");
            break;
        case AST_IDENTIFIER:
            printf(": %s\n", node->data.identifier.name);
            break;
        case AST_VAR_LIST:
            printf(": %s\n", node->data.var_list.name);
            ast_print(node->data.var_list.next, indent);
            break;
        case AST_PROGRAM:
            printf(": %s\n", node->data.program.name);
            if (node->data.program.var_decls) {
                for (int i = 0; i < indent+1; i++) printf("  ");
                printf("VAR_DECLS:\n");
                ast_print(node->data.program.var_decls, indent+2);
            }
            if (node->data.program.func_decls) {
                for (int i = 0; i < indent+1; i++) printf("  ");
                printf("FUNC_DECLS:\n");
                ast_print(node->data.program.func_decls, indent+2);
            }
            if (node->data.program.body) {
                for (int i = 0; i < indent+1; i++) printf("  ");
                printf("BODY:\n");
                ast_print(node->data.program.body, indent+2);
            }
            break;
        case AST_VAR_DECL:
            printf("\n");
            ast_print(node->data.var_decl.id_list, indent+1);
            ast_print(node->data.var_decl.type, indent+1);
            break;
        case AST_FUNC_DECL:
        case AST_PROC_DECL:
            printf(": %s\n", node->data.func_decl.name);
            if (node->data.func_decl.params) ast_print(node->data.func_decl.params, indent+1);
            if (node->data.func_decl.return_type) ast_print(node->data.func_decl.return_type, indent+1);
            if (node->data.func_decl.var_decls) ast_print(node->data.func_decl.var_decls, indent+1);
            if (node->data.func_decl.body) ast_print(node->data.func_decl.body, indent+1);
            break;
        case AST_PARAM:
            printf(": %s\n", node->data.param.name);
            ast_print(node->data.param.type, indent+1);
            ast_print(node->data.param.next, indent);
            break;
        case AST_STMT_LIST:
            printf("\n");
            ast_print(node->data.stmt_list.stmt, indent+1);
            ast_print(node->data.stmt_list.next, indent);
            break;
        case AST_IF:
        case AST_IF_ELSE:
            printf("\n");
            for (int i = 0; i < indent+1; i++) printf("  ");
            printf("CONDITION:\n");
            ast_print(node->data.if_stmt.condition, indent+2);
            for (int i = 0; i < indent+1; i++) printf("  ");
            printf("THEN:\n");
            ast_print(node->data.if_stmt.then_body, indent+2);
            if (node->data.if_stmt.else_body) {
                for (int i = 0; i < indent+1; i++) printf("  ");
                printf("ELSE:\n");
                ast_print(node->data.if_stmt.else_body, indent+2);
            }
            break;
        case AST_WHILE:
            printf("\n");
            ast_print(node->data.while_stmt.condition, indent+1);
            ast_print(node->data.while_stmt.body, indent+1);
            break;
        case AST_REPEAT:
            printf("\n");
            ast_print(node->data.repeat_stmt.body, indent+1);
            ast_print(node->data.repeat_stmt.condition, indent+1);
            break;
        case AST_FOR:
        case AST_FOR_STEP:
            printf(": %s\n", node->data.for_stmt.var);
            ast_print(node->data.for_stmt.start, indent+1);
            ast_print(node->data.for_stmt.end, indent+1);
            if (node->data.for_stmt.step) ast_print(node->data.for_stmt.step, indent+1);
            ast_print(node->data.for_stmt.body, indent+1);
            break;
        case AST_SWITCH:
            printf("\n");
            ast_print(node->data.switch_stmt.expr, indent+1);
            ast_print(node->data.switch_stmt.cases, indent+1);
            if (node->data.switch_stmt.default_case) 
                ast_print(node->data.switch_stmt.default_case, indent+1);
            break;
        case AST_CASE:
            printf("\n");
            ast_print(node->data.case_stmt.value, indent+1);
            ast_print(node->data.case_stmt.stmts, indent+1);
            ast_print(node->data.case_stmt.next, indent);
            break;
        case AST_ASSIGN:
            printf(": %s\n", node->data.assign.var_name);
            ast_print(node->data.assign.expr, indent+1);
            break;
        case AST_READ:
            printf("\n");
            ast_print(node->data.read_stmt.var_list, indent+1);
            break;
        case AST_WRITE:
        case AST_WRITELN:
            printf("\n");
            ast_print(node->data.write_stmt.expr_list, indent+1);
            break;
        case AST_WRITE_PARAM:
            printf("\n");
            ast_print(node->data.write_param.expr, indent+1);
            ast_print(node->data.write_param.next, indent);
            break;
        case AST_FUNC_CALL:
            printf(": %s\n", node->data.func_call.name);
            ast_print(node->data.func_call.args, indent+1);
            break;
        case AST_ARG_LIST:
            printf("\n");
            ast_print(node->data.expr_list.expr, indent+1);
            ast_print(node->data.expr_list.next, indent);
            break;
        case AST_RETURN:
            printf("\n");
            ast_print(node->data.unary.operand, indent+1);
            break;
        case AST_NEG:
        case AST_NOT:
            printf("\n");
            ast_print(node->data.unary.operand, indent+1);
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_INT_DIV:
        case AST_POWER:
        case AST_AND:
        case AST_OR:
        case AST_XOR:
        case AST_EQ:
        case AST_NEQ:
        case AST_LT:
        case AST_GT:
        case AST_LTE:
        case AST_GTE:
            printf("\n");
            ast_print(node->data.binary.left, indent+1);
            ast_print(node->data.binary.right, indent+1);
            break;
        default:
            printf("\n");
            break;
    }
}

void ast_free(ASTNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_STRING:
            free(node->data.string_value);
            break;
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
        case AST_VAR_LIST:
            free(node->data.var_list.name);
            ast_free(node->data.var_list.next);
            break;
        case AST_PROGRAM:
            free(node->data.program.name);
            ast_free(node->data.program.var_decls);
            ast_free(node->data.program.func_decls);
            ast_free(node->data.program.body);
            break;
        case AST_VAR_DECL:
            ast_free(node->data.var_decl.id_list);
            ast_free(node->data.var_decl.type);
            break;
        case AST_FUNC_DECL:
        case AST_PROC_DECL:
            free(node->data.func_decl.name);
            ast_free(node->data.func_decl.params);
            ast_free(node->data.func_decl.return_type);
            ast_free(node->data.func_decl.var_decls);
            ast_free(node->data.func_decl.body);
            break;
        case AST_PARAM:
            free(node->data.param.name);
            ast_free(node->data.param.type);
            ast_free(node->data.param.next);
            break;
        case AST_STMT_LIST:
            ast_free(node->data.stmt_list.stmt);
            ast_free(node->data.stmt_list.next);
            break;
        case AST_IF:
        case AST_IF_ELSE:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_body);
            ast_free(node->data.if_stmt.else_body);
            break;
        case AST_WHILE:
            ast_free(node->data.while_stmt.condition);
            ast_free(node->data.while_stmt.body);
            break;
        case AST_REPEAT:
            ast_free(node->data.repeat_stmt.body);
            ast_free(node->data.repeat_stmt.condition);
            break;
        case AST_FOR:
        case AST_FOR_STEP:
            free(node->data.for_stmt.var);
            ast_free(node->data.for_stmt.start);
            ast_free(node->data.for_stmt.end);
            ast_free(node->data.for_stmt.step);
            ast_free(node->data.for_stmt.body);
            break;
        case AST_SWITCH:
            ast_free(node->data.switch_stmt.expr);
            ast_free(node->data.switch_stmt.cases);
            ast_free(node->data.switch_stmt.default_case);
            break;
        case AST_CASE:
            ast_free(node->data.case_stmt.value);
            ast_free(node->data.case_stmt.stmts);
            ast_free(node->data.case_stmt.next);
            break;
        case AST_ASSIGN:
            free(node->data.assign.var_name);
            ast_free(node->data.assign.expr);
            break;
        case AST_READ:
            ast_free(node->data.read_stmt.var_list);
            break;
        case AST_WRITE:
        case AST_WRITELN:
            ast_free(node->data.write_stmt.expr_list);
            break;
        case AST_WRITE_PARAM:
            ast_free(node->data.write_param.expr);
            ast_free(node->data.write_param.next);
            break;
        case AST_FUNC_CALL:
            free(node->data.func_call.name);
            ast_free(node->data.func_call.args);
            break;
        case AST_ARG_LIST:
            ast_free(node->data.expr_list.expr);
            ast_free(node->data.expr_list.next);
            break;
        case AST_RETURN:
        case AST_NEG:
        case AST_NOT:
            ast_free(node->data.unary.operand);
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_INT_DIV:
        case AST_POWER:
        case AST_AND:
        case AST_OR:
        case AST_XOR:
        case AST_EQ:
        case AST_NEQ:
        case AST_LT:
        case AST_GT:
        case AST_LTE:
        case AST_GTE:
            ast_free(node->data.binary.left);
            ast_free(node->data.binary.right);
            break;
        default:
            break;
    }
    
    free(node);
}
