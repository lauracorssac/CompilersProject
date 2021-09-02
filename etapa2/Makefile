main:
	bison -d -v parser.y
	flex scanner.l
	gcc -c lex.yy.c parser.tab.c main.c
	gcc -o etapa2 lex.yy.o parser.tab.o main.o -lfl
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
sintatico:
	flex scanner.l
	gcc -c lex.yy.c
	gcc -c mainSin.c
	gcc lex.yy.o mainSin.o -o sin -lfl
execsin:
	make sintatico
	./sin
	
	