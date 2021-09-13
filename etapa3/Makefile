main:
	rm -f -r etapa3
	rm -f -r etapa3.tgz
	bison -d parser.y
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c LexicalValue.c main.c AST.c
	gcc -o etapa3 lex.yy.o parser.tab.o main.o LexicalValue.o AST.o -ll
clean:
	rm -f lex.yy.c parser.tab.c lex.yy.c
	rm -f *.o
	rm -f *.output
	rm -f etapa3.tgz
	rm -f -r etapa3
deliver:
	rm -f -r etapa3
	mkdir etapa3
	cp parser.y etapa3
	cp scanner.l etapa3
	cp Makefile etapa3
	cp main.c etapa3
	tar cvzf etapa3.tgz etapa3
exec:
	make main
	./etapa3
