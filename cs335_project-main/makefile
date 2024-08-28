test: parser.tab.c lex.yy.c
	g++ -w -o parser parser.tab.c lex.yy.c -ll

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: lexer.l
	flex lexer.l

clean:
	rm -f parser.tab.c lex.yy.c parser.tab.h parser
