main:
	flex scanner.l
	gcc -c lex.yy.c
	gcc -c main.c
	gcc lex.yy.o main.o -o etapa1 -ll
clean:
	rm etapa1 lex.yy.c etapa1.tgz lex.yy.o main.o
deliver:
	tar cvzf etapa1.tgz .
exec:
	make main
	./etapa1
