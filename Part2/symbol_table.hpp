#ifndef SYM_H
#define SYM_H
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>

enum SymbolType { var_GLOBAL, var_LOCAL, var_FORMAL, func_USER, func_LIB };
enum ScopeType { BLOCK,  FUNC };
struct Variable {
  std::string name;
  unsigned int scope;
  unsigned int line;
  Variable(std::string name, unsigned int scope, unsigned int line) {
    this->name = name;
    this->scope = scope;
    this->line = line;
  }
  Variable() {}
};
struct Function {
  std::string name;
  unsigned int scope;
  unsigned int line;
  Function(std::string name, unsigned int scope, unsigned int line) {
    this->name = name;
    this->scope = scope;
    this->line = line;
  }
  Function() {}
  // std::vector<Variable> arguments;
};
struct SymbolTableEntry {
  bool isActive;

  const char *str_SymbolType[5] = {"[global var]", "[local var]",
                                   "[formal var]", "[user func]", "[lib func]"};
  Variable varVal;
  Function funcVal;
  enum SymbolType type;

  SymbolTableEntry(Variable _value, SymbolType _type, bool _isActive) {
    this->varVal = _value;
    this->type = _type;
    this->isActive = _isActive;
  }
  SymbolTableEntry(Function _value, SymbolType _type, bool _isActive) {
    this->funcVal = _value;
    this->type = _type;
    this->isActive = _isActive;
  }
  SymbolType get_type() { return type; }
  std::string &get_name() {
    if (type == var_GLOBAL || type == var_LOCAL || type == var_FORMAL) {
      return varVal.name;
    } else {
      return funcVal.name;
    }
  }
  unsigned int &get_line() {
    if (type == var_GLOBAL || type == var_LOCAL || type == var_FORMAL) {
      return varVal.line;
    } else {
      return funcVal.line;
    }
  }
  unsigned int &get_scope() {
    if (type == var_GLOBAL || type == var_LOCAL || type == var_FORMAL) {
      return varVal.scope;
    } else {
      return funcVal.scope;
    }
  }
  bool &get_isActive() { return this->isActive; }
  void set_isActive(bool flag) { this->isActive = flag; }
  void print() {
    if (type == var_GLOBAL || type == var_LOCAL || type == var_FORMAL) {
      printf("\"%s\"\t%s\t(scope %d)\t(line %d) isActive: %d\n",
             varVal.name.c_str(), str_SymbolType[type], varVal.scope,
             varVal.line, isActive);
    } else {
      printf("\"%s\"\t%s\t(scope %d)\t(line %d) isActive: %d\n",
             funcVal.name.c_str(), str_SymbolType[type], funcVal.scope,
             funcVal.line, isActive);
    }
  }
};

SymbolTableEntry *lookUp(std::string symbol, int curr_scope);
SymbolTableEntry *lookUpScope(std::string symbol, int scope);
SymbolTableEntry *lookUpLIB(std::string symbol);
void hide(unsigned int scope);
void insert(SymbolTableEntry symbol);
void init_Libfunc();
std::string get_tmp_name(std::string prefix);
void zero_tmp_counter();
int get_min_legal_scope();

#endif // !SYM_H
