main:
	bison -d -v parser.y
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c main.c
	gcc -o etapa2 lex.yy.o parser.tab.o main.o -ll
clean:
	rm lex.yy.c parser.tab.c
	rm *.o
	rm *.h
	rm etapa2 etapa2.tgz
deliver:
	tar cvzf etapa2.tgz .
exec:
	make main
	./etapa2
