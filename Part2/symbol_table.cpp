#include "symbol_table.hpp"
#include <string>

unsigned int tmp_counter = 0;

std::map<std::string, std::vector<SymbolTableEntry>> symbol_table;
std::map<unsigned int, std::vector<SymbolTableEntry>> scope_lists;

std::vector<ScopeType> Scope;
int get_min_legal_scope() {
  for (int i = Scope.size() - 1; i >= 0; i--) {
    if (Scope[i] == FUNC) {
      return i+1;
    }
  }
  return 0;
}
SymbolTableEntry *lookUp(std::string symbol, int curr_scope) {
  auto symbol_iter = symbol_table.find(symbol);
  if (symbol_iter != symbol_table.end()) {
    for (int i = symbol_iter->second.size() - 1; i >= 0; i--) {
      if (symbol_iter->second.at(i).get_isActive() == true &&
          symbol_iter->second.at(i).get_scope() != curr_scope &&
          symbol_iter->second.at(i).get_scope() != 0) {
        return &symbol_iter->second.at(
            i); /* an to vrw kai to active einai true */
      }
    }
  }
  return NULL;
}
SymbolTableEntry *lookUpLIB(std::string symbol) {
  for (auto &lib_func : scope_lists.at(0)) {
    if (lib_func.get_type() == func_LIB && symbol == lib_func.get_name()) {
      return &lib_func;
    }
  }
  return NULL;
}
SymbolTableEntry *lookUpScope(std::string symbol, int scope) {
  if (scope_lists.find(scope) == scope_lists.end()) {
    return NULL;
  }
  for (int i = scope_lists.at(scope).size() - 1; i >= 0; i--) {
    auto var_atScope = scope_lists.at(scope).at(i);
    if (var_atScope.get_name() == symbol &&
        var_atScope.get_isActive() == true) {
      return &scope_lists.at(scope).at(i);
    }
  }
  return NULL;
}

void hide(unsigned int scope) {
  for (auto &symEntr : symbol_table) {
    for (auto &sym_listEntr : symEntr.second) {
      if (sym_listEntr.get_scope() == scope) {
        auto active = sym_listEntr.get_isActive();
        if (active) {
          sym_listEntr.set_isActive(false);
        }
      }
    }
  }
  for (auto &var_scope : scope_lists) {
    if (var_scope.first != scope)
      continue;
    for (auto &vars : var_scope.second) {
      vars.get_isActive() = false;
    }
  }
}
void insert(SymbolTableEntry symbol) {
  using symbol_pair = std::pair<std::string, std::vector<SymbolTableEntry>>;
  using scope_pair = std::pair<unsigned int, std::vector<SymbolTableEntry>>;
  auto scope_lists_iter = scope_lists.find(symbol.get_scope());
  if (scope_lists_iter == scope_lists.end()) {
    std::vector<SymbolTableEntry> temp;
    temp.push_back(symbol);
    scope_lists.insert(scope_pair(symbol.get_scope(), temp));
  } else {
    scope_lists.at(symbol.get_scope()).push_back(symbol);
  }

  auto sym_table_iter = symbol_table.find(symbol.get_name());
  if (sym_table_iter == symbol_table.end()) {
    std::vector<SymbolTableEntry> temp;
    temp.push_back(symbol);
    symbol_table.insert(symbol_pair(symbol.get_name(), temp));
  } else {

    sym_table_iter->second.push_back(symbol);
  }
}
void init_Libfunc() {
  insert(SymbolTableEntry(Function("print", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("input", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("objectmemberkeys", 0, 0), func_LIB, true));
  insert(
      SymbolTableEntry(Function("objecttotalmembers", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("objectcopy", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("totalarguments", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("argument", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("typeof", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("strtonum", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("sqrt", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("cos", 0, 0), func_LIB, true));
  insert(SymbolTableEntry(Function("sin", 0, 0), func_LIB, true));
}

std::string get_tmp_name(std::string prefix) {

  ++tmp_counter;
  return prefix + std::to_string(tmp_counter);
}
void zero_tmp_counter() { tmp_counter = 0; }
