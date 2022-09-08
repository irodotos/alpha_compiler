#ifndef PARSER
#define PARSER
#include <iostream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
enum General_Type {
  UNDEFINED = 0,
  KEYWORD,
  INTCONST,
  REALCONST,
  OPERATOR,
  STRING,
  PUNCTUATION,
  IDENT,
  COMMENT
};
static const char *str_General_Type[9] = {"UNDEFINED",   "KEYWORD",  "INTCONST",
                                          "REALCONST",   "OPERATOR", "STRING",
                                          "PUNCTUATION", "IDENT",    "COMMENT"};
struct alpha_token_t {
  alpha_token_t(unsigned int _line_num, unsigned int _num_token,
                std::string _token, General_Type _gen_Type,
                std::string _spec_Type, std::string _assign_Type)
      : num_line(_line_num), num_Token(_num_token), Token(_token),
        gen_Type(_gen_Type), spec_Type(_spec_Type), assign_Type(_assign_Type){};
  unsigned int num_line;
  unsigned int num_Token;
  std::string Token;
  General_Type gen_Type;
  // Specific_Type spec_Type;
  std::string spec_Type;
  std::string assign_Type;
};
int alpha_yylex(std::vector<alpha_token_t> &tokens);
void print_yyout(int line_num, int token_num, std::string token, General_Type,
                 std::string spec_Type, std::string assign_Type);
#endif
