 CPPFLAGS = -Wall -std=c++11
 DEBUGFLAGS = -ggdb
 .PHONY: clean

all: al.out
	rm -f *.o

al.out: alpha_lexer.o al.cpp
	g++ $(CPPFLAGS) $(DEBUGFLAGS) alpha_lexer.o  al.cpp -o al.out

alpha_lexer.o: alpha_lexer.cpp
	g++ $(CPPFLAGS) $(DEBUGFLAGS) -c alpha_lexer.cpp

alpha_lexer.cpp: yyalpha.l
	flex yyalpha.l

clean:
	rm -f *.out *.o alpha_lexer.cpp
