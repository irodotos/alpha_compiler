#include "quad.hpp"
#include <vector>

std::vector<quad *> quads;
std::stack<std::vector<int>> breakList;
std::stack<std::vector<int>> contList;

bool comp_error = false;
unsigned total = 0;
unsigned int currQuad = 1;
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;
extern int yylineno;

bool isInteger(double N) {
  int X = N;
  double ipolipo = N - X;
  if (ipolipo > 0) {
    return false;
  }
  return true;
}

void emit(iopcode op, expr *result, expr *arg1, expr *arg2, unsigned label,
          unsigned line) {
  quad *temp = new quad();
  temp->op = op;
  temp->result = result;
  temp->arg1 = arg1;
  temp->arg2 = arg2;
  temp->label = label;
  temp->line = line;
  temp->iaddress = currQuad++;
  quads.push_back(temp);
}

expr *Symbol_to_Expr(SymbolTableEntry *sym) {
  assert(sym);
  expr *temp = new expr();
  temp->next = (expr *)0;
  temp->sym = sym;
  if (sym->get_type() == var_LOCAL) {
    temp->type = var_e;
  } else if (sym->get_type() == var_GLOBAL) {
    temp->type = var_e;
  } else if (sym->get_type() == var_FORMAL) {
    temp->type = var_e;
  } else if (sym->get_type() == func_USER) {
    temp->type = programfunc_e;
  } else if (sym->get_type() == func_LIB) {
    temp->type = libraryfunc_e;
  } else {
    assert(0);
  }

  // MPORI NA THELI NA PROSTHESW KALIA STO TEMP ???????????
  return temp;
}

expr *newexpr(expr_t type) {
  expr *temp = new expr();
  temp->type = type;
  return temp;
}

void print_quads() {
  // int quad_num = 1;
  if (comp_error) {
    printf("INFO:: Compilation Failed!\n");
    return;
  }
  printf("\nquad#  │  %-15s  │  %-15s  │  %-15s  │  %-10s  │  %-5s  │  %-5s\n"
         "───────┼───────────────────┼───────────────────┼───────────────────┼─"
         "──────────"
         "───┼─────────┼───────────\n",
         "opcode", "result", "arg1", "arg2", "label", "line");
  for (auto quad : quads) {
    if (quad->label == 0) {
      printf("#%-5d │  %-15s  │  %-15s  │  %-15s  │  %-10s  │  %-5s  │  %d\n",
             quad->iaddress, opToString(quad->op).c_str(),
             exprToString(quad->result).c_str(),
             exprToString(quad->arg1).c_str(), exprToString(quad->arg2).c_str(),
             "", quad->line);
    } else {
      printf("#%-5d │  %-15s  │  %-15s  │  %-15s  │  %-10s  │  %-5d  │  %d\n",
             quad->iaddress, opToString(quad->op).c_str(),
             exprToString(quad->result).c_str(),
             exprToString(quad->arg1).c_str(), exprToString(quad->arg2).c_str(),
             quad->label, quad->line);
    }
  }
}
std::string exprToString(expr *e) {
  if (e == NULL)
    return "";
  switch (e->type) {
  case var_e:
    return e->sym->get_name();
  case constnum_e: {
    double num = e->numConst;
    if (isInteger(num)) {
      return std::to_string(static_cast<int>(num));
    } else
      return std::to_string(num);
  }
  case constbool_e:
    return e->boolConst ? "TRUE" : "FALSE";
  case tableitem_e:
    return e->sym->get_name();
  case libraryfunc_e:
    return e->sym->get_name();
  case arithexpr_e:
    return e->sym->get_name();
  case conststring_e:
    return "\"" + e->strConst + "\"";
  case newtable_e:
    return e->sym->get_name();
  case nil_e:
    return "NIL";
  case programfunc_e:
    return e->sym->get_name();
  case boolexpr_e:
    return e->sym->get_name();
  case assignexpr_e:
    return e->sym->get_name();
  default:
    return "FAIL";
  }
}

std::string opToString(iopcode op) {
  switch (op) {
  case assign:
    return "assign";
  case add:
    return "add";
  case sub:
    return "sub";
  case mul:
    return "mul";
  case div_:
    return "div";
  case uminus:
    return "uminus";
  case mod:
    return "mod";
  case if_eq:
    return "if_eq";
  case if_noteq:
    return "if_not_eq";
  case if_lesseq:
    return "if_lesseq";
  case if_greatereq:
    return "if_greatereq";
  case if_greater:
    return "if_greater";
  case if_less:
    return "if_less";
  case call:
    return "call";
  case ret:
    return "return";
  case getretval:
    return "getretval";
  case funcstart:
    return "funcstart";
  case funcend:
    return "funcend";
  case jump:
    return "jump";
  case tablecreate:
    return "tablecreate";
  case tablegetelem:
    return "tablegetelem";
  case tablesetelem:
    return "tablesetelem";
  case param:
    return "param";
  // case not_c:
  //   return "not";
  // case or_c:
  //   return "or";
  // case and_c:
  //   return "and";
  default:
    return "";
  }
}

scopespace_t currscopespace() {
  if (scopeSpaceCounter == 1) {
    return programvar;
  } else {
    if (scopeSpaceCounter % 2 == 0) {
      return formalarg;
    } else {
      return functionlocal;
    }
  }
}

unsigned currscopeoffset() {
  switch (currscopespace()) {
  case programvar:
    return programVarOffset;
  case functionlocal:
    return functionLocalOffset;
  case formalarg:
    return formalArgOffset;
  default:
    assert(0);
  }
}

void inccurrscopeoffset() {
  switch (currscopespace()) {
  case programvar:
    ++programVarOffset;
    break;
  case functionlocal:
    ++functionLocalOffset;
    break;
  case formalarg:
    ++formalArgOffset;
    break;
  default:
    assert(0);
  }
}

void enterscopespace() { ++scopeSpaceCounter; }

void exitscopespace() {
  assert(scopeSpaceCounter > 1);
  --scopeSpaceCounter;
}

void reset_functionlocaloffset() { functionLocalOffset = 0; }

void reset_formalargoffset() { formalArgOffset = 0; }

void restorecurrscopeoffset(unsigned n) {
  switch (currscopespace()) {
  case programvar:
    programVarOffset = n;
    break;
  case functionlocal:
    functionLocalOffset = n;
    break;
  case formalarg:
    formalArgOffset = n;
    break;
  default:
    assert(0);
  }
}

unsigned nextquad() { return currQuad; }

expr *newexpr_constnum(double i) { 
  expr *e = newexpr(constnum_e);
  e->numConst = i;
  return e;
}

expr *newexpr_constbool(bool val) {
  expr *e = newexpr(constbool_e);
  e->boolConst = val;
  return e;
}

expr *newexpr_conststring(std::string val) {
  expr *e = newexpr(conststring_e);
  e->strConst = val;
  return e;
}

void comperror(const char *message) {
  comp_error = true;
  fprintf(stderr, "ERROR, %s\n", message);
}
void comperror() { comp_error = true; }

void check_arithm(
    expr *e,
    const char *message) { // xrisimopiite sto uminus gia na sigoureftoume an
                           // einai number to expr
  if (e->type == constbool_e || e->type == conststring_e || e->type == nil_e ||
      e->type == newtable_e || e->type == programfunc_e ||
      e->type == libraryfunc_e || e->type == boolexpr_e) {
    comperror(message);
  }
}

unsigned int
istempname(std::string s) { // gia epanaxtisimopiisi krifwn metavlitwn
  return s[0] == '_';
}

unsigned int istempexpr(expr *e) { ////gia epanaxtisimopiisi krifwn metavlitwn
  return e->sym && istempname(e->sym->get_name());
}

// void give_offset_space(SymbolTableEntry* sym){
//     sym->offset = currscopeoffset();
//     sym->space = currscopespace();
//     inccurrscopeoffset();
// }

expr *emit_iftableitem(expr *e) {
  if (e->type != tableitem_e) {
    return e;
  } else {
    expr *result = newexpr(var_e);
    result->sym = new_temp();
    emit(tablegetelem, result, e, e->index, 0,
         e->sym->line); /*!!!!!!!!!!!!!ta dyo teleutaia orismata*/
    return result;
  }
}

expr *member_item(expr *lvalue, const char *name) {
  lvalue = emit_iftableitem(lvalue);
  expr *item = newexpr(tableitem_e);
  item->sym = lvalue->sym;
  item->index = newexpr_conststring(name);
  return item;
}

expr *reverse_elist(expr *elist) {

  expr *current = elist;
  expr *prev = NULL, *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  elist = prev;
  return elist;
}

expr *make_call(expr *lv, expr *reversed_elist) {
  reversed_elist = reverse_elist(reversed_elist);
  expr *func = emit_iftableitem(lv);
  while (reversed_elist) {
    emit(param, reversed_elist, NULL, NULL, 0, yylineno);
    reversed_elist = reversed_elist->next;
  }
  emit(call, func, NULL, NULL, 0, yylineno);
  expr *result = newexpr(var_e);
  result->sym = new_temp();
  emit(getretval, result, NULL, NULL, 0, yylineno);
  return result;
}

void loop_enter() {
  std::vector<int> newBreakList;
  std::vector<int> newContList;
  breakList.push(newBreakList);
  contList.push(newContList);
}
void patch_break(int label) {
  for (int i : breakList.top()) {
    patchlabel(i, label);
  }
}
void patch_cont(int label) {
  for (int i : contList.top()) {
    patchlabel(i, label);
  }
}
void insert_break(int label) { breakList.top().push_back(label); }
void insert_cont(int label) { contList.top().push_back(label); }
void loop_exit() {
  breakList.pop();
  contList.pop();
}
SymbolTableEntry *recycle_temp(expr *E1, expr *E2) {
  if (istempexpr(E1)){
    inccurrscopeoffset();
    return E1->sym;
  }
  else if (istempexpr(E2)){
    inccurrscopeoffset();
    return E2->sym;
  }
  else
    return new_temp();
}

void patchlabel(unsigned quadNo, unsigned label) {
  assert(quadNo < currQuad);
  // assert(quads[quadNo - 1]->label == 0);
  quads[quadNo - 1]->label = (float)label;
}

void backpatch(std::vector<unsigned int> &list, unsigned quad) {
  for (auto patch : list) {
    patchlabel(patch, quad);
  }
}
expr *relop(expr *E1, iopcode op, expr *E2) {

  expr *E;
  E = newexpr(var_e);
  E->inLogical = true;
  E->truelist.push_back(nextquad());
  E->falselist.push_back(nextquad() + 1);
  // E->sym = recycle_temp(E1, E2);
  E->sym = NULL;
  emit(op, NULL, E1, E2, 0, yylineno);
  emit(jump, NULL, NULL, NULL, 0, yylineno);
  return E;
}
std::vector<unsigned int> mergelists(std::vector<unsigned int> &list1,
                                     std::vector<unsigned int> &list2) {
  std::vector<unsigned int> temp(list1);
  temp.insert(temp.end(), list2.begin(), list2.end());
  return temp;
}

