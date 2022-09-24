#include "quad.hpp"
#include "symbol_table.hpp"
#include "t_code.hpp"
#include <FlexLexer.h>
#define VERBOSE
extern FILE *yyin, *yyout;
extern int yylineno;
extern char *yytext;
int yyparse();
void init_Input(int argc, char **argv);

int main(int argc, char **argv) {

  init_Input(argc, argv);
  init_Libfunc();
  yyparse();
#ifdef VERBOSE
  print_symtable();
  print_quads();
#endif // VERBOSE

  generate_all();
  create_bytecode_file();

  return 0;
}

void init_Input(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    printf("ERROR:: Wrong arguments.\nEg.: $ ./My_Scanner input_file "
           "optional_out_file\n");
    assert(0);
  }
  if (!(yyin = fopen(argv[1], "r"))) {
    printf("ERROR:: File \"%s\" could not be read.(EXITING)\n", argv[1]);
    assert(0);
  }
  if (argc == 3) {
    if (!(yyout = fopen(argv[2], "w"))) {
      printf("ERROR:: File \"%s\" could not be writen to.(EXITING)\n", argv[2]);
      assert(0);
    }
  } else {
    yyout = stdout;
  }
}

int yyerror(char *YaccERROR) {
  fprintf(stderr, "%s: at line %d,before token: \"%s\" !\n", YaccERROR,
          yylineno, yytext);
  comperror();
  return 2;
}
