%{
#include "symbol_table.hpp"
#include "quad.hpp"


	int yyerror( char *ErrorMessage);
	int curr_scope = 0;
	extern int yylineno;
	extern int yylex(void);

	ScopeType prev_block;
	bool isReturn=false;
	int inFunction=0;
	bool Insert = false;
	std::stack<int> scopeoffsetstack;
	std::stack<int> functionjumpstack;
	std::stack<std::vector<unsigned int>> functionretstack;
	bool isBackpatch = 0;


%}

%start program

%union {
	const char* stringVal;
	int intVal;
	double doubleVal;
	expr* expression;
	forstruct* forVal;
	callstruct* callVal;
	indexedstruct* pairVal;
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

%type <expression> lvalue member primary assignexpr call term objectdef const expr elist 
%type <pairVal> indexedelem indexed
%type <intVal> Q N M whilestart whilecond ifprefix elseprefix
%type <forVal> forprefix
%type <stringVal> func_name
%type <intVal> func_body
%type <expression> funcdef func_prefix
%type <callVal> methodcall callsuffix normcall
%type <expression> or_prefix and_prefix not_equal_prefix equal_prefix


/*
Priority (Lower->Higher)
*/
%right ASSIGNMENT /* = */
%left OR 
%left AND  /* or and */
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


stmt: expr SEMICOLON {
auto i = $1;
		if ($1->inLogical && isBackpatch == 0) {
		    backpatch($expr->falselist, nextquad() + 2);
		    backpatch($expr->truelist, nextquad());
		    auto t = $1;

		expr* temp = newexpr(arithexpr_e);
		temp->sym = istempexpr($expr) ? $expr->sym : new_temp();
		/* $1->sym = istempexpr($expr) ? $expr->sym : new_temp(); */
			emit(assign , temp , newexpr_constbool(true) , NULL ,  -1 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , temp  , newexpr_constbool(false) , NULL , -1 , yylineno);
		}
		isBackpatch = 0;
		zero_tmp_counter();
	}
	| ifstmt {zero_tmp_counter();}
	| whilestmt {zero_tmp_counter();}
	| forstmt {zero_tmp_counter();}
	| returnstmt {zero_tmp_counter();}
	| BREAK SEMICOLON {
			if(!is_in_loop()){yyerror("ERROR:: BREAK outside loop ");}
			insert_break(nextquad());
			emit(jump, NULL, NULL, NULL, 0, yylineno);
			zero_tmp_counter();
						}
	| CONTINUE SEMICOLON{
			if(!is_in_loop()){yyerror("ERROR:: CONTINUE outside loop ");}
			insert_cont(nextquad());
			emit(jump, NULL, NULL, NULL, 0, yylineno);
			zero_tmp_counter();
						}
	| block {zero_tmp_counter();}
	| funcdef {zero_tmp_counter();}
	| SEMICOLON {zero_tmp_counter();}
	;


stmts : stmt stmts
      |
	;

expr: 	assignexpr
  	|expr PLUS expr {
		$$ = newexpr(arithexpr_e);
		$$->sym = recycle_temp($1,$3);
		emit(add, $$, $1, $3, -1 , yylineno);
	}
	|expr MINUS  expr {
		$$ = newexpr(arithexpr_e);
		$$->sym = recycle_temp($1,$3);
		emit(sub, $$, $1, $3, -1 , yylineno);
	}
	|expr MULTIPLICATION expr {
		$$ = newexpr(arithexpr_e);
		$$->sym = recycle_temp($1,$3);
		emit(mul, $$, $1, $3, -1 , yylineno);
	}
	|expr DIVISION expr {
		$$ = newexpr(arithexpr_e);
		$$->sym = recycle_temp($1,$3);
		emit(div_, $$, $1, $3, -1 , yylineno);
	}
	|expr MODULO expr {
		$$ = newexpr(arithexpr_e);
		$$->sym = recycle_temp($1,$3);
		emit(mod, $$, $1, $3, -1 , yylineno);
	}
	|expr GREATER_THAN expr { $$= relop( $1,if_greater, $3); }
	|expr GREATER_OR_EQUAL expr { $$= relop( $1,if_greatereq, $3); }
	|expr LESS_THAN expr { $$ = relop( $1,if_less, $3);} 
	|expr LESS_OR_EQUAL expr { $$= relop( $1,if_lesseq, $3); }
	|equal_prefix expr %prec EQUAL{ 
			$$= relop( $1,if_eq, $2);
			backpatch($$->falselist , nextquad()+2);
			backpatch($$->truelist , nextquad());
			/* $$->sym =  recycle_temp($1,$2); */
			/* emit(assign , $$ , newexpr_constbool(true) , NULL ,  -1 , yylineno); */
			/* emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno); */
			/* emit(assign , $$  , newexpr_constbool(false) , NULL , -1 , yylineno); */
	}
	|not_equal_prefix expr %prec NOT_EQUAL{
			$$= relop( $1,if_noteq, $2);
			backpatch($$->falselist , nextquad()+2);
			backpatch($$->truelist , nextquad());
			/* $$->sym =  recycle_temp($1,$2); */
			/* emit(assign , $$ , newexpr_constbool(true) , NULL ,  -1 , yylineno); */
			/* emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno); */
			/* emit(assign , $$  , newexpr_constbool(false) , NULL , -1 , yylineno); */
	}
	|and_prefix Q expr %prec AND {
			if ($3->truelist.size() == 0 && $3->falselist.size() == 0) {
			    /* $3->type = logicalop_e; */
			    $3->truelist.push_back(nextquad());
			    $3->falselist.push_back(nextquad() + 1);
			    if ($3->not_c) {
				$3->truelist.swap($3->falselist);
				$3->not_c = false;
			    }
			    emit(if_eq, NULL,$3, newexpr_constbool(1),  0, yylineno);
			    emit(jump, NULL, NULL, NULL, 0, yylineno);
			}
			backpatch($1->truelist, $Q);
			$$->falselist = mergelists($1->falselist, $3->falselist);
			$$->truelist = $3->truelist;
			/* $$->type = logicalop_e; */
			$$->inLogical=true;
	}
	|or_prefix  Q expr %prec OR{
			if ($3->truelist.size() == 0 && $3->falselist.size() == 0) {
			    /* $3->type = logicalop_e; */
			    $3->truelist.push_back(nextquad());
			    $3->falselist.push_back(nextquad() + 1);

			    if ($3->not_c) {
				$3->truelist.swap($3->falselist);
				$3->not_c = false;
			    }
			    emit(if_eq,NULL, $3, newexpr_constbool(1),  0, yylineno);
			    emit(jump, NULL, NULL, NULL, 0, yylineno);
			}
			backpatch($1->falselist, $Q);
			$$->truelist = mergelists($1->truelist, $3->truelist);
			$$->falselist = $3->falselist;
			/* $$->type = logicalop_e; */
			$$->inLogical=true;
	}
	| term {$$=$1;}
	;

and_prefix: expr AND {
		if ($1->truelist.size() == 0 && $1->falselist.size() == 0) {
		    /* $1->type = logicalop_e; */
		    $1->truelist.push_back(nextquad());
		    $1->falselist.push_back(nextquad() + 1);
		    if ($1->not_c) {
			$1->truelist.swap($1->falselist);
			$1->not_c = false;
		    }
		    emit(if_eq,  NULL,$1, newexpr_constbool(1), 0, yylineno);
		    emit(jump, NULL, NULL, NULL, 0, yylineno);
			/* $1->type=logicalop_e; */
		}
	} 
	;

or_prefix: expr OR {


		if($1->truelist.size()==0 && $1->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			$1->truelist.push_back(nextquad());
			$1->falselist.push_back( nextquad()+1);
			if ($1->not_c){$1->truelist.swap($1->falselist);$1->not_c=false;}

			emit(if_eq,NULL ,$1,newexpr_constbool(1),0,yylineno);
			emit(jump , NULL , NULL , NULL , 0 , yylineno);
			$1->inLogical=true;
		}

	}
	;

not_equal_prefix: expr NOT_EQUAL{
		if($1->truelist.size()==0 && $1->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			$1->truelist.push_back(nextquad());
			$1->falselist.push_back( nextquad()+1);
			if ($1->not_c){$1->truelist.swap($1->falselist);$1->not_c=false;}
			$1->inLogical=true;
		}
	}
	;

equal_prefix: expr EQUAL{
		if($1->truelist.size()==0 && $1->falselist.size()==0){
  			/* $1->type=logicalop_e; */
			$1->truelist.push_back(nextquad());
			$1->falselist.push_back( nextquad()+1);
			if ($1->not_c){$1->truelist.swap($1->falselist);$1->not_c=false;}
			$1->inLogical=true;
		}
	}
	;

Q : {$$=nextquad();}
term: LEFT_PAREN expr RIGHT_PAREN {$$=$expr;}
	| MINUS expr %prec UMINUS {
		check_arithm($expr, "ERROR:: Not an arirthemic expression!");
		$$ = newexpr(arithexpr_e);
		$$->sym = istempexpr($expr) ? $expr->sym : new_temp();
		emit(uminus, $$, $expr, NULL, -1 , yylineno);
	}
	| NOT expr {


		if($expr->truelist.size()==0 && $expr->falselist.size()==0){
			/* $expr->type=logicalop_e; */
			$expr->truelist.push_back(nextquad());
			$expr->falselist.push_back( nextquad()+1);
			emit(if_eq,$2,newexpr_constbool(true) ,NULL ,0,yylineno);
			emit(jump , NULL , NULL , NULL , 0, yylineno);
}

			$2->truelist.swap($2->falselist);
			backpatch($2->falselist , nextquad()+2);
			backpatch($2->truelist , nextquad());
			$2->not_c=true;
			/* if ($expr->sym ==NULL){SymbolTableEntry } */
			$2->inLogical=true;
		$$=$2;
	}
	| PLUS_PLUS lvalue{
		if($lvalue != NULL && $lvalue->sym != NULL ){
			if ($lvalue->sym->get_type() == func_USER || $lvalue->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {


				check_arithm($lvalue , "Not an arithmetic expression!");
				if ($lvalue->type == tableitem_e) {
					$$ = emit_iftableitem($lvalue);
					emit(add,$$, $$, newexpr_constnum(1),-1,yylineno );
					emit(tablesetelem,$lvalue,  $lvalue->index,$$,-1,yylineno );
				}
				else {
					emit(add,$lvalue, $lvalue, newexpr_constnum(1),-1,yylineno );
					$term = newexpr(arithexpr_e);
					$term->sym = new_temp();
					emit(assign,$$, $lvalue, NULL,-1,yylineno);
				}
			}
		}
	}
	| lvalue PLUS_PLUS {
		if($lvalue != NULL && $lvalue->sym != NULL ){
			if ($lvalue->sym->get_type() == func_USER || $lvalue->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {

				check_arithm($lvalue , "Not an arithmetic expression!");
				$term = newexpr(var_e);
				$term->sym = new_temp();
				if ($lvalue->type == tableitem_e) {
					expr* val = emit_iftableitem($lvalue);
					emit(assign,$term, val, NULL,-1,yylineno );
					emit(add,val, val, newexpr_constnum(1),-1,yylineno );
					emit(tablesetelem, $lvalue,  $lvalue->index,val,-1,yylineno );
				}
				else {
					emit(assign,$$, $lvalue, NULL,-1,yylineno);
					emit(add, $lvalue ,$lvalue, newexpr_constnum(1),-1,yylineno);
				}
			}
		}
	}
	| MINUS_MINUS lvalue {
		if($lvalue != NULL && $lvalue->sym != NULL ){
			if ($lvalue->sym->get_type() == func_USER || $lvalue->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {


				check_arithm($lvalue , "Not an arithmetic expression!");
				if ($lvalue->type == tableitem_e) {
					$$ = emit_iftableitem($lvalue);
					emit(sub,$$, $$, newexpr_constnum(1),-1,yylineno );
					emit(tablesetelem,$lvalue,  $lvalue->index,$$,-1,yylineno );
				}
				else {
					emit(sub,$lvalue, $lvalue, newexpr_constnum(1),-1,yylineno );
					$term = newexpr(arithexpr_e);
					$term->sym = new_temp();
					emit(assign,$$, $lvalue, NULL,-1,yylineno);

				}
			}
		}
	}
	| lvalue MINUS_MINUS {
		if($lvalue != NULL && $lvalue->sym != NULL ){
			if ($lvalue->sym->get_type() == func_USER || $lvalue->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
			else {
				check_arithm($lvalue , "Not an arithmetic expression!");
				$term = newexpr(var_e);
				$term->sym = new_temp();
				if ($lvalue->type == tableitem_e) {
					expr* val = emit_iftableitem($lvalue);
					emit(assign,$term, val, NULL,-1,yylineno );
					emit(sub,val, val, newexpr_constnum(1),-1,yylineno );
					emit(tablesetelem, $lvalue,  $lvalue->index,val,-1,yylineno );
				}
				else {
					emit(assign,$$, $lvalue, NULL,-1,yylineno);
					emit(sub, $lvalue ,$lvalue, newexpr_constnum(1),-1,yylineno);

				}
			}

		}
	}
	| primary
	;

assignexpr: lvalue {
		
		if($lvalue != NULL && $lvalue->sym != NULL ){
			if ($lvalue->sym->get_type() == func_USER || $lvalue->sym->get_type() == func_LIB) {
				yyerror("ERROR:: Assigning value to function ");
			}    
	    }
	} ASSIGNMENT expr {

		if ($1 != NULL && $expr->inLogical) {
		    backpatch($expr->falselist, nextquad() + 2);
		    backpatch($expr->truelist, nextquad());

		    $assignexpr = newexpr(boolexpr_e);
		    $expr = newexpr(assignexpr_e);
		    $assignexpr->sym = $expr->sym = new_temp();

		    emit(assign, $assignexpr, newexpr_constbool(true), NULL, -1, yylineno);
		    emit(jump, NULL, NULL, NULL, nextquad() + 2, yylineno);
		    emit(assign, $assignexpr, newexpr_constbool(false), NULL, -1, yylineno);
		    isBackpatch = true;
		}
		if ($1 != NULL && $1->type == tableitem_e) {
		    emit(tablesetelem, $lvalue, $lvalue->index, $expr, -1, yylineno);
		    $$ = emit_iftableitem($lvalue);
		    $$->type = assignexpr_e;
		} else {
		    emit(assign, $lvalue, $expr, NULL, -1, yylineno);
		    $assignexpr = newexpr(assignexpr_e);
		    $assignexpr->sym = new_temp();
		    emit(assign, $assignexpr, $lvalue, NULL, -1, yylineno);
		}
}
	;

primary: lvalue {
				
		$$ = emit_iftableitem($lvalue);
				}
	| call 
	| objectdef
	| LEFT_PAREN funcdef RIGHT_PAREN {$$ = $funcdef;}
	| const 
	;

lvalue: IDENT  { 
		Insert = true;
		SymbolTableEntry *temp;
		std::string var_name = yylval.stringVal;
		if (isReturn == true) {
		    Insert = false;
		    if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		    } else if ((temp = lookUp(var_name, curr_scope)) !=
			       NULL) { /* look in all previus scopes starting with the
					  curr_scope -1 until zero */
			Insert = false;
			if (temp->get_type() != func_USER &&
			    temp->get_scope() < get_min_legal_scope()) {
			    yyerror("ERROR:: You cant access the IDENT ");
			}
		    } else if ((temp = lookUpScope(var_name, 0)) != NULL) {

		    } else {
			yyerror("ERROR:: There is no name for the var/func you try to return ");
		    }
		} else {

		    if ((temp = lookUpScope(var_name, curr_scope)) !=
			NULL) { /* look in the same scope => formal arguments and variable in
				   the scope/function */
			Insert = false;
		    } else if ((temp = lookUp(var_name, curr_scope)) !=
			       NULL) { /* look in all previus scopes starting with the
					  curr_scope -1 until zero */
			Insert = false;
			if (temp->get_type() != func_USER &&
			    temp->get_scope() < get_min_legal_scope()) {
			    yyerror("ERROR:: You cant access the IDENT ");
			}
		    } else if ((temp = lookUpScope(var_name, 0)) !=
			       NULL) { /* look in global scope */
			Insert = false;
		    }
		}

		if (Insert == true) {
		    if (curr_scope == 0) {
			insert(var_name, curr_scope, yylineno, var_GLOBAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    } else {
			insert(var_name, curr_scope, yylineno, var_LOCAL, true,
			       currscopeoffset(), currscopespace());
			inccurrscopeoffset();
			temp = lookUpScope(var_name, curr_scope);
		    }
		}
		if (temp == NULL) {
		    $$ = NULL;
		} else {
		    $$ = Symbol_to_Expr(temp);
		}
	}

	| LOCAL IDENT {

		std::string var_name = yylval.stringVal;
		SymbolTableEntry *temp;
		// elenxos an iparxi idi sto scope ident idio => anaferomaste se afto to ident
		if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		}
		// elenxos an einai idi lib function => error
		else if ((temp = lookUpLIB(var_name)) != NULL) {
		    yyerror("ERROR:: Assigning local libfunc outside GLOBAL scope ");
		}
		// dimiourgiena neo ident kai to vazi stin table => insert in table
		else {
		    if (curr_scope == 0) {
			insert(var_name, curr_scope, yylineno, var_GLOBAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    } else {
			insert(var_name, curr_scope, yylineno, var_LOCAL, true,
			       currscopeoffset(), currscopespace());
			temp = lookUpScope(var_name, curr_scope);
			inccurrscopeoffset();
		    }
		}
		if (temp == NULL) {
		    $$ = NULL;
		} else {
		    $$ = Symbol_to_Expr(temp);
		}
} 
| COLON_COLON IDENT {
		std::string var_name = yylval.stringVal;
		SymbolTableEntry *temp;
		if ((temp = lookUpScope(var_name, 0)) == NULL) {
		    yyerror("ERROR:: No GLOBAL whith this name ");
		}
		if (temp == NULL) {
		    $$ = NULL;
		} else {
		    $$ = Symbol_to_Expr(temp);
		}
}
	| member  {$$=$1;}
	;

member: lvalue DOT IDENT {$$ = member_item($lvalue , $IDENT);}
	| lvalue  LEFT_BRACKET expr RIGHT_BRACKET { 
						$1 = emit_iftableitem($1); 
						$$ = newexpr(tableitem_e); 
						$$->sym = $1->sym; 
						$$->index = $3; 
					}
	| call DOT IDENT {
			$$=$1 ;
			$$->type=tableitem_e;

}

	| call LEFT_BRACKET expr RIGHT_BRACKET
	;

call: call LEFT_PAREN elist RIGHT_PAREN  {$$ = make_call($1, $elist);

			if($elist != NULL && $elist->inLogical){
				expr* temp = newexpr(assignexpr_e);
				temp->sym = new_temp();
				emit(assign , temp , newexpr_constbool(true) , NULL ,  -1 , yylineno);
				emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
				emit(assign , temp  , newexpr_constbool(false) , NULL , -1 , yylineno);
			}

	}
	| lvalue callsuffix {
			$lvalue = emit_iftableitem($lvalue);
			if ($callsuffix->method) {
			    expr *t = $lvalue;
			    $lvalue = emit_iftableitem(member_item(t, $callsuffix->name));
			    $callsuffix->elist->next = t;
			}
			$call = make_call($lvalue, $callsuffix->elist);
   }
	| LEFT_PAREN funcdef RIGHT_PAREN LEFT_PAREN elist RIGHT_PAREN {
						expr* func = newexpr(programfunc_e);
						func->sym = $funcdef->sym;
						$$ = make_call(func, $elist);
						}
	;

callsuffix: normcall {$$ = $normcall;}
	| methodcall {$$ = $methodcall;}
	;

normcall: LEFT_PAREN {} elist RIGHT_PAREN {
					
			
			$normcall = new callstruct();
			$normcall->elist = $elist;
			$normcall->method = 0;
			$normcall->name = NULL;
			
		}
	;

methodcall: DOT_DOT IDENT LEFT_PAREN {} elist RIGHT_PAREN  {
							//$$ = newexpr(tableitem_e);

				$$->elist = $elist;
				$$->name = $IDENT;
				$$->method = 1;
	}
	;

elist: expr{
	if($expr!=NULL && $expr->inLogical){
				backpatch($expr->falselist , nextquad()+2);
				backpatch($expr->truelist , nextquad());
				expr* temp = newexpr(assignexpr_e);
				//printf("hshshshshhs");
				temp->sym = new_temp();
				emit(assign , temp , newexpr_constbool(true) , NULL ,  -1 , yylineno);
				emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
				emit(assign , temp  , newexpr_constbool(false) , NULL , -1 , yylineno);
				$expr = temp;	
			}
	$$ = $1;
}| elist COMMA expr{
	expr* tmp = $1;
	while(tmp->next!=NULL) tmp = tmp->next;
	tmp->next = $expr;
	$$ = $1;
}| {$$ = NULL;}
	 ;

objectdef: LEFT_BRACKET indexed RIGHT_BRACKET  {

		expr *temp = newexpr(newtable_e);
		temp->sym = new_temp();
		emit(tablecreate, temp, NULL, NULL, -1, yylineno);
		for (int i = 0; $indexed; $indexed = $indexed->next) {
		    emit(tablesetelem, temp, $indexed->index, $indexed->element, -1, yylineno);
		}
		$$ = temp;
	 }
	 | LEFT_BRACKET  elist  RIGHT_BRACKET {

        expr* temp = newexpr(newtable_e);
        temp->sym = new_temp();
        emit(tablecreate, temp, NULL, NULL , -1 , yylineno);
        for (int i = 0; $elist; $elist = $elist->next){
            emit(tablesetelem,  temp, newexpr_constnum(i++), $elist , -1 , yylineno);
        }
        $$ = temp;
	}
	;

indexed: indexedelem{ $$=$1;}
     | indexed COMMA indexedelem{
		indexedstruct *temp = $1;
		while (temp->next)
		    temp = temp->next;
		temp->next = $3;
		$$ = $1;
	}
	 ;
indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE {
	   $$ = new indexedstruct();	
	   $$->index = $2;
	   $$->element= $4;
	   $$->next= NULL;

	   }
	;

block:  LEFT_BRACE {
     		curr_scope++;
		push_Scope(prev_block);
		prev_block=BLOCK;
		} stmts RIGHT_BRACE {  hide(curr_scope);  pop_Scope();   curr_scope--;}
	;
func_name: IDENT {$$=$1;}
	 |/* empty */ {$$= get_anon_func_name().c_str();} 


func_prefix: FUNCTION func_name { 
		SymbolTableEntry *temp;
		std::string func_name = std::string($func_name);
		functionretstack.push(std::vector<unsigned int>());
		if ((temp = lookUpLIB(func_name)) != NULL) {
		    yyerror("ERROR:: Shadowing a LIB function ");
		} else if ((temp = lookUpScope(func_name, curr_scope)) != NULL) {
		    if (temp->get_type() == var_LOCAL || temp->get_type() == var_FORMAL ||
			temp->get_type() == var_GLOBAL) {
			yyerror("ERROR:: Already assigned a variable with this name ");
		    } else if (temp->get_type() == func_USER) {
			yyerror("ERROR:: Already assigned a function with this name ");
		    }
		} else {
		    insert(func_name, curr_scope, yylineno, func_USER, true, currscopeoffset(),
			   currscopespace());
		    inccurrscopeoffset();
		    temp = lookUpScope(func_name, curr_scope);
		}
		if (temp == NULL) {
		    $$ = NULL;
		} else {
		    $$ = Symbol_to_Expr(temp);
		    //$$->sym->iaddress = nextquad();
		}
		emit(jump, NULL, NULL, NULL, 0, yylineno);
		functionjumpstack.push(nextquad());
		emit(funcstart, $$, NULL, NULL, -1, yylineno);
		scopeoffsetstack.push(currscopeoffset());
		enterscopespace();
		reset_formalargoffset();
	}
func_args : LEFT_PAREN {
	curr_scope++;
	push_Scope(BLOCK);
	} idlist RIGHT_PAREN {
		curr_scope--;
		enterscopespace();
		pop_Scope();
		++inFunction;
		prev_block=FUNC;
		reset_functionlocaloffset();
			};
func_body: block{
		--inFunction;
		$$= currscopeoffset();
		exitscopespace();
		}


funcdef: func_prefix func_args func_body{

		exitscopespace();
		$func_prefix->sym->totalLocals = $func_body;
		int offset = scopeoffsetstack.top();
		scopeoffsetstack.pop();
 		restorecurrscopeoffset(offset); 
		$funcdef = $func_prefix;
		emit(funcend, $funcdef, NULL, NULL , -1 ,yylineno);
		patchlabel(functionjumpstack.top()-1 , nextquad());
		backpatch(functionretstack.top() , nextquad()-1);
		functionjumpstack.pop();
		functionretstack.pop();
       }

const: 	INTCONST { $$ = newexpr_constnum($INTCONST); }
	| REALCONST { $$ = newexpr_constnum($REALCONST); }
	| STRINGCONST { $$ = newexpr_conststring($STRINGCONST); }
	| NIL {  $$ = newexpr(nil_e);  }
	| TRUE {  $$ = newexpr_constbool(true);  }
	| FALSE { $$ = newexpr_constbool(false);  }
	;

idlist:  IDENT { 

		SymbolTableEntry *temp;
		std::string var_name = yylval.stringVal;
		if ((temp = lookUpLIB(var_name)) != NULL) {
		    yyerror("ERROR:: Shadowing libfunc ");
		} else if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
		    if (temp->get_type() == var_FORMAL) {
			yyerror("ERROR:: Formal argument already assigned ");
		    }
		} else {
		    insert(var_name, curr_scope, yylineno, var_FORMAL, true, currscopeoffset(),
			   currscopespace());
		    inccurrscopeoffset();
		}

	 	} idlists
	|/*empty*/ 
	;

idlists: COMMA IDENT {

				SymbolTableEntry *temp;
				std::string var_name = yylval.stringVal;
				if ((temp = lookUpLIB(var_name)) != NULL) {
				    yyerror("ERROR:: Shadowing libfunc ");
				} else if ((temp = lookUpScope(var_name, curr_scope)) != NULL) {
				    if (temp->get_type() == var_FORMAL) {
					yyerror("ERROR:: Formal argument already assigned ");
				    }
				} else {
				    insert(var_name, curr_scope, yylineno, var_FORMAL, true, currscopeoffset(),
					   currscopespace());
				    inccurrscopeoffset();
				}

		} idlists
       |/*empty*/ 
       ;

ifprefix: IF LEFT_PAREN  expr RIGHT_PAREN{

			backpatch($expr->falselist , nextquad()+2);
			backpatch($expr->truelist , nextquad());

if ($expr!=NULL && $expr->inLogical){
			$expr = newexpr(assignexpr_e);
			$expr->sym = new_temp();
			emit(assign , $expr , newexpr_constbool(true) , NULL ,  -1 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , $expr  , newexpr_constbool(false) , NULL , -1 , yylineno);
}
			emit(if_eq, $expr, newexpr_constbool(true), NULL, nextquad()+2, yylineno);
			$$ = nextquad();
			emit(jump,NULL, NULL, NULL, 0, yylineno);
			/* isBackpatch = true; */
	}
	;

elseprefix: ELSE{
				$$ = nextquad();
				emit(jump,NULL,NULL,NULL, 0, yylineno);
				}
	;

ifstmt:	ifprefix stmt {
			patchlabel($ifprefix, nextquad());
			}
	|ifprefix stmt elseprefix stmt{
					patchlabel($ifprefix , $elseprefix + 1);
					patchlabel($elseprefix , nextquad());
								}
	;

whilestart : WHILE {
					$whilestart = nextquad();
					loop_enter();
					}
	;

whilecond :  LEFT_PAREN expr RIGHT_PAREN {
				backpatch($expr->falselist, nextquad() + 2);
				backpatch($expr->truelist, nextquad());

if ($expr!=NULL && $expr->inLogical){
				$expr = newexpr(assignexpr_e);
				$expr->sym = new_temp();
				emit(assign, $expr, newexpr_constbool(true), NULL, -1, yylineno);
				emit(jump, NULL, NULL, NULL, nextquad() + 2, yylineno);
				emit(assign, $expr, newexpr_constbool(false), NULL, -1, yylineno);
				}

				emit(if_eq, $expr, newexpr_constbool(true), NULL, nextquad() + 2, yylineno);
				$whilecond = nextquad();
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				prev_block = FLOW;
				/* isBackpatch = true; */
			}
	;

whilestmt: whilestart whilecond stmt 
	{
		emit(jump, NULL, NULL, NULL, $whilestart, yylineno);
		patchlabel($whilecond, nextquad());
		patch_break(nextquad());
		patch_cont($whilestart);
		loop_exit();
		//edw exi kanti me pathlist  dialeksi 11 telefteo slide
	};

N: {$N = nextquad(); emit(jump ,NULL , NULL , NULL , 0 , yylineno);

					prev_block=FLOW;
}
	;

M: {$M = nextquad();}
	;

forprefix: FOR { loop_enter(); } LEFT_PAREN elist SEMICOLON M expr SEMICOLON	{
		if ($expr->inLogical && isBackpatch == 0) {
			backpatch($expr->falselist, nextquad() + 2);
			backpatch($expr->truelist, nextquad());
			$expr->sym = istempexpr($expr) ? $expr->sym : new_temp();
			emit(assign , $expr , newexpr_constbool(true) , NULL ,  -1 , yylineno);
			emit(jump   , NULL, NULL , NULL , nextquad() + 2  , yylineno);
			emit(assign , $expr  , newexpr_constbool(false) , NULL , -1 , yylineno);
		}
				$forprefix = new forstruct();
				$forprefix->test = $M;
				$forprefix->enter = nextquad();
		emit(if_eq, $expr, newexpr_constbool(true), NULL , 0 , yylineno);
		isBackpatch = 0;
			}

forstmt: forprefix N elist RIGHT_PAREN  N stmt N {
		patchlabel($forprefix->enter , $5+1); // true jumb
		patchlabel($2 , nextquad());          //false jumb
		patchlabel($5 , $forprefix->test);    //loop jumb
		patchlabel($7 , $2+1);               //closure jumb
		patch_break(nextquad());
		patch_cont($2+1);
		loop_exit();
		// edw kati allo kani exra me patchlist dialeksi 11 telefteo slide
		}
	;

returnstmt: RETURN{ 
			if (inFunction == 0) {
			    yyerror("ERROR:: Return outside of function ");
			}
			isReturn = true;
		} expr SEMICOLON {
			isReturn=false;  
			emit(ret , $expr , NULL ,NULL , -1 , yylineno); 
			emit(jump, NULL ,NULL ,NULL ,0 ,yylineno);
			functionretstack.top().push_back(nextquad()-1);
			}
	| RETURN { if(inFunction==0){ yyerror("ERROR:: Return outside of function "); } 
			} SEMICOLON {
				emit(ret , NULL , NULL ,NULL , -1 , yylineno);
				emit(jump, NULL ,NULL ,NULL ,0 ,yylineno);
				functionretstack.top().push_back(nextquad()-1);
			}
	;
	
%%
