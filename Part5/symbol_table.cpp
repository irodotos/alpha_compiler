#include "symbol_table.hpp"
#include "quad.hpp"

unsigned int anon_counter = 0;
unsigned int tmp_counter = 0;
unsigned int offset = 0;
extern int yylineno;

const char *str_SymbolType[5] = {"[global var]", "[local var]", "[formal var]",
                                 "[user func]", "[lib func]"};
std::map<std::string, std::vector<SymbolTableEntry *>> symbol_table;
std::map<unsigned int, std::vector<SymbolTableEntry *>> scope_lists;

std::vector<ScopeType> Scope;

void push_Scope(ScopeType type) { Scope.push_back(type); }
void pop_Scope() { Scope.pop_back(); };
int get_min_legal_scope() {
  for (int i = Scope.size() - 1; i >= 0; i--) {
    if (Scope[i] == FUNC) {
      return i + 1;
    }
  }
  return 0;
}
SymbolTableEntry *lookUp(std::string symbol, int curr_scope) {
  auto symbol_iter = symbol_table.find(symbol);
  if (symbol_iter != symbol_table.end()) {
    for (int i = symbol_iter->second.size() - 1; i >= 0; i--) {
      if (symbol_iter->second.at(i)->get_isActive() == true &&
          symbol_iter->second.at(i)->get_scope() != curr_scope &&
          symbol_iter->second.at(i)->get_scope() != 0) {
        return symbol_iter->second.at(i);
      }
    }
  }
  return NULL;
}
SymbolTableEntry *lookUpLIB(std::string symbol) {
  for (auto &lib_func : scope_lists.at(0)) {
    if (lib_func->get_type() == func_LIB && symbol == lib_func->get_name()) {
      return lib_func;
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
    if (var_atScope->get_name() == symbol &&
        var_atScope->get_isActive() == true) {
      return scope_lists.at(scope).at(i);
    }
  }
  return NULL;
}

void hide(unsigned int scope) {
  for (auto &symEntr : symbol_table) {
    for (auto &sym_listEntr : symEntr.second) {
      if (sym_listEntr->get_scope() == scope) {
        auto active = sym_listEntr->get_isActive();
        if (active) {
          sym_listEntr->set_isActive(false);
        }
      }
    }
  }
  for (auto &var_scope : scope_lists) {
    if (var_scope.first != scope)
      continue;
    for (auto &vars : var_scope.second) {
      vars->get_isActive() = false;
    }
  }
}
void insert(std::string _name, unsigned int _scope, unsigned int _line,
            SymbolType _type, bool _isActive, unsigned int _offset,
            scopespace_t _space) {
  SymbolTableEntry *temp = new SymbolTableEntry();
  temp->scope = _scope;
  temp->line = _line;
  temp->name = _name;
  temp->type = _type;
  temp->isActive = _isActive;
  temp->offset = _offset;
  temp->space = _space;

  auto sym_table_iter = symbol_table.find(temp->get_name());
  auto scope_lists_iter = scope_lists.find(temp->get_scope());
  if (scope_lists_iter == scope_lists.end()) {
    std::vector<SymbolTableEntry *> temp_vec;
    temp_vec.push_back(temp);
    scope_lists.insert({temp->get_scope(), temp_vec});
  } else {
    scope_lists.at(temp->get_scope()).push_back(temp);
  }
  if (sym_table_iter == symbol_table.end()) {
    std::vector<SymbolTableEntry *> temp_vec;
    temp_vec.push_back(temp);
    symbol_table.insert({temp->get_name(), temp_vec});
  } else {

    sym_table_iter->second.push_back(temp);
  }
}
void init_Libfunc() {
  insert("print", 0, 0, func_LIB, true, 0, programvar);
  insert("input", 0, 0, func_LIB, true, 0, programvar);
  insert("objectmemberkeys", 0, 0, func_LIB, true, 0, programvar);
  insert("objecttotalmembers", 0, 0, func_LIB, true, 0, programvar);
  insert("objectcopy", 0, 0, func_LIB, true, 0, programvar);
  insert("totalarguments", 0, 0, func_LIB, true, 0, programvar);
  insert("argument", 0, 0, func_LIB, true, 0, programvar);
  insert("typeof", 0, 0, func_LIB, true, 0, programvar);
  insert("strtonum", 0, 0, func_LIB, true, 0, programvar);
  insert("sqrt", 0, 0, func_LIB, true, 0, programvar);
  insert("cos", 0, 0, func_LIB, true, 0, programvar);
  insert("sin", 0, 0, func_LIB, true, 0, programvar);
}

std::string get_anon_func_name() {

  return "_f" + std::to_string(anon_counter++);
}
void zero_anon_func_counter() { anon_counter = 0; }

std::string get_tmp_name() { return "_t" + std::to_string(tmp_counter++); }
void zero_tmp_counter() { tmp_counter = 0; }

SymbolTableEntry *new_temp() {
  std::string name = get_tmp_name();
  SymbolTableEntry *temp;
  inccurrscopeoffset();
  if ((temp = lookUpScope(name, Scope.size())) == NULL) {
    insert(name, Scope.size(), yylineno, var_LOCAL, true, currscopeoffset()-1, currscopespace());
    return lookUpScope(name, Scope.size());
  } else
    return temp;
}
bool is_in_loop() { return Scope.back() == FLOW ? true : false; }
void print_symtable() {

  for (auto list_of_scopes : scope_lists) {
    printf("\n-------------------------- SCOPE %d -----------------------\n\n",
           list_of_scopes.first);
    for (auto a : list_of_scopes.second) {
      a->print();
    }
  }
}
