%{
#include "symbol_table.hpp"
#include "quad.hpp"
#include "alpha_syntaxer.hpp"
int mylineno = 1;
int token_num = 1;
%}

%option noyywrap
%option yylineno
%option outfile = "alpha_lexer.cpp"

COMM_LINE "//".*
COMM_BLOCK "/*"
SKIP      [ \t]+
INTCONST	[0-9]+
REALCONST [0-9]+\.[0-9]*
IDENT [a-zA-Z][a-zA-Z0-9_]*
UNDEFINED .

%%
"\+" {
++token_num;
return PLUS;
}
"=" {
++token_num;
return ASSIGNMENT;
}
"-" {
++token_num;
return MINUS;

}
"\*" {
++token_num;
return MULTIPLICATION;
}
"\/" {
++token_num;
return DIVISION;

}
"\%" {

++token_num;
return MODULO;
}
"\=\=" {

++token_num;
return EQUAL;
}
"\!\=" {

++token_num;
return NOT_EQUAL;
}
"\+\+" {

++token_num;
return PLUS_PLUS;
}
"\-\-" {

++token_num;
return MINUS_MINUS;
}
"\>" {

++token_num;
return GREATER_THAN;
}
"\<" {

++token_num;
return LESS_THAN;
}
"\>\=" {

++token_num;
return GREATER_OR_EQUAL;
}
"\<\=" {

++token_num;
return LESS_OR_EQUAL;
}

"if" {

++token_num;
return IF;

}
"else" {

++token_num;
return ELSE;
}
"while" {

++token_num;
return WHILE;
}
"for" {

++token_num;
return FOR;
}
"function" {

++token_num;
return FUNCTION;
}
"return" {

++token_num;
return RETURN;
}
"break" {

++token_num;
return BREAK;
}
"continue" {

++token_num;
return CONTINUE;
}
"and" {

++token_num;
return AND;
}
"not" {

++token_num;
return NOT;
}
"or" {

++token_num;
return OR;
}
"local" {

++token_num;
return LOCAL;
}
"true" {

++token_num;
return TRUE;
}
"false" {

++token_num;
return FALSE;
}
"nil" {

++token_num;
return NIL;
}

"\{" {

++token_num;
return LEFT_BRACE;
}
"\}" {

++token_num;
return RIGHT_BRACE;
}
"\[" {

++token_num;
return LEFT_BRACKET;
}
"\]" {

++token_num;
return RIGHT_BRACKET;
}
"\(" {

++token_num;
return LEFT_PAREN;
}
"\)" {

++token_num;
return RIGHT_PAREN;
}
"\;" {

++token_num;
return SEMICOLON;
}
"\," {

++token_num;
return COMMA;
}
"\:" {

++token_num;
return COLON;
}
"\:\:" {

++token_num;
return COLON_COLON;
}
"\." {

++token_num;
return DOT;
}
"\.\." {

++token_num;
return DOT_DOT;
}

{SKIP}    /* skip blanks and tabs */

{COMM_LINE} {
    ++token_num;
}
{COMM_BLOCK}    {
	std::stack<int> nest_start_line;
	nest_start_line.push(mylineno);
    int c;
	while( (c=yyinput()) != 0 ){
		if( c == '\n'){
			++mylineno;
		}
		if( c == '/'){
			if( (c=yyinput()) == '*'){
				nest_start_line.push(mylineno);
			}else unput(c);
		}
		else if( c == '*'){
			if( (c=yyinput()) == '/'){

			std::string token = "{"+ std::to_string(nest_start_line.top()) + "," + std::to_string(mylineno) + "}";
			if(nest_start_line.size()>1){
			}else{
			}
				++token_num;
				nest_start_line.pop();
			}else unput(c);
		}
		if(nest_start_line.empty()){
			break;
		}
	}

	if (c==0) printf("ERROR:: \"/*\" at line :%d didn't get terminated before <<EOF>>.\n",nest_start_line.top());
}
￼
{INTCONST} {
	++token_num;
	yylval.intVal = atoi(yytext);
	return INTCONST;
}

{REALCONST}	{
	++token_num;
	yylval.doubleVal = atof(yytext);
return REALCONST;
}

\" {

int c ; 
std::string out_str;
int tmp_line_no = mylineno;
while((c = yyinput()) != 0 ) {
	      
 if (c == '\\') {
	c = yyinput();
	 switch (c) {
		 case 'n':
		 out_str.push_back('\n');
		 break;
		 case 't':
		 out_str.push_back('\t');
		 break;
		 default:
		 out_str.push_back(c);
		 break;
	 }
}
else if(c == '\n'){
	++mylineno;
	out_str.push_back(c);
}
else if(c=='"'){
c=1;
++token_num;
yylval.stringVal = strdup (out_str.c_str());
return STRINGCONST;
	break;}
else {
	out_str.push_back(c);
 }
}
	      if (!c) printf("ERROR:: \" didn't get terminated before <<EOF>>.\n");

}

{IDENT} {
	++token_num;
	yylval.stringVal = strdup(yytext);
	return IDENT;
}

\n     {   mylineno++;continue; }

{UNDEFINED} {printf("ERROR::\"%s\" on line :%d is an UNDEFINED token!\n",yytext,mylineno);
return UNDEFINED;}


%%
