#ifndef QUAD_H
#define QUAD_H
#include "symbol_table.hpp"
#include <cassert>
#include <set>

enum iopcode {
  add,
  sub,
  mul,
  div_,
  mod,
  tablecreate,
  tablegetelem,
  tablesetelem,
  assign,
  uminus,
  jump,
  // and_c,
  // or_c,
  // not_c,
  if_eq,
  if_noteq,
  if_greater,
  if_greatereq,
  if_less,
  if_lesseq,
  param,
  call,
  getretval,
  funcstart,
  ret,
  funcend,
  nop
};

enum expr_t {
  var_e,
  tableitem_e,

  programfunc_e,
  libraryfunc_e,

  arithexpr_e,
  boolexpr_e,
  assignexpr_e,
  // logicalop_e,
  newtable_e,

  constnum_e,
  constbool_e,
  conststring_e,

  nil_e
};

struct expr {
  expr_t type;
  SymbolTableEntry *sym;
  expr *index;
  double numConst;
  std::string strConst;
  unsigned char boolConst;
  std::vector<unsigned int> truelist, falselist;
  bool not_c = false;
  bool inLogical = false;
  struct expr *next;
};

struct quad {
  iopcode op;
  expr *result;
  expr *arg1;
  expr *arg2;
  unsigned label;
  unsigned line;
  unsigned iaddress;
  unsigned taddress;
};

struct forstruct {
  int test;
  int enter;
};

struct callstruct {
  expr *elist;
  unsigned char method;
  const char *name;
};

struct indexedstruct {
  expr *index;
  expr *element;
  indexedstruct *next;
};

expr *Symbol_to_Expr(SymbolTableEntry *sym);
void emit(iopcode op, expr *result, expr *arg1, expr *arg2, unsigned label,
          unsigned line);
expr *newexpr(expr_t type);
std::string exprToString(expr *expr);
std::string opToString(iopcode op);
// void give_offset_space(SymbolTableEntry* sym);
scopespace_t currscopespace();
unsigned currscopeoffset();
void inccurrscopeoffset();
void reset_functionlocaloffset();
void reset_formalargoffset();
void enterscopespace();
void exitscopespace();
void restorecurrscopeoffset(unsigned n);
unsigned nextquad();
void patchlabel(unsigned quadNo, unsigned label);
expr *newexpr_constnum(double i);
unsigned int istempname(char *s);
unsigned int istempexpr(expr *e);
void check_arithm(expr *e, const char *message);
expr *newexpr_constbool(bool val);
expr *newexpr_conststring(std::string val);
void print_quads();
expr *member_item(expr *lvalue, const char *name);
expr *emit_iftableitem(expr *e);
expr *make_call(expr *lv, expr *reversed_elist);
expr *reverse_elist(expr *elist);

void loop_enter();
void patch_break(int label);
void patch_cont(int label);
void insert_break(int label);
void insert_cont(int label);
void loop_exit();
void comperror(const char *message);
void comperror();
expr *relop(expr *E1, iopcode op, expr *E2);
void backpatch(std::vector<unsigned int> &list, unsigned quad);
std::vector<unsigned int> mergelists(std::vector<unsigned int> &list1,
                                     std::vector<unsigned int> &list2);
SymbolTableEntry *recycle_temp(expr *E1, expr *E2);
#endif // !QUAD_H
