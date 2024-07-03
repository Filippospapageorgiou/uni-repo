all:
	bison -d simple-bison-code.y 
	flex simple-flex-code.l
	gcc simple-bison-code.tab.c lex.yy.c -Wall -Wextra -ll -lfl -lm -o flex-bison  
	./flex-bison input.txt output.txt

clean:
	rm uni-c.tab.c uni-c.tab.h lex.yy.c

flex:
	flex -o simple-flex-code.c simple-flex-code.l
	gcc -o simple-flex-code simple-flex-code.c
	./simple-flex-code input.txt output.txt

clean-flex:
	rm simple-flex-code simple-flex-code.c

bison:
	bison -o simple-bison-code.c simple-bison-code.y
	gcc -o simple-bison-code simple-bison-code.c
	./simple-bison-code input.txt output.txt

clean-bison:
	rm simple-bison-code.c simple-bison-code
