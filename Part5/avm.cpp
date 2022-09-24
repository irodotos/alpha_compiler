#include "avm.hpp"
#include <array>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define execute_uminus execute_arithmetic
#define execute_jle execute_relational
#define execute_jge execute_relational
#define execute_jlt execute_relational
#define execute_jgt execute_relational
#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1
#define AVM_MAX_INSTRUCTIONS 23
#define PI 3.14159
#define AVM_ENDING_PC instructions.size()
using library_func_t = void (*)(void);
extern const char *vmarg_t_string[];
extern const char *vmopcode_t_string[];

const char *avm_memcell_t_string[] = {
    "number_m",   "string_m",  "bool_m", "table_m",
    "userfunc_m", "libfunc_m", "nil_m",  "undef_m",
};
unsigned programVarOffset;
extern std::vector<std::string> stringConst;
extern std::vector<avm_memcell*> numberConst;
extern std::vector<userfunc> userfunctionConst;
extern std::vector<std::string> libConst;
extern std::vector<instruction *> instructions;

std::unordered_map<std::string, library_func_t> avm_libFuncs;
int top = AVM_STACKSIZE - 1, topsp = AVM_STACKSIZE - 1, totalActuals = 0,
    pc = 0;
int globs = 0;
int restore_pc = 0;
bool executionStop = false;
int curr_func_top = 0;
int in_function = 0;

avm_memcell ax, bx, cx;
avm_memcell retval;
std::array<avm_memcell, AVM_STACKSIZE> mem_stack;

std::string avm_tostring(avm_memcell *m);
void avm_tabledestroy(avm_table *t) { t->~avm_table(); }
void avm_tableincrefcounter(avm_table *t) { ++(t->refCounter); }
void avm_tabledecrefcounter(avm_table *t) {
  assert(t->refCounter > 0);
  if (!--t->refCounter) {
    avm_tabledestroy(t);
  }
}
void avm_warning(const char *msg) { printf("WARNING:: %s \n", msg); }

void avm_error(const char *msg) {
  printf("ERROR:: %s \n", msg);
  executionStop = true;
}
std::vector<std::string> split(std::string str) {
  auto ss = std::stringstream(str);
  std::vector<std::string> tokens;
  std::string s;
  while (std::getline(ss, s, ' ')) {
    tokens.push_back(s);
  }
  return tokens;
}
void binary_parser() {

  std::string input;
  std::string size;
  std::ifstream abcCode("code.abc");
  std::getline(abcCode, input);
  if (input != "69696969") {
    std::cout << "Not an Alpha file. EXITING...\n";
    return;
  }

  std::getline(abcCode, input);
  programVarOffset = std::stoi(input);

  std::getline(abcCode, size);
  for (int i = 0; i < std::stoi(size); i++) {
    std::getline(abcCode, input);
    stringConst.push_back(input);
  }

  std::getline(abcCode, size);
  for (int i = 0; i < std::stoi(size); i++) {
    std::getline(abcCode, input);
    avm_memcell* temp = new avm_memcell();
    temp->type = number_m;
    temp->data.numVal = std::stod(input);
    numberConst.push_back(temp);
  }

  std::getline(abcCode, size);
  for (int i = 0; i < std::stoi(size); i++) {
    std::getline(abcCode, input);
    userfunctionConst.push_back(input_to_userfunc(input));
  }

  std::getline(abcCode, size);
  for (int i = 0; i < std::stoi(size); i++) {
    std::getline(abcCode, input);
    libConst.push_back(input);
  }

  while (std::getline(abcCode, input)) {
    auto instruction = split(input);
    auto temp =
        new_instruction(static_cast<vmopcode>(std::stoi(instruction[0])));
    temp->result->type = static_cast<vmarg_t>(std::stoi(instruction[1]));
    temp->result->val = std::stoi(instruction[2]);
    temp->arg1->type = static_cast<vmarg_t>(std::stoi(instruction[3]));
    temp->arg1->val = std::stoi(instruction[4]);
    temp->arg2->type = static_cast<vmarg_t>(std::stoi(instruction[5]));
    temp->arg2->val = std::stoi(instruction[6]);
    temp->srcLine = std::stoi(instruction[7]);
    emit_instraction(temp);
  }
}

userfunc input_to_userfunc(std::string func) {
  auto temp = split(func);
  return userfunc(std::stoi(temp[0]), std::stoi(temp[1]), temp[2]);
}
void avm_register_libFunc(const char *name, library_func_t func) {
  avm_libFuncs.insert({name, func});
}

void print_mem_globals() {
  std::cout << "================================" << std::endl;

  std::cout << globs << std::endl;
  for (int i = AVM_STACKSIZE - 1; i > AVM_STACKSIZE - globs; i--) {
    std::cout << i << " " << mem_stack[i].type << mem_stack[i].type
              << std::endl;
  }
}

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg) {
  switch (arg->type) {
    case global_a: {
      ++globs;
      printf("eimai sta olobals\n");
      // switch (arg->type) {
      // cases
      // }
      // mem_stack[AVM_STACKSIZE - 1 - (arg->val)].data.numVal = arg->val;
      return &mem_stack[AVM_STACKSIZE - 1 - (arg->val)];
    }
    case local_a:{
      avm_memcell* temp = new avm_memcell();
      temp = &mem_stack[topsp - (arg->val)];
      temp->type = number_m;
      //return &mem_stack[topsp - (arg->val)];
      return temp;
    }
    case formal_a:
      return &mem_stack[topsp + AVM_STACKENV_SIZE + 1 + (arg->val)];
    case retval_a:
      return &retval;
    case number_a: {
      reg->type = number_m;
      reg->data.numVal = numberConst[arg->val]->data.numVal;
      return reg;
    }
    case string_a: {
      reg->type = string_m;
      reg->data.strVal = stringConst[arg->val].c_str();
      return reg;
    }
    case bool_a: {
      reg->type = bool_m;
      reg->data.boolVal = arg->val;
      return reg;
    }
    case nil_a: {
      reg->type = nil_m;
      return reg;
    }
    case userfunc_a: {
      reg->type = userfunc_m;
      reg->data.funcVal = arg->val;
      return reg;
    }
    case libfunc_a: {
      reg->type = libfunc_m;
      reg->data.libfuncVal = libConst[arg->val].c_str();
      return reg;
    }
    default:
      avm_warning("no type found\n");
      return nullptr;
      break;
    }
}
typedef void (*memclear_func_t)(avm_memcell *);

void memclear_string(avm_memcell *m) {
  assert(m->data.strVal);
  free((char *)m->data.strVal);
}

void memclear_table(avm_memcell *m) {
  assert(m->data.tableVal);
  avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[] = {
    0,
    memclear_string, /* string */
    0,               /* bool */
    memclear_table,  /* table */
    0,               /* userfunc */
    0,               /* libfunc */
    0,               /* nil */
    0,               /* undef */
};

/*When a cell is cleared, it has to destroy all
  dynamic data content or reset its reference to a table.*/
void avm_memcellclear(avm_memcell *m) {
  if (m->type != undef_m) {
    memclear_func_t f = memclearFuncs[m->type];
    if (f) {
      (*f)(m);
    }
    m->type = undef_m;
  }
}
void avm_assign(avm_memcell *lv, avm_memcell *rv) {
  if (lv == rv) {
    printf("Same cells assign\n");
    return;
  }

  if (lv->type == table_m && rv->type == table_m &&
      lv->data.tableVal == rv->data.tableVal) {
    printf("Same tables assign\n");

    return;
  }

  if (rv->type == undef_m) {
    avm_warning("assigning from 'undef' content!");
  }

  avm_memcellclear(lv);
  memcpy(lv, rv, sizeof(avm_memcell));
  // lv = rv;

  if (lv->type == string_m) {
    lv->data.strVal = strdup(rv->data.strVal);
  } else if (lv->type == table_m) {
    avm_tableincrefcounter(lv->data.tableVal);
  }
}
void avm_dec_top(void) {
  if (!top) {
    avm_error("Stack Overflow");
    executionStop = true;
  } else {
    --top;
  }
}
void avm_push_envvalue(unsigned val) {
  mem_stack[top].type = number_m;
  mem_stack[top].data.numVal = val;
  avm_dec_top();
}
void avm_callsaveenvironment() {
  avm_push_envvalue(totalActuals);
  avm_push_envvalue(pc + 1);
  avm_push_envvalue(top + totalActuals + 2);
  avm_push_envvalue(topsp);
}
typedef void (*execute_func_t)(instruction *);

void execute_assign(instruction *instr) {
#ifdef VERBOSE
  printf("execute_assign\n");
#endif //
  avm_memcell *lv = avm_translate_operand((instr->result), (avm_memcell *)0);
  avm_memcell *rv = avm_translate_operand((instr->arg1), &ax);

  assert(lv && (&mem_stack[AVM_STACKSIZE - 1] >= lv && lv > &mem_stack[top] ||
                lv == &retval));
  assert(rv);

  avm_assign(lv, rv);
}

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
double div_impl(double x, double y) {
  if (y != 0) {
    return x / y;
  } else {
    avm_error("Division by 0");
    return 0.0;
  }
}
double mod_impl(double x, double y) {
  if (y != 0) {
    return ((unsigned)x) % ((unsigned)y);
  } else {
    avm_error("Mod by 0");
    return 0.0;
  }
}

double unimus_impl(double x, double) { return x *= -1; }
arithmetic_func_t arithmeticFuncs[] = {
    add_impl, sub_impl, mul_impl, div_impl, mod_impl, unimus_impl,
};

void execute_add(instruction *instr);
void execute_sub(instruction *instr);
void execute_mul(instruction *instr);
void execute_div(instruction *instr);
void execute_mod(instruction *instr);
void execute_uminus(instruction *instr);
void execute_arithmetic(instruction *instr) {
#ifdef VERBOSE
  printf("execute_arithmetic\n");
#endif //
  avm_memcell *lv = avm_translate_operand((instr->result), (avm_memcell *)0);
  avm_memcell *rv1 = avm_translate_operand((instr->arg1), &ax);
  avm_memcell *rv2 = avm_translate_operand((instr->arg2), &bx);

  assert(lv && (&mem_stack[AVM_STACKSIZE - 1] >= lv && lv > &mem_stack[top] ||
                lv == &retval));
  assert(rv1 && (instr->opcode == uminus_v || rv2));

  if (rv1->type == number_m &&
      (instr->opcode == uminus_v || rv2->type == number_m)) {
    arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = (*op)(rv1->data.numVal,
                            instr->opcode == uminus_v ? 0 : rv2->data.numVal);
  } else {
    avm_error("not a number arithmetic!");
  }
}

using to_bool = bool (*)(avm_memcell *);

bool number_tobool(avm_memcell *m) { return m->data.numVal != 0; }
bool string_tobool(avm_memcell *m) { return m->data.strVal[0] != 0; }
bool bool_tobool(avm_memcell *m) { return m->data.boolVal; }
bool table_tobool(avm_memcell *m) { return 1; }
bool userfunc_tobool(avm_memcell *m) { return 1; }
bool libfunc_tobool(avm_memcell *m) { return 1; }
bool nil_tobool(avm_memcell *m) { return 0; }
bool undef_tobool(avm_memcell *m) {
  assert(0);
  return 0;
}

to_bool toboolFuncs[] = {
    number_tobool,   string_tobool,  bool_tobool, table_tobool,
    userfunc_tobool, libfunc_tobool, nil_tobool,  undef_tobool,
};

bool avm_tobool(avm_memcell *m) {
  assert(m->type >= number_m && m->type < undef_m);
  return (toboolFuncs[m->type])(m);
}

using comp_func = bool (*)(avm_memcell *rv1, avm_memcell *rv2);

bool number_cmp(avm_memcell *rv1, avm_memcell *rv2) {
  return rv1->data.numVal == rv2->data.numVal;
}
bool string_cmp(avm_memcell *rv1, avm_memcell *rv2) {
  return strcmp(rv1->data.strVal, rv2->data.strVal) == 0 ? true : false;
}

comp_func cmp_dispatch[] = {number_cmp, string_cmp, 0, 0, 0, 0, 0, 0};

void execute_jeq(instruction *instr) {

  printf("execute_jeq\n");

  assert(instr->result->type == label_a);

  avm_memcell *rv1 = avm_translate_operand((instr->arg1), &ax);
  avm_memcell *rv2 = avm_translate_operand((instr->arg2), &bx);

  bool result = false;

  if (rv1->type == undef_m  ) {
    avm_error("'undef 1' involved in comparing");
  }else if (rv2->type == undef_m){
    avm_error("undef 2");
  } else if (rv1->type == nil_m || rv2->type == nil_m) {
    std::cout<<"NILLLLLLL\n";
    result = rv1->type == nil_m && rv2->type == nil_m;
  } else if (rv1->type == bool_m || rv2->type == bool_m) {
    std::cout<<"BOOOLLLLL\n";
    std::cout<<"rv1 type = " << rv1->type <<"\n";
    std::cout<<"rv2 type = " << rv2->type <<"\n";
    result = (avm_tobool(rv1) == avm_tobool(rv2));
    std::cout<<"rv1 bool = " << avm_tobool(rv1) <<"\n";
    std::cout<<"rv2 bool = " << avm_tobool(rv2) <<"\n";
    std::cout<<"result sto eq = " << result <<"\n";
  } else if (rv1->type != rv2->type) {
    avm_error("Comparing diffrent types of arguments");
    printf("%s == %s is illegal", avm_memcell_t_string[rv1->type],
           avm_memcell_t_string[rv2->type]);
  } else {
    std::cout<<"ELSE\n";

    result = (cmp_dispatch[rv1->type])(rv1, rv2);
  }

  if (!executionStop && result) {
    // std::cout<<"yes\n";
    pc = instr->result->val - 1;
    std::cout<<"PC after eq true = " << pc <<"\n";
  }
}

void execute_jne(instruction *instr) {
#ifdef VERBOSE
  printf("execute_jne\n");
#endif //
  assert(instr->result->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  bool result = false;

  if (rv1->type == undef_m  ) {
    avm_error("'undef 1' involved in comparing");
  }else if (rv2->type == undef_m){
    avm_error("undef 2");
  } else if (rv1->type == nil_m || rv2->type == nil_m) {
    result = rv1->type == nil_m && rv2->type == nil_m;
  } else if (rv1->type == bool_m || rv2->type == bool_m) {
    result = (avm_tobool(rv1) != avm_tobool(rv2));
  } else if (rv1->type != rv2->type) {
    avm_error("Comparing diffrent types of arguments");
    printf("%s != %s is illegal", avm_memcell_t_string[rv1->type],
           avm_memcell_t_string[rv2->type]);
  } else {
    result = (cmp_dispatch[rv1->type])(rv1, rv2);
  }

  if (!executionStop && !result) {
    pc = instr->result->val;
  }
}

using cmp_val = bool (*)(double x, double y);

bool less_eq(double x, double y) { return x <= y; }
bool greater_eq(double x, double y) { return x >= y; }
bool less(double x, double y) { printf("less\n");return x < y; }
bool greater(double x, double y) { return x > y; }

cmp_val comparisonFuncs[] = {less_eq, greater_eq, less, greater};

void execute_jle(instruction *instr);
void execute_jge(instruction *instr);
void execute_jlt(instruction *instr);
void execute_jgt(instruction *instr);

void execute_relational(instruction *instr) {
  std::cout<<"relational"<<"\n";
  assert(instr->result->type == label_a);

  avm_memcell *rv1 = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *rv2 = avm_translate_operand(instr->arg2, &bx);

  assert(rv1 && rv2);

  bool result = 0;
  // printf("%s\n" , rv1->data);
  // printf("%s\n" , rv2->data);
  if (rv1->type == undef_m  ) {
    avm_error("'undef 1' involved in comparing");
  }else if (rv2->type == undef_m){
    avm_error("undef 2");
  } else if (rv1->type == nil_m || rv2->type == nil_m) {
    result = rv1->type == nil_m && rv2->type == nil_m;
  } else if (rv1->type == bool_m || rv2->type == bool_m) {
    result = (avm_tobool(rv1) == avm_tobool(rv2));
  } else if (rv1->type != rv2->type) {
    avm_error("Comparing diffrent types of arguments");
    printf("%s == %s is illegal", avm_memcell_t_string[rv1->type],
           avm_memcell_t_string[rv2->type]);
  } else {
    printf("eimai stin sigkrisi arithmwn\n");
    cmp_val op;
    if(instr->opcode == if_lesseq_v){
      op = comparisonFuncs[0];
    }
    else if(instr->opcode == if_greatereq_v){
      op = comparisonFuncs[1];
    }
    else if(instr->opcode == if_less_v){
      op = comparisonFuncs[2];
    }
    else{
      op = comparisonFuncs[3];
    }
    // cmp_val op = comparisonFuncs[instr->opcode - 10];
    std::cout<<"OP = " << op<<"\n";
    result = (op)(rv1->data.numVal, rv2->data.numVal);
    std::cout<<result<<"\n";
  }

  if (!executionStop && result) {
    pc = instr->result->val;
  }
}
// ========================================

// void execute_jle(instruction *) {}
// void execute_jge(instruction *) {}
// void execute_jlt(instruction *) {}
// void execute_jgt(instruction *) {}
void execute_call(instruction *);

void execute_pusharg(instruction *instr) {
#ifdef VERBOSE
  printf("execute_pusharg\n");
#endif //
  avm_memcell *arg = avm_translate_operand(instr->result, &ax);
  assert(arg);
  avm_assign(&mem_stack[top], arg);
  ++totalActuals;
  avm_dec_top();
}
userfunc *avm_getfuncinfo(unsigned address) {

  for (auto &fun : userfunctionConst) {
    if (fun.address - 1 == address) {
      return &fun;
    }
  }
  return NULL;
}
void execute_funcenter(instruction *instr) {
#ifdef VERBOSE
  printf("execute_funcenter\n");
#endif //
  avm_memcell *func = avm_translate_operand(instr->result, &ax);
  assert(func);
  assert(pc == userfunctionConst[func->data.funcVal].address - 1);
  in_function++;
  totalActuals = 0;
  userfunc *funcInfo = avm_getfuncinfo(pc);
  topsp = top;
  top = top - funcInfo->localsize;
}

unsigned avm_get_envvalue(unsigned i) {
  assert(mem_stack[i].type == number_m);
  unsigned val = (unsigned)mem_stack[i].data.numVal;
  assert(mem_stack[i].data.numVal == ((double)val));
  return val;
}

void execute_funcexit(instruction *instr) {
#ifdef VERBOSE
  printf("execute_funcexit\n");
#endif //
  // if (instructions[restore_pc]->opcode == 16) {
  unsigned oldTop = top;

  top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
  pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
  topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

  /* Ka8arismos Activation record ( garbage collection )*/
  while (++oldTop <= top) { /* Agnooume to prwto epitides*/
    avm_memcellclear(&mem_stack[oldTop]);
  }

  in_function--;
}
// void execute_newtable(instruction *) {}
// void execute_tablegetelem(instruction *) {}
// void execute_tablesetelem(instruction *) {}

avm_table *avm_tablenew(void) {
  auto temp = new avm_table();
  return temp;
}

avm_memcell *avm_tablegetelem(avm_table *t, avm_memcell *key) {
  switch (key->type) {
  case number_m: {

    auto temp = t->int_hashtable.find(key->data.numVal);
    if (temp != t->int_hashtable.end())
      return temp->second;
  }
  case string_m: {

    auto temp = t->string_hashtable.find(key->data.strVal);
    if (temp != t->string_hashtable.end())
      return temp->second;
  }
  default:

    // printf("No item with index %s found in table!", key->data.strVal);
    return NULL;
    break;
  }
}
void execute_newtable(instruction *instr) {
#ifdef VERBOSE
  printf("execute_newtable\n");
#endif //
  avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
  assert(lv && (&mem_stack[AVM_STACKSIZE - 1]) >= lv &&
             lv > &(mem_stack[top]) ||
         lv == &retval);

  avm_memcellclear(lv);

  lv->type = table_m;
  lv->data.tableVal = avm_tablenew();
  avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction *instr) {
#ifdef VERBOSE
  printf("execute_tablegetelem\n");
#endif //
  avm_memcell *lv = avm_translate_operand(instr->result, (avm_memcell *)0);
  avm_memcell *t = avm_translate_operand(instr->arg1, (avm_memcell *)0);
  avm_memcell *i = avm_translate_operand(instr->arg2, &ax);

  assert(lv && (&mem_stack[AVM_STACKSIZE - 1]) >= lv && lv > &mem_stack[top] ||
         lv == &retval);
  assert(t && (&mem_stack[AVM_STACKSIZE - 1]) >= t && t > &mem_stack[top]);
  assert(i);

  avm_memcellclear(lv);

  lv->type = nil_m;

  if (t->type != table_m) {
    avm_error("Illegal use of table");
    printf("%s is not a table!\n", avm_memcell_t_string[t->type]);
  } else {
    avm_memcell *content = avm_tablegetelem(t->data.tableVal, i);
    if (content) {
      avm_assign(lv, content);
    } else {
      std::string out =
          avm_tostring(t) + "[" + avm_tostring(i) + "]" + "not found!";
      avm_warning(" Cannot be found!");
    }
  }
}

void avm_tablesetelem(avm_table *t, avm_memcell *key, avm_memcell *value) {
  auto temp = new avm_memcell();
  temp->type = value->type;
  temp->data = value->data;
  switch (key->type) {
  case string_m:
    t->string_hashtable.insert({std::string(key->data.strVal), temp});
    t->total++;
    break;
  case number_m:
    t->int_hashtable.insert({key->data.numVal, temp});
    t->total++;
    break;
  default:

    break;
  }
}
void execute_tablesetelem(instruction *instr) {
#ifdef VERBOSE
  printf("execute_tablesetelem\n");
#endif //
  avm_memcell *t = avm_translate_operand(instr->result, (avm_memcell *)0);

  avm_memcell *i = avm_translate_operand(instr->arg1, &ax);
  avm_memcell *c = avm_translate_operand(instr->arg2, &bx);

  assert(t && &mem_stack[AVM_STACKSIZE - 1] >= t && t > &mem_stack[top]);
  assert(i && c);

  if (t->type != table_m) {
    printf("Error! illegal use of type %s as table, line %d, tcode %d !",
           avm_memcell_t_string[t->type], instr->srcLine, instr->taddress);
    executionStop = 1;

  } else {
    avm_tablesetelem(t->data.tableVal, i, c);
  }
}
void execute_nop(instruction *) {}
void execute_jmp(instruction *instr) { pc = instr->result->val - 1; }
void execute_NULL(instruction *) {}

execute_func_t executeFuncs[] = {
    execute_assign,       execute_add,  execute_sub,
    execute_mul,          execute_div,  execute_mod,
    execute_uminus,       execute_jeq,  execute_jne,
    execute_jle,          execute_jge,  execute_jlt,
    execute_jgt,          execute_call, execute_funcenter,
    execute_funcexit,     execute_jmp,  execute_tablegetelem,
    execute_tablesetelem, execute_nop,  execute_pusharg,
    execute_newtable,     execute_NULL,
};

bool execute_cycle(void) {
  // std::cout<<pc<<std::endl;
  // std::cout<<
  if (executionStop) {
    std::cout << "lathos" << std::endl;
    return true;
  } else if (pc == AVM_ENDING_PC) {
    std::cout << "telos kodika" << std::endl;
    executionStop = 1;
    return true;
  } else if (pc == AVM_ENDING_PC + 1) {
    std::cout << "ekana jump meta to telos tou kodika" << std::endl;
    return true;
  } else {
    instruction *instr = instructions[pc];

    assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
    unsigned oldPC = pc;
    executeFuncs[instr->opcode](instr);
    if (pc == oldPC) {
      pc++;
    }
  }
  return false;
}

library_func_t avm_getlibraryfunc(const char *id) {
  auto fun = avm_libFuncs.find(id);
  if (fun != avm_libFuncs.end())
    return fun->second;
  return NULL;
}
unsigned avm_totalactuals() {
  return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}
avm_memcell *avm_getactual(unsigned i) {
  assert(i < avm_totalactuals());
  return &mem_stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

// typedef const char *(*tostring_func_t)(avm_memcell *m);
using tostring_func_t = std::string (*)(avm_memcell *m);

std::string number_tostring(avm_memcell *m) {
  std::string out = std::to_string(m->data.numVal);
  return out;
  // return out.c_str();
}

std::string string_tostring(avm_memcell *m) {
  return std::string(m->data.strVal);
}

std::string bool_tostring(avm_memcell *m) {
  if (m->data.boolVal == 1) {
    return "true";
  } else {
    return "false";
  }
}

std::string userfunc_tostring(avm_memcell *m) {
  std::string s = "User Function : " +
                  std::to_string(userfunctionConst[m->data.funcVal].address);
  return s;
}

std::string libfunc_tostring(avm_memcell *m) {
  std::string s = "Library Function : " + std::string(m->data.libfuncVal);
  return s;
}

std::string table_tostring(avm_memcell *m);
std::string nil_tostring(avm_memcell *m) { return "nil"; }

tostring_func_t tostringFuncs[] = {
    number_tostring,   string_tostring,  bool_tostring, table_tostring,
    userfunc_tostring, libfunc_tostring, nil_tostring,  0};

std::string table_tostring(avm_memcell *m) {
  std::string out;
  out.append("[ ");
  for (auto item : m->data.tableVal->string_hashtable) {
    if(item.second != NULL){
      out.append("{ \"");
      out.append(item.first);
      out.append("\" : ");
      out.append(tostringFuncs[item.second->type](item.second));
      out.append(" } , ");
    }
    else{
      out.append(item.first + " , ");
    }
  }
  for (auto item : m->data.tableVal->int_hashtable) {
    if(item.second != NULL){
      out.append("{ ");
      out.append(std::to_string(item.first));
      out.append(" : ");
      out.append(tostringFuncs[item.second->type](item.second));
      out.append("} , ");
    }
    else{
      out.append(std::to_string(item.first) + " , ");
    }
  }
  out.pop_back();
  out.pop_back();
  out.pop_back();
  out += " ]";
  return out;
}

std::string avm_tostring(avm_memcell *m) {
  assert(m->type >= number_m && m->type <= undef_m);
  return (*tostringFuncs[m->type])(m);
}

void libfunc_print() {
  unsigned n = avm_totalactuals();
  for (unsigned i = 0; i < n; ++i) {
    std::string s = avm_tostring(avm_getactual(i));
    puts(s.c_str());
  }
}
void avm_calllibfunc(const char *id) {
  library_func_t f = avm_getlibraryfunc(id);
  if (!f) {
    avm_error("unsupported lib func");
    printf("'%s' called!", id);
  } 
  else {

    if( std::strcmp(id , "totalarguments") == 0 || std::strcmp(id , "argument") == 0){
      curr_func_top = topsp;
    }

    in_function++;
    topsp = top;
    totalActuals = 0;

    (*f)();
    if (!executionStop) {
      execute_funcexit((instruction *)0);
    }
  }
}
void execute_call(instruction *instr) {
  avm_memcell *func = avm_translate_operand(instr->result, &ax);
  assert(func);
  avm_callsaveenvironment();
  // std::cout << "restore pc = " << restore_pc << "\n";

  switch (func->type) {
  case userfunc_m: {
    pc = userfunctionConst[func->data.funcVal].address - 1;
    // std::cout << "pc = " << pc << "\n";
    assert(pc < AVM_ENDING_PC);
    assert(instructions[pc]->opcode == funcenter_v);
    break;
  }
  case string_m:
    avm_calllibfunc(func->data.strVal);
    break;
  case libfunc_m:
    avm_calllibfunc(func->data.libfuncVal);
    break;
  default: {
    std::string s = "call: cannot bind " + avm_tostring(func) + " to function!";
    avm_error(s.c_str());
    executionStop = 1;
  }
  }
}

void libfunc_typeof() {
  unsigned n = avm_totalactuals();

  if (n > 1) {
    retval.type = nil_m;
    printf("ERROR, too many arguments for library function typeof. (needs 1 "
           "argument)\n");
  } else {
    const char *s = avm_memcell_t_string[avm_getactual(0)->type];
    retval.type = string_m;
    retval.data.strVal = s;
  }
}

void libfunc_sqrt() {
  double i = avm_getactual(0)->data.numVal;
  if (i < 0) {
    retval.type = nil_m;
  } else {
    retval.type = number_m;
    retval.data.numVal = sqrt(i);
  }
}

void libfunc_sin() {
  double i = avm_getactual(0)->data.numVal;
  double rads = PI * i / 180;
  retval.type = number_m;
  retval.data.numVal = sin(rads);
}

void libfunc_cos() {
  double i = avm_getactual(0)->data.numVal;

  double rads = PI * i / 180;

  retval.type = number_m;
  retval.data.numVal = cos(rads);
}

void libfunc_strtonum() {
  std::string i = avm_getactual(0)->data.strVal;

  if (avm_getactual(0)->type != string_m) {
    retval.type = nil_m;
  } else {
    retval.data.numVal = std::stod(i);
    retval.type = number_m;
  }
}

void libfunc_input(){
  char* input = (char*)malloc(1024);
  scanf("%s" , input);

  int noDigits = 0;
  int noAlpha = 0;
  int noDot = 0;

  for(int i=0; i<strlen(input); i++){
    if ( std::isdigit(input[i])){
      noDigits++;
    }
    else if(input[i] == '.'){
      noDot++;
    }
    else if( std::isalpha(input[i])){
      noAlpha++;
    }
  }

  if (noAlpha == 0 && noDot == 0 && noDigits == strlen(input)){  //AKEREOS ARITHMOS
    retval.type = number_m;
    retval.data.numVal = atoi(input);
  }
  else if (noAlpha == 0 && noDot == 1 && noDigits == strlen(input)-1){   //DEKADIKOS ARITHMOS
    retval.type = number_m;
    retval.data.numVal = atof(input);
  }
  else if( std::strcmp(input, "true") == 0 ){
    retval.type = bool_m;
    retval.data.boolVal = 1;
  }
  else if( std::strcmp(input , "false") == 0){
    retval.type = bool_m;
    retval.data.boolVal = 0;
  }
  else if(std::strcmp(input , "nill") == 0){
    retval.type = nil_m;
  }
  else{
    retval.type = string_m;
    retval.data.strVal = input;
  }
}

void libfunc_objectmemeberkeys(){
  avm_table *input = avm_getactual(0)->data.tableVal;
  avm_table *temp = new avm_table();

  if(input->int_hashtable.size() != 0){
    for (auto pair : input->int_hashtable ){
        temp->int_hashtable.insert( {pair.first , NULL} );
    }
  }
  if(input->string_hashtable.size() != 0){
    for (auto pair : input->string_hashtable){
      temp->string_hashtable.insert( {pair.first , NULL} );
    }
  }

  retval.type = table_m;
  retval.data.tableVal = temp;

}

void libfunc_objecttotalmembers(){
  avm_table *t = avm_getactual(0)->data.tableVal;
  retval.data.numVal = t->total;
}

void libfunc_objectcopy(){
  avm_table *t = avm_getactual(0)->data.tableVal;
  avm_table *temp = new avm_table();

  for (auto index : t->int_hashtable){
    temp->int_hashtable.insert( {index.first , index.second} );
  }

  for (auto index : t->string_hashtable){
    temp->string_hashtable.insert( {index.first , index.second});
  }

  retval.type = table_m;
  retval.data.tableVal = temp;
}

void libfunc_totalarguments(){
  if(in_function == 0){
    retval.type = nil_m;
  }
  else{
    retval.type = number_m;
    retval.data.numVal = avm_get_envvalue(curr_func_top + AVM_NUMACTUALS_OFFSET);
  }
}

void libfunc_argument(){
  if(in_function == 0){
    retval.type = nil_m;
  }
  else{
    int noArg = avm_getactual(0)->data.numVal;
    // std::cout<<noArg<<"\n";

    avm_memcell* arg = &mem_stack[curr_func_top + AVM_STACKENV_SIZE  + 1 + noArg];
    // printf("%i\n" , arg->type);
    // std::string temp = avm_tostring(arg);
    // retval.type = string_m;
    // retval.data.strVal = temp.c_str();
    retval.type = arg->type;
    retval.data = arg->data;
  }
}

void amv_initstack() {
  // for (auto &memcel : mem_stack) {
  //   memcel.type = undef_m;
  // }

  for(int i=0; i<programVarOffset; i++){
    // mem_stack[top].data.numVal = i;
    top--;
    topsp--;
  }

  for(int i=top-1; i>=0; i--){
    mem_stack[i].type = undef_m;
  }

  avm_register_libFunc("print", libfunc_print);
  avm_register_libFunc("typeof", libfunc_typeof);
  avm_register_libFunc("strtonum", libfunc_strtonum);
  avm_register_libFunc("sqrt", libfunc_sqrt);
  avm_register_libFunc("cos", libfunc_cos);
  avm_register_libFunc("sin", libfunc_sin);
  avm_register_libFunc("input", libfunc_input);
  avm_register_libFunc("objectmemberkeys" , libfunc_objectmemeberkeys);
  avm_register_libFunc("objecttotalmembers", libfunc_objecttotalmembers);
  avm_register_libFunc("objectcopy", libfunc_objectcopy);
  avm_register_libFunc("totalarguments", libfunc_totalarguments);
  avm_register_libFunc("argument", libfunc_argument);

  
}
