 CPPFLAGS = -std=c++11 -Wno-write-strings
 DEBUGFLAGS = -ggdb
 CC = g++
 .PHONY: clean

all: al.out alvm.out
	rm -f *.o

al.out: symbol_table.o quad.o alpha_syntaxer.o alpha_lexer.o t_code.o t_data.o al.o
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) $^ -o al.out
al.o: al.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c al.cpp
alpha_lexer.o: alpha_lexer.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c alpha_lexer.cpp

alpha_syntaxer.o: alpha_syntaxer.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c alpha_syntaxer.cpp

symbol_table.o: symbol_table.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c symbol_table.cpp

quad.o: quad.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c quad.cpp

t_code.o: t_code.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c t_code.cpp

alpha_lexer.cpp: llalpha.lex
	flex llalpha.lex

alpha_syntaxer.cpp: yyalpha.yacc
	bison --yacc --output=alpha_syntaxer.cpp yyalpha.yacc --defines

alvm.out: avm.o alvm.o t_data.o
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) avm.o alvm.o t_data.o -o alvm.out

t_data.o: t_data.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c t_data.cpp
alvm.o: alvm.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c alvm.cpp
avm.o : avm.cpp
	$(CC) $(CPPFLAGS) $(DEBUGFLAGS) -c avm.cpp

clean:
	rm -f *.out *.o alpha_lexer.cpp
