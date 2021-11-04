	# LAURA BRAGANTE CORSSAC - 00274694

main:
	rm -f -r etapa6
	rm -f -r etapa6.tgz
	bison -d parser.y
	flex scanner.l
	g++ -std=c++11 -c SymbolTable.cpp SymbolTableStack.cpp SymbolTableValue.cpp \
	ErrorManager.cpp Utils.cpp \
	LexicalValue.cpp AST.cpp SyntacticalType.cpp ReleaseManager.cpp \
	CodeGenerator.cpp Code.cpp CodePrinter.cpp \
	ASMGenerator.cpp lex.yy.c parser.tab.c main.cpp
	g++ -std=c++11 -o etapa6 lex.yy.o parser.tab.o main.o \
	LexicalValue.o AST.o SymbolTable.o SymbolTableStack.o SymbolTableValue.o \
	CodePrinter.o Code.o CodeGenerator.o \
	ErrorManager.o SyntacticalType.o Utils.o \
	ASMGenerator.o ReleaseManager.o -lfl

clean:
	rm -f -r .vscode
	rm -f lex.yy.c parser.tab.c lex.yy.cc
	rm -f *.o
	rm -f *.output
	rm -f etapa6.tgz
	rm -f -r etapa6
	rm -f parser.tab.h
	rm -f saida saida.txt
deliver:
	make clean
	tar cvzf etapa6.tgz .
exec:
	make main
	./etapa6
