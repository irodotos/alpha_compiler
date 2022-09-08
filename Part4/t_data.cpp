#include "t_data.hpp"
#include <vector>
unsigned currInst = 1;
std::vector<std::string> stringConst;
std::vector<double> numberConst;
std::vector<userfunc> userfunctionConst;
std::vector<std::string> libConst;
std::vector<instruction *> instructions;

unsigned insert_stringConst(std::string s1) {

  for (int i = 0; i < stringConst.size(); i++) {
    if (stringConst[i] == s1)
      return i;
  }
  stringConst.push_back(s1);
  return stringConst.size() - 1;
}

unsigned insert_numberConst(double num) {
  for (int i = 0; i < numberConst.size(); i++) {
    if (numberConst[i] == num)
      return i;
  }
  numberConst.push_back(num);
  return numberConst.size() - 1;
}
unsigned insert_userfunctionConst(SymbolTableEntry *sym) {
  for (int i = 0; i < userfunctionConst.size(); i++) {
    if (userfunctionConst[i].address == sym->taddress)
      return i;
  }
  userfunctionConst.push_back(
      userfunc{sym->taddress, sym->totalLocals, sym->name});
  return userfunctionConst.size() - 1;
}

unsigned insert_libConst(std::string s1) {
  for (int i = 0; i < libConst.size(); i++) {
    if (libConst[i] == s1)
      return i;
  }
  libConst.push_back(s1);
  return libConst.size() - 1;
}
const char *vmarg_t_string[] = {

    "label_a", "global_a", "formal_a",   "local_a",   "number_a", "string_a",
    "bool_a",  "nil_a",    "userfunc_a", "libfunc_a", "retval_a", "NULL_a",

};
const char *vmopcode_t_string[] = {
    "assign_v",     "add_v",          "sub_v",          "mul_v",
    "div_v",        "mod_v",          "uminus_v",       "if_eq_v",
    "if_not_eq_v",  "if_lesseq_v",    "if_greatereq_v", "if_less_v",
    "if_greater_v", "call_v",         "funcenter_v",    "funcexit_v",
    "jump_v",       "tablegetelem_v", "tablesetelem_v", "nop_v",
    "pusharg_v",    "newtable_v",     "NULL_v",
};
void print_tables() {

  printStrings();
  printNum();
  printUserFunc();
  printlibFunc();
}
void printStrings() {
  int cntr = 0;
  printf("STRINGS\n");
  for (auto a : stringConst) {
    printf("%d: \"%s\"\n", cntr++, a.c_str());
  }
  printf("=======================\n");
}

void printNum() {
  int cntr = 0;
  printf("NUMBERS\n");
  for (auto a : numberConst) {
    printf("%d: \"%f\"\n", cntr++, a);
  }
  printf("=======================\n");
}

void printUserFunc() {
  int cntr = 0;
  printf("FUNCS\n");
  for (auto a : userfunctionConst) {
    printf("%d:   %d  %d   %s \n", cntr++, a.address, a.localsize,
           a.id.c_str());
  }
  printf("=======================\n");
}

void printlibFunc() {
  int cntr = 0;
  printf("LIBFUNCS\n");
  for (auto a : libConst) {
    printf("%d:    %s\n", cntr++, a.c_str());
  }
  printf("=======================\n");
}

instruction *new_instruction(vmopcode op) {
  instruction *temp = new instruction();
  temp->result = new vmarg();
  temp->arg1 = new vmarg();
  temp->arg2 = new vmarg();
  temp->opcode = op;
  return temp;
}

unsigned nextinstructionlabel() { return currInst; }

// using value_of_arg_t = std::string (*)(vmarg *);
// std::string label_to_str(vmarg *arg) {
//   return std::string("label_a : ") + std::to_string(arg->val);
// }
// std::string global_to_str(vmarg *arg) {
//
//   return std::string("global_a : ") + std::to_string(arg->val) + "("+ mem_stack[arg->val].type +")";
// }
// std::string formal_to_str(vmarg *arg) {}
// std::string local_to_str(vmarg *arg) {}
// std::string number_to_str(vmarg *arg) {}
// std::string string_to_str(vmarg *arg) {}
// std::string bool_to_str(vmarg *arg) {}
// std::string nil_to_str(vmarg *arg) {}
// std::string userfunc_to_str(vmarg *arg) {}
// std::string libfunc_to_str(vmarg *arg) {}
// std::string retval_to_str(vmarg *arg) {}
// std::string NULL_to_str(vmarg *arg) {}
// value_of_arg_t arg_to_str[] = {
//
// };
void emit_instraction(instruction *inst) {
  inst->taddress = currInst++;
  instructions.push_back(inst);
}
void printInstructions() {
  printf("\ninst#  │  %-15s  │  %-18s  │  %-18s  │  %-14s  │  %-5s\n"
         "───────┼───────────────────┼──────────────────────┼──────────────────"
         "────┼──────────────────┼─────────────────\n",
         "opcode", "result", "arg1", "arg2", "line");

  for (auto inst : instructions) {
    std::string arg1 = inst->arg1->type == NULL_a
                           ? ""
                           : std::string(vmarg_t_string[inst->arg1->type]) +
                                 " : " + std::to_string(inst->arg1->val);
    std::string arg2 = inst->arg2->type == NULL_a
                           ? ""
                           : std::string(vmarg_t_string[inst->arg2->type]) +
                                 " : " + std::to_string(inst->arg2->val);
    std::string result = inst->result->type == NULL_a
                             ? ""
                             : std::string(vmarg_t_string[inst->result->type]) +
                                   " : " + std::to_string(inst->result->val);

    printf("#%-5d │  %-15s  │  %-18s  │  %-18s  │  %-13s   │  %d\n",
           inst->taddress, vmopcode_t_string[inst->opcode], result.c_str(),
           arg1.c_str(), arg2.c_str(), inst->srcLine);
  }
}
