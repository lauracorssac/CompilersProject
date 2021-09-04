main:
	rm -f -r etapa2
	rm -f -r etapa2.tgz
	bison -v -d parser.y
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c main.c
	gcc -o etapa2 lex.yy.o parser.tab.o main.o -lfl
clean:
	rm -f lex.yy.c parser.tab.c lex.yy.c
	rm -f *.o
	rm -f *.h
	rm -f *.output
	rm -f etapa2.tgz
	rm -f -r etapa2
deliver:
	rm -f -r etapa2
	mkdir etapa2
	cp parser.y etapa2
	cp scanner.l etapa2
	cp Makefile etapa2
	cp main.c etapa2
	tar cvzf etapa2.tgz etapa2
exec:
	make main
	./etapa2
