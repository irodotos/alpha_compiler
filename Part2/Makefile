 CPPFLAGS = -std=c++11 -Wno-write-strings
 DEBUGFLAGS = -ggdb
 CC = g++
 .PHONY: clean

all: al.out
	rm -f *.o

al.out: symbol_table.o alpha_syntaxer.o alpha_lexer.o al.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) symbol_table.o alpha_lexer.o alpha_syntaxer.o al.cpp -o al.out

alpha_lexer.o: alpha_lexer.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c alpha_lexer.cpp

alpha_syntaxer.o: alpha_syntaxer.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c alpha_syntaxer.cpp

symbol_table.o: symbol_table.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c symbol_table.cpp

alpha_lexer.cpp: llalpha.lex
	flex llalpha.lex

alpha_syntaxer.cpp: yyalpha.yacc
	bison --yacc --output=alpha_syntaxer.cpp yyalpha.yacc --defines


clean:
	rm -f *.out *.o alpha_lexer.cpp
