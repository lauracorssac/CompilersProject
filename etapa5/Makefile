
	# LAURA BRAGANTE CORSSAC - 00274694

main:
	rm -f -r etapa5
	rm -f -r etapa5.tgz
	bison -d parser.y
	flex scanner.l
	g++ -std=c++11 -c SymbolTable.cpp SymbolTableStack.cpp SymbolTableValue.cpp \
	ErrorManager.cpp Utils.cpp
	gcc -c LexicalValue.c AST.c SyntacticalType.c ReleaseManager.c
	g++ -std=c++11 -c lex.yy.c parser.tab.c main.cpp
	g++ -std=c++11 -o etapa5 lex.yy.o parser.tab.o main.o \
	LexicalValue.o AST.o SymbolTable.o SymbolTableStack.o SymbolTableValue.o \
	ErrorManager.o SyntacticalType.o Utils.o ReleaseManager.o -lfl

clean:
	rm -f -r .vscode
	rm -f lex.yy.c parser.tab.c lex.yy.cc
	rm -f *.o
	rm -f *.output
	rm -f etapa5.tgz
	rm -f -r etapa5
	rm -f parser.tab.h
	rm -f saida saida.txt
deliver:
	make clean
	tar cvzf etapa5.tgz .
exec:
	make main
	./etapa5
