#include "symbol_table.hpp"
#include <FlexLexer.h>
#include <assert.h>
#include <cstdio>
#include <string>
extern FILE *yyin, *yyout;
extern int yylineno;
extern char *yytext;
extern std::map<std::string, std::vector<SymbolTableEntry>> symbol_table;
extern std::map<unsigned int, std::vector<SymbolTableEntry>> scope_lists;
int yyparse();


int yyerror( char *YaccERROR) {
  fprintf(stderr, "%s: at line %d,before token: \"%s\" !\n", YaccERROR,
          yylineno, yytext);
  return 2;
}


int main(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    printf("ERROR:: Wrong arguments.\nEg.: $ ./My_Scanner input_file "
           "optional_out_file\n");
    return 2;
  }
  if (!(yyin = fopen(argv[1], "r"))) {
    printf("ERROR:: File \"%s\" could not be read.(EXITING)\n", argv[1]);
    return 2;
  }
  if (argc == 3) {
    if (!(yyout = fopen(argv[2], "w"))) {
      printf("ERROR:: File \"%s\" could not be writen to.(EXITING)\n", argv[2]);
      return 2;
    }
  } else {
    yyout = stdout;
  }
	init_Libfunc();
  yyparse();

  // for (auto a : Sym_Table.symbol_table) {
  //   for (auto a : a.second) {
  //     a.print();
  //   }
  // }

//   for (int i =0 ;i<Sym_Table.scope_lists.size();i++) {
// printf("\n---------------------- SCOPE %d ---------------------\n\n",i);
//     for (auto a : Sym_Table.scope_lists.at(i)) {
//       a.print();
//     }
//   }
for (auto list_of_scopes : scope_lists) {
	printf("\n-------------------------- SCOPE %d -----------------------\n\n",list_of_scopes.first);
	for (auto a : list_of_scopes.second) {
		a.print();
	}
}
  // auto item = Sym_Table.lookUp("IRO");
  // if (item != NULL) {
  //   for (auto a : *item) {
  //     a.print();
  //   }
  // }else {
  // printf("NOT found!");
  // }
  // for (auto token : tokens) {
  // 	print_yyout(token.num_line, token.num_Token, token.Token,
  // token.gen_Type,
  //       token.spec_Type, token.assign_Type);
  // }

  return 0;
}
