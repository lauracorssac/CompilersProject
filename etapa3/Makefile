
	# LAURA BRAGANTE CORSSAC - 00274694

main:
	rm -f -r etapa3
	rm -f -r etapa3.tgz
	bison -d parser.y
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c LexicalValue.c main.c AST.c
	gcc -o etapa3 lex.yy.o parser.tab.o main.o LexicalValue.o AST.o -lfl
clean:
	rm -f -r .vscode
	rm -f lex.yy.c parser.tab.c lex.yy.c
	rm -f *.o
	rm -f *.output
	rm -f etapa3.tgz
	rm -f -r etapa3
	rm -f parser.tab.h
	rm -f saida
deliver:
	make clean
	tar cvzf etapa3.tgz .
exec:
	make main
	./etapa3
