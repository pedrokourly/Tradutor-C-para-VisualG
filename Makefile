CFLAGS=-std=gnu99 -Wall -Wextra -g
# Adicionei -I src/ para garantir que o parser ache o codegen.h
CPARAMS=-lm -I bin/ -I src/ 

BIN_DIR := bin

# Regra padrão ao digitar apenas 'make'
all: compile

# Apenas roda o tradutor (Gera o output.c mas não executa)
run: 
	./bin/tradutor.exe sample/exemplo_$(N).c

# Apenas roda o tradutor no arquivo de teste padrão
teste: 
	./bin/tradutor.exe sample/visualg_sample_1.alg

# --- NOVA REGRA ---
# Traduz o VisualG, Compila o C gerado e roda o programa final
# Uso: make teste_full
teste_full: compile
	@echo "\n--- 1. Traduzindo VisualG para C ---"
	./bin/tradutor.exe sample/visualg_sample_1.alg
	@echo "\n--- 2. Compilando o Codigo Gerado (output.c) ---"
	gcc output.c -o programa_final -lm
	@echo "\n--- 3. Executando o Programa Final ---"
	./programa_final

# Adicionado src/codegen.c na lista de compilação
compile: clean parser scanner
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) src/AST.c src/codegen.c $(BIN_DIR)/parser.tab.c $(BIN_DIR)/lex.yy.c $(CPARAMS) -o $(BIN_DIR)/tradutor.exe

parser:
	mkdir -p $(BIN_DIR)
	bison -d src/parser.y -o $(BIN_DIR)/parser.tab.c

scanner:
	mkdir -p $(BIN_DIR)
	flex -o $(BIN_DIR)/lex.yy.c src/scanner.l 

clean:
	rm -rf $(BIN_DIR)/* output.c programa_final

zip:
	mkdir -p bkp
	tar -czvf bkp/backup_`date +%y-%m-%d-%H-%M-%S`.tar.gz Makefile src/* sample/*