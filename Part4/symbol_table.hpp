#ifndef SYM_H
#define SYM_H
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

enum SymbolType { var_GLOBAL, var_LOCAL, var_FORMAL, func_USER, func_LIB };
enum ScopeType { BLOCK, FLOW, FUNC };
enum scopespace_t { programvar, functionlocal, formalarg };
extern const char *str_SymbolType[5];

struct SymbolTableEntry {
  bool isActive;
  unsigned int scope = 0;
  unsigned int line = 0;
  std::string name;
  enum SymbolType type;
  int offset;
  enum scopespace_t space;
  unsigned int taddress;        // EXTRA GIA FUNCTION
  unsigned int totalLocals = 0; // EXTRA GIA FUNCTION

  SymbolType get_type() { return type; }
  std::string &get_name() { return this->name; }
  unsigned int &get_line() { return this->line; }
  unsigned int &get_scope() { return this->scope; }
  bool &get_isActive() { return this->isActive; }
  void set_isActive(bool flag) { this->isActive = flag; }
  void print() {
    printf("\"%s\"\t%s\t(scope %d)\t(line %d) isActive: %d   offset: %d  "
           "space:%d\n",
           name.c_str(), str_SymbolType[type], scope, line, isActive, offset,
           space);
  }
};

SymbolTableEntry *lookUp(std::string symbol, int curr_scope);
SymbolTableEntry *lookUpScope(std::string symbol, int scope);
SymbolTableEntry *lookUpLIB(std::string symbol);
void hide(unsigned int scope);
void insert(std::string _name, unsigned int _scope, unsigned int _line,
            SymbolType _type, bool _isActive, unsigned int _offset,
            scopespace_t _space);
void init_Libfunc();
int get_min_legal_scope();

std::string get_anon_func_name();
void zero_anon_func_counter();

std::string get_tmp_name();
SymbolTableEntry *new_temp();
void zero_tmp_counter();
void print_symtable();

void push_Scope(ScopeType type);
void pop_Scope();
bool is_in_loop();
#endif // !SYM_H
