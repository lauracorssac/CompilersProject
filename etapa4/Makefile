
	# LAURA BRAGANTE CORSSAC - 00274694

main:
	rm -f -r etapa4
	rm -f -r etapa4.tgz
	bison -d parser.y
	flex scanner.l
	g++ -c SymbolTable.cpp
	gcc -c LexicalValue.c AST.c
	g++ -c lex.yy.c parser.tab.c main.cpp
	g++ -o etapa4 lex.yy.o parser.tab.o main.o LexicalValue.o AST.o SymbolTable.o -ll
clean:
	rm -f -r .vscode
	rm -f lex.yy.c parser.tab.c lex.yy.c
	rm -f *.o
	rm -f *.output
	rm -f etapa4.tgz
	rm -f -r etapa4
	rm -f parser.tab.h
	rm -f saida
deliver:
	make clean
	tar cvzf etapa4.tgz .
exec:
	make main
	./etapa4
