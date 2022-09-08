%{
#include <iostream>
#include <string>
#include "parser.hpp"
#define YY_DECL int alpha_yylex(std::vector<alpha_token_t> &tokens)
	int alpha_yylex(std::vector<alpha_token_t> &tokens);
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
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"PLUS","enumerated"));
++token_num;
}
"=" {
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"ASSIGNMENT","enumerated"));
++token_num;
}
"-" {
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"MINUS","enumerated"));
++token_num;
}
"\*" {
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"MULTIPLICATION","enumerated"));
++token_num;
}
"\/" {
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"DIVISION","enumerated"));
++token_num;

}
"\%" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"MODULO","enumerated"));
++token_num;
}
"\=\=" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"EQUAL","enumerated"));
++token_num;
}
"\!\=" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"NOT_EQUAL","enumerated"));
++token_num;
}
"\+\+" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"PLUS_PLUS","enumerated"));
++token_num;
}
"\-\-" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"MINUS_MINUS","enumerated"));
++token_num;
}
"\>" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"GREATER_THAN","enumerated"));
++token_num;
}
"\<" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"LESS_THAN","enumerated"));
++token_num;
}
"\>\=" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"GREATER_OR_EQUAL","enumerated"));
++token_num;
}
"\<\=" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::OPERATOR,"LESS_OR_EQUAL","enumerated"));
++token_num;
}

"if" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"IF","enumerated"));
++token_num;

}
"else" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"ELSE","enumerated"));
++token_num;
}
"while" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"WHILE","enumerated"));
++token_num;
}
"for" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"FOR","enumerated"));
++token_num;
}
"function" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"FUNCTION","enumerated"));
++token_num;
}
"return" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"RETURN","enumerated"));
++token_num;
}
"break" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"BREAK","enumerated"));
++token_num;
}
"continue" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"CONTINUE","enumerated"));
++token_num;
}
"and" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"AND","enumerated"));
++token_num;
}
"not" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"NOT","enumerated"));
++token_num;
}
"or" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"OR","enumerated"));
++token_num;
}
"local" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"LOCAL","enumerated"));
++token_num;
}
"true" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"TRUE","enumerated"));
++token_num;
}
"false" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"FALSE","enumerated"));
++token_num;
}
"nil" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::KEYWORD,"NIL","enumerated"));
++token_num;
}

"\{" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"LEFT_BRACE","enumerated"));
++token_num;
}
"\}" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"RIGHT_BRACE","enumerated"));
++token_num;
}
"\[" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"LEFT_BRACKET","enumerated"));
++token_num;
}
"\]" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"RIGHT_BRACKET","enumerated"));
++token_num;
}
"\(" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"LEFT_PAREN","enumerated"));
++token_num;
}
"\)" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"RIGHT_PAREN","enumerated"));
++token_num;
}
"\;" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"SEMICOLON","enumerated"));
++token_num;
}
"\," {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"COMMA","enumerated"));
++token_num;
}
"\:" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"COLON","enumerated"));
++token_num;
}
"\:\:" {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"COLON_COLON","enumerated"));
++token_num;
}
"\." {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"DOT","enumerated"));
++token_num;
}
"\.\." {

tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::PUNCTUATION,"DOT_DOT","enumerated"));
++token_num;
}

{SKIP}    /* skip blanks and tabs */

{COMM_LINE} {
    tokens.push_back(alpha_token_t(mylineno , token_num , "" , General_Type::COMMENT,"LINE_COMMENT","enumerated"));
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
				tokens.push_back(alpha_token_t(nest_start_line.top() , token_num , token , General_Type::COMMENT,"NESTED_COMMENT","enumerated"));
			}else{
				tokens.push_back(alpha_token_t(nest_start_line.top() , token_num , token , General_Type::COMMENT,"BLOCK_COMMENT","enumerated"));
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
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::INTCONST,yytext,"int"));
	++token_num;
}

{REALCONST}	{
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::REALCONST,yytext,"double"));
	++token_num;
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
tokens.push_back(alpha_token_t(tmp_line_no,token_num,out_str,General_Type::STRING,"\"" + out_str + "\"","string"));
++token_num;
	break;}
else {
	out_str.push_back(c);
 }
}
	      if (!c) printf("ERROR:: \" didn't get terminated before <<EOF>>.\n");
}

{IDENT} {
tokens.push_back(alpha_token_t(mylineno,token_num,yytext,General_Type::IDENT,"\"" + std::string(yytext) + "\"","enumerated"));
	++token_num;
}

\n        mylineno++;

{UNDEFINED} {printf("ERROR::\"%s\" on line :%d is an UNDEFINED token!\n",yytext,mylineno);
return 2;}


%%
