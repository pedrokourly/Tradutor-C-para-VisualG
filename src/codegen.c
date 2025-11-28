#include "codegen.h"
#include "parser.tab.h"
/* * DEFINA AQUI OS VALORES DOS TOKENS DO SEU PARSER 
 * (Geralmente definidos no y.tab.h ou tokens.h)
 */

static FILE *output = NULL;
static int indentation_level = 0;

/* Protótipos de funções auxiliares */
static void emit_node(ASTNode *node);
static void emit_indent();
static void emit_type(int type_token);

/* Utilitário para indentação */
static void emit_indent() {
    for (int i = 0; i < indentation_level; i++) {
        fprintf(output, "    ");
    }
}

/* Traduz tipos do VisualG para C */
static void emit_type(int type_token) {
    // Você precisa ajustar os Cases para bater com seus tokens do Bison
    switch (type_token) {
        case INTEIRO:      // Nome definido no parser.y
            fprintf(output, "int"); 
            break;
        case REAL:         // Nome definido no parser.y
            fprintf(output, "float"); 
            break;
        case CARACTER:     // VisualG: "caracter" (geralmente um char único)
            fprintf(output, "char"); 
            break;
        case LITERAL:      // VisualG: "literal" (string)
            fprintf(output, "char*"); 
            break;
        case LOGICO:       // VisualG: "logico"
            fprintf(output, "int"); 
            break;
        default:            
            fprintf(output, "int"); // Fallback
            break;
    }
}

/* Função principal de processamento de nós */
static void emit_node(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        // --- PROGRAMA ---
        case AST_PROGRAM:
            fprintf(output, "#include <stdio.h>\n");
            fprintf(output, "#include <stdlib.h>\n");
            fprintf(output, "#include <string.h>\n\n");
            
            // Declarações globais (se houver, no VisualG variáveis costumam ser globais ao main)
            if (node->data.program.var_decls) {
                emit_node(node->data.program.var_decls);
                fprintf(output, "\n");
            }

            // Funções (antes do main)
            if (node->data.program.func_decls) {
                emit_node(node->data.program.func_decls);
                fprintf(output, "\n");
            }

            fprintf(output, "int main() {\n");
            indentation_level++;
            
            if (node->data.program.body) {
                emit_node(node->data.program.body);
            }

            emit_indent();
            fprintf(output, "return 0;\n");
            indentation_level--;
            fprintf(output, "}\n");
            break;

        // --- DECLARAÇÕES ---
        case AST_VAR_DECL:
            emit_indent();
            // 1. Imprime o tipo
            if (node->data.var_decl.type) {
                emit_type(node->data.var_decl.type->data.type_spec.type_token); 
            } else {
                fprintf(output, "int");
            }
            fprintf(output, " ");
            
            // 2. Imprime a lista de nomes (Celcius)
            emit_node(node->data.var_decl.id_list);
            fprintf(output, ";\n");

            // --- CORREÇÃO AQUI ---
            // 3. Verifica se existe uma PRÓXIMA linha de declaração e a imprime
            // Nota: Verifique se no seu AST.h existe um ponteiro 'next' dentro de 'var_decl'
            // ou se ele usa um ponteiro genérico no final da struct.
            if (node->data.var_decl.next) { 
                 emit_node(node->data.var_decl.next);
            }
            break;

        case AST_VAR_LIST:
            if (node->data.var_list.next) {
                emit_node(node->data.var_list.next);
                fprintf(output, ", "); // Separador entre variáveis anteriores e a atual
            }
            fprintf(output, "%s", node->data.var_list.name);
            break;

        // --- COMANDOS E LISTAS ---
        case AST_STMT_LIST:
            if (node->data.stmt_list.next) {
                emit_node(node->data.stmt_list.next);
            }
            emit_node(node->data.stmt_list.stmt);
            break;

        case AST_ASSIGN:
            emit_indent();
            fprintf(output, "%s = ", node->data.assign.var_name);
            emit_node(node->data.assign.expr);
            fprintf(output, ";\n");
            break;

        case AST_IF:
        case AST_IF_ELSE:
            emit_indent();
            fprintf(output, "if (");
            emit_node(node->data.if_stmt.condition);
            fprintf(output, ") {\n");
            indentation_level++;
            emit_node(node->data.if_stmt.then_body);
            indentation_level--;
            emit_indent();
            fprintf(output, "}");
            
            if (node->data.if_stmt.else_body) {
                fprintf(output, " else {\n");
                indentation_level++;
                emit_node(node->data.if_stmt.else_body);
                indentation_level--;
                emit_indent();
                fprintf(output, "}");
            }
            fprintf(output, "\n");
            break;

        case AST_WHILE:
            emit_indent();
            fprintf(output, "while (");
            emit_node(node->data.while_stmt.condition);
            fprintf(output, ") {\n");
            indentation_level++;
            emit_node(node->data.while_stmt.body);
            indentation_level--;
            emit_indent();
            fprintf(output, "}\n");
            break;

        case AST_FOR:
        case AST_FOR_STEP:
            // VisualG: PARA i DE 1 ATE 10 [PASSO 2] FACA
            // C: for (i = 1; i <= 10; i += 2)
            emit_indent();
            fprintf(output, "for (%s = ", node->data.for_stmt.var);
            emit_node(node->data.for_stmt.start);
            fprintf(output, "; %s <= ", node->data.for_stmt.var); // Assume <= por padrão (crescente)
            emit_node(node->data.for_stmt.end);
            fprintf(output, "; %s += ", node->data.for_stmt.var);
            
            if (node->data.for_stmt.step) {
                emit_node(node->data.for_stmt.step);
            } else {
                fprintf(output, "1");
            }
            fprintf(output, ") {\n");
            indentation_level++;
            emit_node(node->data.for_stmt.body);
            indentation_level--;
            emit_indent();
            fprintf(output, "}\n");
            break;

        // --- I/O ---
        case AST_IDENTIFIER:
            // Caso especial: LIMPATELA é frequentemente pego como identificador
            if (strcmp(node->data.identifier.name, "LIMPATELA") == 0) {
                emit_indent();
                fprintf(output, "system(\"cls\"); /* Ou 'clear' no Linux */\n");
            } else {
                fprintf(output, "%s", node->data.identifier.name);
            }
            break;

        case AST_WRITE:
        case AST_WRITELN:
            {
                ASTNode *param = node->data.write_stmt.expr_list;
                while (param != NULL) {
                    emit_indent();
                    fprintf(output, "printf(\"");
                    
                    if (param->type == AST_WRITE_PARAM) {
                        ASTNode *expr = param->data.write_param.expr;
                        int w = param->data.write_param.width;
                        int p = param->data.write_param.precision;

                        // SE FOR STRING
                        if (expr->type == AST_STRING) {
                            fprintf(output, "%%s");
                            fprintf(output, "\", ");
                            emit_node(expr);
                            fprintf(output, ");\n");
                        } 
                        // SE FOR NUMERO OU VARIAVEL
                        else {
                            fprintf(output, "%%");
                            if (w != -1) fprintf(output, "%d", w);
                            if (p != -1) fprintf(output, ".%d", p);
                            
                            if (p != -1) fprintf(output, "f");
                            else fprintf(output, "g");
                            
                            // --- AQUI ESTÁ A CORREÇÃO ---
                            // Fechamos as aspas do printf e adicionamos (double)(...)
                            fprintf(output, "\", (double)("); 
                            emit_node(expr);
                            fprintf(output, "));\n");
                        }
                        
                        param = param->data.write_param.next;
                    } else {
                        break; 
                    }
                }
                
                if (node->type == AST_WRITELN) {
                    emit_indent();
                    fprintf(output, "printf(\"\\n\");\n");
                }
            }
            break;

        case AST_READ:
            // Ex: scanf("%d", &var); 
            // Nota: Sem saber o tipo da variável, é difícil gerar o scanf correto.
            // Geraremos um código genérico assumindo float ou int e pedindo atenção.
            {
                ASTNode *var = node->data.read_stmt.var_list;
                while (var != NULL) {
                    emit_indent();
                    // Assumindo float por padrão para o exemplo de temperatura, 
                    // mas num compilador real precisaria consultar a tabela de símbolos.
                    fprintf(output, "scanf(\"%%f\", &%s); /* TODO: Verificar tipo correto */\n", 
                            var->data.var_list.name);
                    var = var->data.var_list.next;
                }
            }
            break;

        case AST_FUNC_CALL:
            // Verifica se é o comando LIMPATELA chamado como função (com parênteses)
            if (strcmp(node->data.func_call.name, "LIMPATELA") == 0) {
                 emit_indent();
                 fprintf(output, "system(\"cls\"); // No Linux use \"clear\"\n");
            } else {
                 // Chamada de função normal: nome(arg1, arg2)
                 // Se for um comando que deve estar em linha nova, emitimos indentação.
                 // Como não sabemos se é void ou retorno de valor, assumimos uso geral.
                 // Se estiver dentro de uma expressão (ex: x = func()), a indentação
                 // pode atrapalhar, mas para comandos soltos é necessária.
                 // O ideal seria verificar o contexto, mas aqui simplificamos:
                 fprintf(output, "%s(", node->data.func_call.name);
                 if (node->data.func_call.args) {
                     emit_node(node->data.func_call.args);
                 }
                 fprintf(output, ")");
            }
            break;

        case AST_ARG_LIST: 
            // Lista de argumentos separados por vírgula
            emit_node(node->data.expr_list.expr);
            if (node->data.expr_list.next) {
                fprintf(output, ", ");
                emit_node(node->data.expr_list.next);
            }
            break;

        case AST_REPEAT:
            // Tradução de REPITA ... ATE para DO ... WHILE (!condicao)
            emit_indent();
            fprintf(output, "do {\n");
            indentation_level++;
            emit_node(node->data.repeat_stmt.body);
            indentation_level--;
            emit_indent();
            fprintf(output, "} while (!("); // Nega a condição pois REPITA é "até verdade"
            emit_node(node->data.repeat_stmt.condition);
            fprintf(output, "));\n");
            break;

        case AST_INT_DIV:
            // Divisão inteira (\ no VisualG)
            emit_node(node->data.binary.left);
            fprintf(output, " / "); 
            emit_node(node->data.binary.right);
            break;    

        // --- LITERAIS ---
        case AST_NUMBER: fprintf(output, "%d", node->data.int_value); break;
        case AST_FLOAT:  fprintf(output, "%.6f", node->data.float_value); break;
        case AST_STRING: 
            fprintf(output, "%s", node->data.string_value); 
            break;

        // --- OPERAÇÕES BINÁRIAS ---
        // (Apenas alguns exemplos principais)
        case AST_ADD:
            emit_node(node->data.binary.left);
            fprintf(output, " + ");
            emit_node(node->data.binary.right);
            break;
        case AST_SUB:
            emit_node(node->data.binary.left);
            fprintf(output, " - ");
            emit_node(node->data.binary.right);
            break;
        case AST_MUL:
            emit_node(node->data.binary.left);
            fprintf(output, " * ");
            emit_node(node->data.binary.right);
            break;
        case AST_DIV: // Divisão real
            fprintf(output, "(float)");
            emit_node(node->data.binary.left);
            fprintf(output, " / ");
            emit_node(node->data.binary.right);
            break;
            
        // Adicione outros cases (LT, GT, EQ...) conforme necessário
        
        default:
            // Caso encontre um nó não implementado
            // fprintf(stderr, "Aviso: Nó tipo %d não tratado no codegen\n", node->type);
            break;
    }
}

void generate_code(ASTNode *node, FILE *out) {
    output = out;
    indentation_level = 0;
    emit_node(node);
}