LEX = lex
YACC = yacc
CC = gcc
CFLAG = -lfl
YFLAGD = -d
YFLAGV = -v
all: y.tab lex.yy.c a.out
y.tab: *.y
	${YACC} ${YFLAGD} *.y
lex.yy.c: *.l
	${LEX} *.l
a.out: lex.yy.c y.tab.c
	${CC} y.tab.c 
clean: 
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm y.output
	clear

