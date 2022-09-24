#include "symbol_table.hpp"
#include <string>
#include <sstream>

enum vmarg_t {
  label_a = 0,
  global_a = 1,
  formal_a = 2,
  local_a = 3,
  number_a = 4,
  string_a = 5,
  bool_a = 6,
  nil_a = 7,
  userfunc_a = 8,
  libfunc_a = 9,
  retval_a = 10,
  NULL_a = 11
};

struct vmarg {
  vmarg_t type;
  unsigned int val;
  vmarg() {
    this->val = 0;
    this->type = NULL_a;
  }
};

enum vmopcode {
  assign_v,
  add_v,
  sub_v,
  mul_v,
  div_v,
  mod_v,
  uminus_v,
  if_eq_v,
  if_not_eq_v,
  if_lesseq_v,
  if_greatereq_v,
  if_less_v,
  if_greater_v,
  call_v,
  funcenter_v,
  funcexit_v,
  jump_v,
  tablegetelem_v,
  tablesetelem_v,
  nop_v,
  pusharg_v,
  newtable_v,
  NULL_v
};

struct instruction {
  vmopcode opcode;
  vmarg *result;
  vmarg *arg1;
  vmarg *arg2;
  unsigned srcLine; // we may use unsigned int
  unsigned taddress;
};

struct userfunc {
  unsigned address;
  unsigned localsize;
  std::string id;
  userfunc(unsigned address, unsigned localsize, std::string id) {
    this->address = address;
    this->localsize = localsize;
    this->id = id;
  }
};

struct incomplete_jump {
  unsigned instNo;
  unsigned iaddress;
};

unsigned insert_stringConst(std::string s1);

unsigned insert_numberConst(double num);

unsigned insert_userfunctionConst(SymbolTableEntry *sym);

unsigned insert_libConst(std::string s1);

instruction *new_instruction(vmopcode op);

void emit_instraction(instruction *inst);
unsigned nextinstructionlabel();

// struct avm_table {
//   unsigned refCounter;
//   std::unordered_map<avm_memcell, avm_memcell> stringIndex;
//   std::unordered_map<avm_memcell, avm_memcell> numIndex;
//   unsigned total;
// };

// void init_stack();
void printStrings();
void printNum();
void printUserFunc();
void printlibFunc();
void print_tables();
void printInstructions();
