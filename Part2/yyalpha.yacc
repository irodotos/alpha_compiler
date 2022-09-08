%{
#include "symbol_table.hpp"

	int yyerror( char *ErrorMessage);
	int curr_scope = 0;
	bool should_Insert = false;
	extern int yylineno;
extern int yylex(void);
extern std::map<std::string, std::vector<SymbolTableEntry>> symbol_table;
extern std::map<unsigned int, std::vector<SymbolTableEntry>> scope_lists;
extern std::vector<ScopeType> Scope;
bool prev_is_func=false;
    bool thereIsAlreadyActiveIDENT = true;
    bool isLibFunction = false;
	bool LibFunctionAccess = false;
	bool isUserFunc = false;
	bool isReturn=false;
	int inFunction=0;
	int inLoop=0;
	bool isGlobal = false;
	bool Insert = false;
	int call = 0;


%}

%start program

%union {
    char* stringVal;
    int intVal;
    double doubleVal;
    SymbolTableEntry* entry;
}
%token PLUS ASSIGNMENT MINUS MULTIPLICATION DIVISION MODULO PLUS_PLUS MINUS_MINUS
%token UMINUS
%token EQUAL NOT_EQUAL GREATER_THAN LESS_THAN GREATER_OR_EQUAL LESS_OR_EQUAL
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE
%token AND OR NOT
%token LOCAL
%token TRUE FALSE NIL
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_PAREN RIGHT_PAREN

%token SEMICOLON COMMA COLON COLON_COLON DOT DOT_DOT
%token COMM_LINE COMM_BLOCK
%token UNDEFINED
%token NEWLINE
%token <intVal> INTCONST
%token <doubleVal> REALCONST
%token <stringVal> IDENT
%token <stringVal> STRINGCONST
%type <entry> lvalue
%type <entry> member
/*
Priority (Lower->Higher)
*/
%right ASSIGNMENT /* = */
%left OR /* or */
%left AND  /* and */
%nonassoc EQUAL NOT_EQUAL /* == != */
%nonassoc GREATER_THAN GREATER_OR_EQUAL LESS_THAN LESS_OR_EQUAL  /* > >= < <= */
%left PLUS MINUS /* + - */
%left MULTIPLICATION DIVISION MODULO /* * / % */
%right NOT PLUS_PLUS MINUS_MINUS /* not ++  --  - */
%left DOT DOT_DOT /* . .. */
%nonassoc UMINUS 
%left LEFT_BRACKET RIGHT_BRACKET /* [] */ 
%left LEFT_BRACE RIGHT_BRACE  /* {} */
%left LEFT_PAREN RIGHT_PAREN /* () */

%%
program: stmts {}
	;


stmt: expr SEMICOLON {isUserFunc=false;isLibFunction=false;}
	| ifstmt
	| whilestmt
	| forstmt
	| returnstmt
	| BREAK SEMICOLON {if(inLoop==0){yyerror("ERROR:: BREAK outside loop ");}}
	| CONTINUE SEMICOLON{if(inLoop==0){yyerror("ERROR:: CONTINUE outside loop ");}}
	| block
	| funcdef
	| SEMICOLON
	;


stmts : stmt stmts
      |
	;

expr: 	assginexpr
  	|expr PLUS expr
	|expr MINUS  expr
	|expr MULTIPLICATION expr
	|expr DIVISION expr
	|expr MODULO expr
	|expr GREATER_THAN expr
	|expr GREATER_OR_EQUAL expr
	|expr LESS_THAN expr
	|expr LESS_OR_EQUAL expr
	|expr EQUAL expr
	|expr NOT_EQUAL expr
	|expr AND expr
	|expr OR expr
	| term
	;

term: LEFT_PAREN expr RIGHT_PAREN 
	| MINUS expr %prec UMINUS
	| NOT expr
	| PLUS_PLUS lvalue{
	if($2 != NULL ){
	if ($2->get_type() == func_USER || $2->get_type() == func_LIB) {
		yyerror("ERROR:: Assigning value to function ");
}    
		}
	}
	| lvalue PLUS_PLUS {
	if($1 != NULL ){
	if ($1->get_type() == func_USER || $1->get_type() == func_LIB) {
		yyerror("ERROR:: Assigning value to function ");
}    
		}
		}
	| MINUS_MINUS lvalue {
	if($2 != NULL ){
	if ($2->get_type() == func_USER || $2->get_type() == func_LIB) {
		yyerror("ERROR:: Assigning value to function ");
}    
		}
			}
	| lvalue MINUS_MINUS {
	if($1 != NULL ){
	if ($1->get_type() == func_USER || $1->get_type() == func_LIB) {
		yyerror("ERROR:: Assigning value to function ");
}    
		}
				}
	| primary
	;

assginexpr: lvalue {
	if($1 != NULL ){
	if ($1->get_type() == func_USER || $1->get_type() == func_LIB) {
		yyerror("ERROR:: Assigning value to function ");
}    
	    }
	  } ASSIGNMENT{} expr {/*INSERT*/ } 
	;

primary: lvalue {


				}
	| call 
	| objectdef
	| LEFT_PAREN funcdef RIGHT_PAREN
	| const
	;

lvalue: IDENT  { 
	Insert = true;
	SymbolTableEntry* temp;
	std::string var_name = yylval.stringVal;
	if(isReturn == true){
		Insert = false;
		if(inFunction == 0){
			yyerror("ERROR:: You try to return without being in function ");
		}
		else if( (temp = lookUpScope(var_name , curr_scope)) != NULL){
		$$=temp;

		}
		else if( (temp = lookUpScope(var_name , 0)) != NULL ){

		}
		else if( (temp = lookUp(var_name, curr_scope)) != NULL ){  /* look in all previus scopes starting with the curr_scope -1 until zero */
			Insert = false;
		if (temp->get_type() != func_USER &&  
		temp->get_scope() < get_min_legal_scope() ){

				yyerror("ERROR:: You cant access the IDENT ");

			}
			$$ = temp;
		}
		else{
			yyerror("ERROR:: There is no name for the var/func you try to return ");

		}
	}
	/* else if(call != 0){ */
	/**/
	/* 	insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_FORMAL, true)); */
	/* 	Insert = false; */
	/* } */
	else{
	
		if( (temp = lookUpScope(var_name , curr_scope)) != NULL ){  /* look in the same scope => formal arguments and variable in the scope/function */
				Insert = false;
				$$ = temp;
		}
		else if( (temp = lookUp(var_name, curr_scope)) != NULL ){  /* look in all previus scopes starting with the curr_scope -1 until zero */
			Insert = false;
		if (temp->get_type() != func_USER &&  
		temp->get_scope() < get_min_legal_scope() ){

				yyerror("ERROR:: You cant access the IDENT ");

			}
			$$ = temp;
		}
		else if( (temp = lookUpScope(var_name , 0)) != NULL ){  /* look in global scope */
			Insert = false;
			if(temp->get_type() == func_LIB){								/* if it's a library function */
				isLibFunction = true;
				if(curr_scope != 0){									/* if curr_scope != 0 => we dont have access */
					LibFunctionAccess = false;
				}
				else{
					LibFunctionAccess = true;
				}
			}
			else{
				isLibFunction = false;
			}
			$$ = temp;
		}
	}

	if(Insert == true){
		if(curr_scope == 0){
			insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_GLOBAL, true));
		}
		else{
			insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_LOCAL, true));
		}
	}

}

	| LOCAL IDENT {

	std::string var_name = yylval.stringVal;
    SymbolTableEntry* temp; 
    if ((temp = lookUpScope(var_name,curr_scope)) != NULL) {
                if(temp->get_type() == func_USER) isUserFunc=true;
                $$ = temp;
            }
// elenxos an einai idi lib function => error 
else if ((temp = lookUpLIB(var_name)) != NULL){
                yyerror("ERROR:: Assigning local libfunc outside GLOBAL scope ");
		$$ = temp;
            }// elenxos an iparxi idi sto scope ident idio => anaferomaste se afto to ident 
// dimiourgiena neo ident kai to vazi stin table => insert in table
    else {
            if (curr_scope == 0){
                insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_GLOBAL, true));
            }
            else {
                insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_LOCAL, true));
            }
	$$= temp;
    }
} 
| COLON_COLON IDENT {
	std::string var_name = yylval.stringVal;
	SymbolTableEntry* temp;
       if ( (temp = lookUpScope(var_name,0)) == NULL) {
	yyerror("ERROR:: No GLOBAL whith this name ");
       }
       $$=temp;
}
	| member
	;

member: lvalue DOT IDENT
	| lvalue  LEFT_BRACKET expr RIGHT_BRACKET
	| call DOT IDENT {$$= NULL;}
	| call LEFT_BRACKET expr RIGHT_BRACKET
	;

call: call LEFT_PAREN elist RIGHT_PAREN
	| lvalue callsuffix
	| LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN
	;

callsuffix: normcall
	| methodcall
	;

normcall: LEFT_PAREN {call++;} elist RIGHT_PAREN {call--;}
	;

methodcall: DOT_DOT IDENT LEFT_PAREN {call++;} elist RIGHT_PAREN  {call--;}
	;

elist: expr elist_expressions
	|/*empty*/
	;

elist_expressions: COMMA expr elist_expressions 
		 |/*empty*/
		 ;


objectdef: LEFT_BRACKET indexed RIGHT_BRACKET 
	 | LEFT_BRACKET  elist  RIGHT_BRACKET
	;

indexed: indexedelem index_elements
	;

index_elements: COMMA indexedelem index_elements
		 | /*empty*/
		 ;

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE
	;

block:  LEFT_BRACE {curr_scope++;if (!prev_is_func) Scope.push_back(BLOCK) ;else Scope.push_back(FUNC);prev_is_func=false;} stmts RIGHT_BRACE {   /* HIDE TIS METAVITES */hide(curr_scope) ;Scope.pop_back();curr_scope--;}
	;

funcdef: FUNCTION IDENT { 
        std::string var_name = yylval.stringVal;
	SymbolTableEntry* temp;
	if( (temp = lookUpLIB(var_name)) != NULL){
			yyerror("ERROR:: Shadowing a LIB function ");
		}
	else if ((temp = lookUpScope(var_name,curr_scope)) != NULL) {
		if(temp->get_type() == var_LOCAL || temp->get_type() == var_FORMAL || temp->get_type() == var_GLOBAL){
			yyerror("ERROR:: Already assigned a variable with this name ");
		}
		else if(temp->get_type() == func_USER ){
				yyerror("ERROR:: Already assigned a function with this name ");
			}
	}
	else {
	    insert(SymbolTableEntry(Function(var_name, curr_scope, yylineno), func_USER, true));
	}
	} LEFT_PAREN {curr_scope++;Scope.push_back(BLOCK);} idlist RIGHT_PAREN {curr_scope--;Scope.pop_back();++inFunction;prev_is_func=true;} block{--inFunction;}
	| FUNCTION LEFT_PAREN {
		std::string lambdaName = get_tmp_name("_");
		insert(SymbolTableEntry(Function(lambdaName, curr_scope, yylineno), func_USER, true));
		curr_scope++;Scope.push_back(BLOCK);}idlist RIGHT_PAREN{Scope.pop_back();curr_scope--;++inFunction;prev_is_func=true;} block  {--inFunction;}
		// TODO look^ 
	;

const: 	INTCONST
	| REALCONST
	| STRINGCONST
	| NIL
	| TRUE
	| FALSE
	;

idlist:  IDENT { 

SymbolTableEntry* temp;
std::string var_name= yylval.stringVal;
if ((temp = lookUpLIB(var_name)) != NULL){
		yyerror("ERROR:: Shadowing libfunc ");
}
else if ((temp = lookUpScope(var_name,curr_scope)) != NULL ){
	if (temp->get_type() == var_FORMAL) yyerror("ERROR:: Formal argument already assigned ");

}
else insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_FORMAL, true)); 
	 } idlists
	|/*empty*/ 
	;

idlists: COMMA IDENT {

SymbolTableEntry* temp;
std::string var_name= yylval.stringVal;
if ((temp = lookUpLIB(var_name)) != NULL){
		 yyerror("ERROR:: Shadowing libfunc ");
}
else if ((temp = lookUpScope(var_name,curr_scope)) != NULL ){
	if (temp->get_type() == var_FORMAL) yyerror("ERROR:: Formal argument already assigned ");

}
else insert(SymbolTableEntry(Variable(var_name, curr_scope, yylineno), var_FORMAL, true)); 
	} idlists
       |/*empty*/ 
       ;

ifstmt: IF LEFT_PAREN expr RIGHT_PAREN stmt ELSE stmt
	|	IF LEFT_PAREN expr RIGHT_PAREN stmt
	;

whilestmt: WHILE LEFT_PAREN expr RIGHT_PAREN {++inLoop;}stmt{--inLoop;}
	;

forstmt: FOR LEFT_PAREN elist SEMICOLON expr SEMICOLON elist RIGHT_PAREN {++inLoop;}stmt{--inLoop;}
	;

returnstmt: RETURN{if(inFunction==0){ yyerror("ERROR:: Return outside of function "); }
		isReturn=true;
		} expr SEMICOLON {isReturn=false;}
	| 	RETURN SEMICOLON
	;
	
%%
