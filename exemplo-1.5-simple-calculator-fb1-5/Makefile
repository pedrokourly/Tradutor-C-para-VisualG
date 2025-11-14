#
# Ref.: http://dinosaur.compilertools.net/bison/bison_5.html
#

CFLAGS = -std=gnu99 #-Wall -Wextra -g
CPARAMS = -lm -ll

PROJ = calculadora
EXE = $(PROJ)

run: clean parser scanner compile
	./$(EXE)
        
all: clean parser scanner
	gcc $(CFLAGS) $(CPARAMS) -o $(EXE) $(PROJ).tab.c lex.yy.c

compile: parser scanner
	gcc $(CFLAGS) -o $(EXE) $(PROJ).tab.c lex.yy.c $(CPARAMS) 

parser:
	bison -d -v --report='all' $(PROJ).y 

scanner:
	flex $(PROJ).l 

clean:
	rm -f $(EXE) \
          lex.yy.c \
          $(PROJ).output \
          $(PROJ).tab.c \
          $(PROJ).tab.h