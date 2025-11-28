#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "AST.h"

/* * Função principal de geração de código.
 * Recebe a raiz da AST e o arquivo de saída (pode ser stdout).
 */
void generate_code(ASTNode *node, FILE *out);

#endif