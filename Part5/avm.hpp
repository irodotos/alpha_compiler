#include "t_data.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>

enum avm_memcell_t {
  number_m = 0,
  string_m = 1,
  bool_m = 2,
  table_m = 3,
  userfunc_m = 4,
  libfunc_m = 5,
  nil_m = 6,
  undef_m = 7
};

void avm_warning(char *format);
void avm_error(char *format);
struct avm_table;

struct avm_memcell {
  avm_memcell_t type;
  union {
    double numVal;
    const char *strVal;
    unsigned char boolVal;
    struct avm_table *tableVal;
    unsigned funcVal;
    const char *libfuncVal;
  } data;
};

struct avm_table {
  unsigned refCounter;
  std::unordered_map<int, avm_memcell *> int_hashtable;
  std::unordered_map<std::string, avm_memcell *> string_hashtable;
  unsigned total;
  ~avm_table() {
    for (auto d : this->int_hashtable) {
      delete d.second;
    }
	this->int_hashtable.clear();
    for (auto d : this->string_hashtable) {
      delete d.second;
    }
	this->int_hashtable.clear();
  }
};
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);
void binary_parser();
void print_tables();
void printStrings();
void printNum();
void printUserFunc();
void printlibFunc();
void amv_initstack();
void avm_error(const char *format);
void print_mem_globals();
userfunc input_to_userfunc(std::string func);
bool execute_cycle(void);
