#include "parser.hpp"
#include <FlexLexer.h>
#include <cstdio>
#include <string>
extern FILE *yyin, *yyout;

void print_yyout(int line_num, int token_num, std::string token,
                 General_Type gen_Type ,std::string spec_Type , std::string assign_Type) {
  fprintf(yyout, "%d:\t#%d\t\"%s\"\t%s\t%s\t<--(%s)\n", line_num, token_num, token.c_str(),
          str_General_Type[gen_Type],spec_Type.c_str(), assign_Type.c_str());
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
  fprintf(yyout,
          "--------------------   Lexical Analysis   --------------------\n\n");
  std::vector<alpha_token_t> tokens;
  alpha_yylex(tokens);
  for (auto token : tokens) {
    print_yyout(token.num_line, token.num_Token, token.Token,
                token.gen_Type , token.spec_Type,token.assign_Type);
  }
  return 0;
}
