#include "t_code.hpp"
#include "quad.hpp"
#include "symbol_table.hpp"
#include "t_data.hpp"
#include <fstream>

extern std::vector<quad *> quads;

extern const char *vmarg_t_string[];
extern const char *vmopcode_t_string[];
extern std::vector<std::string> stringConst;
extern std::vector<double> numberConst;
extern std::vector<userfunc> userfunctionConst;
extern std::vector<std::string> libConst;

extern unsigned programVarOffset;
// std::array<avm_memcell, 4096> mem_stack;
extern std::vector<instruction *> instructions;
std::vector<incomplete_jump> inc_jumps;
std::stack<std::vector<unsigned int>> t_functionretstack;
std::stack<unsigned int> functionIndex;

void make_operand(expr *e, vmarg *arg) {
  if (e == NULL) {
    arg->val = 0;
    return;
  }
  // All those below use a variable for storage
  switch (e->type) {
    case var_e: {
        assert(e->sym);
        arg->val = e->sym->offset;
        if(e->sym->type == func_USER){
            arg->type = userfunc_a;
        }else if(e->sym->type == func_LIB){
            arg->type = libfunc_a;
        }else{
            switch (e->sym->space) {
                case programvar:
                    arg->type = global_a;
                    break;
                case functionlocal:
                    arg->type = local_a;
                    break;
                case formalarg:
                    arg->type = formal_a;
                    break;
                default:
                    assert(0);
            }
        }
        break;
    }
    case tableitem_e: {
        switch (e->sym->space) {
                case programvar:
                    arg->type = global_a;
                    break;
                case functionlocal:
                    arg->type = local_a;
                    break;
                case formalarg:
                    arg->type = formal_a;
                    break;
                default:
                    assert(0);
            }
        break;
    }
    case arithexpr_e: {
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space) {
            case programvar:
                arg->type = global_a;
                break;
            case functionlocal:
                arg->type = local_a;
                break;
            case formalarg:
                arg->type = formal_a;
                break;
            default:
                assert(0);
        }
        break;
    }
    case boolexpr_e:
    case assignexpr_e: { /* auto edw eleipeeeeeeeeeeeeeeeee */
        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space) {
            case programvar:
                arg->type = global_a;
                break;
            case functionlocal:
                arg->type = local_a;
                break;
            case formalarg:
                arg->type = formal_a;
                break;
            default:
                assert(0);
        }
        break;
    }
    case newtable_e: {
      arg->val = e->sym->offset;
      switch (e->sym->space) {
        case programvar:
          arg->type = global_a;
          break;
        case functionlocal:
          arg->type = local_a;
          break;
        case formalarg:
          arg->type = formal_a;
          break;
        default:
          assert(0);
        }
      break;
    }
    // Constants
    case constbool_e: {
      arg->val = e->boolConst;
      arg->type = bool_a;
      break;
    }
    case conststring_e: {
      arg->val = insert_stringConst(e->strConst);
      arg->type = string_a;
      break;
    }
    case constnum_e: {
      arg->val = insert_numberConst(e->numConst);
      arg->type = number_a;
      break;
    }

    case nil_e: {
      arg->type = nil_a;
      break;
    }
    // functions
    case programfunc_e: {
      arg->type = userfunc_a;
      arg->val = insert_userfunctionConst(e->sym);
      break;
    }
    case libraryfunc_e: {
      arg->type = libfunc_a;
      arg->val = insert_libConst(e->sym->name);
      break;
    }
    default:
      assert(0);
  }
}

void make_retvaloperand(vmarg *arg) { arg->type = retval_a; }

void patchInstrLabel(unsigned from, unsigned to) {
  instructions[from]->result->val = to;
}
void patchInstrLabel(std::vector<unsigned int> from, unsigned to) {
  for (auto inst : from) {
    instructions[inst - 1]->result->val = to;
  }
}

void add_incomplete_jump(unsigned instNo, unsigned iaddress) {
  inc_jumps.push_back({instNo, iaddress});
}

void patch_incomplete_jumps() {
  // ALLAKSA TIN SINTHIKI GIATI JINI POU ITAN ITAN OTI NANE ALLA PALE EN
  // EDOULEPSE
  for (auto jump : inc_jumps) {
    if (jump.iaddress == quads.size()) {
      patchInstrLabel(jump.instNo, instructions.size() + 1);
    } else {
      patchInstrLabel(jump.instNo, quads[jump.iaddress]->taddress);
    }
    // patchInstrLabel(jump.instNo, nextinstructionlabel()); OTAN TO EVALA MONO
    // AFTO XORIS TA IF KATI DOULEPSE
  }
}

void generate(vmopcode op, quad *quad) {
  instruction *temp = new_instruction(op);
  temp->srcLine = quad->line;
  make_operand(quad->arg1, temp->arg1);
  make_operand(quad->arg2, temp->arg2);
  make_operand(quad->result, temp->result);
  quad->taddress = nextinstructionlabel();
  emit_instraction(temp);
}
void generate_relational(vmopcode op, quad *quad) {
  instruction *temp = new_instruction(op);
  temp->srcLine = quad->line;
  make_operand(quad->arg1, temp->arg1);
  make_operand(quad->arg2, temp->arg2);

  // if (!quad->result)
  temp->result->type = label_a;
  if (quad->label < quad->iaddress) {
    temp->result->val = quads[quad->label - 1]->taddress ;
  } else {
    add_incomplete_jump(nextinstructionlabel() - 1, quad->label - 1);
  }
  quad->taddress = nextinstructionlabel();
  emit_instraction(temp);
}

void generate_ADD(quad *quad) { generate(add_v, quad); }
void generate_SUB(quad *quad) { generate(sub_v, quad); }
void generate_MUL(quad *quad) { generate(mul_v, quad); }
void generate_DIV(quad *quad) { generate(div_v, quad); }
void generate_MOD(quad *quad) { generate(mod_v, quad); }
void generate_NEWTABLE(quad *quad) { generate(newtable_v, quad); }
void generate_TABLEGETELEM(quad *quad) { generate(tablegetelem_v, quad); }
void generate_TABLESETELEM(quad *quad) { generate(tablesetelem_v, quad); }
void generate_ASSIGN(quad *quad) {
  generate(assign_v, quad);
  // patch_incomplete_jumps(); // afto einai gia ta RELATIONAL JUMPS
}
void generate_NOP(quad *quad) {
  instruction *temp = new_instruction(nop_v);
  emit_instraction(temp);
}
void generate_UMINUS(quad *quad) { generate(uminus_v, quad); }
void generate_JUMP(quad *quad) {
  generate_relational(jump_v, quad);
  // patch_incomplete_jumps(); // afto einai gia ta RELATIONAL JUMPS
}
void generate_IF_EQ(quad *quad) { generate_relational(if_eq_v, quad); }
void generate_IF_NOTEQ(quad *quad) { generate_relational(if_not_eq_v, quad); }
void generate_IF_GREATER(quad *quad) {
  generate_relational(if_greater_v, quad);
}
void generate_IF_GREATEREQ(quad *quad) {
  generate_relational(if_greatereq_v, quad);
}
void generate_IF_LESS(quad *quad) { generate_relational(if_less_v, quad); }
void generate_IF_LESSEQ(quad *quad) { generate_relational(if_lesseq_v, quad); }
// void generate_NOT(quad *quad) {}
// void generate_OR(quad *quad) {}
// void generate_AND(quad *quad) {}
void generate_PARAM(quad *quad) {

  instruction *temp = new_instruction(pusharg_v);
  temp->srcLine = quad->line;
  quad->taddress = nextinstructionlabel();
  make_operand(quad->result, temp->result); //temp maybe arg1
  emit_instraction(temp);
}
void generate_CALL(quad *quad) {

  instruction *temp = new_instruction(call_v);
  temp->srcLine = quad->line;
  quad->taddress = nextinstructionlabel();
  make_operand(quad->result, temp->result);
  emit_instraction(temp);
}

void generate_GETRETVAL(quad *quad) {

  instruction *temp = new_instruction(assign_v);
  temp->srcLine = quad->line;
  quad->taddress = nextinstructionlabel();
  make_operand(quad->result, temp->result);
  make_retvaloperand(temp->arg1);
  emit_instraction(temp);
}
void generate_FUNCSTART(quad *quad) {

  SymbolTableEntry *func = quad->result->sym;
  func->taddress = nextinstructionlabel();
  quad->taddress = nextinstructionlabel();
  // functionIndex.push(insert_userfunctionConst(func));
  t_functionretstack.push(std::vector<unsigned int>());

  instruction *temp = new_instruction(funcenter_v);
  temp->srcLine = quad->line;
  make_operand(quad->result, temp->result);
  emit_instraction(temp);
}
void generate_RETURN(quad *quad) {
  instruction *temp = new_instruction(assign_v);
  temp->srcLine = quad->line;
  quad->taddress = nextinstructionlabel();
  make_operand(quad->result, temp->arg1);
  make_retvaloperand(temp->result);
  emit_instraction(temp);

  t_functionretstack.top().push_back(nextinstructionlabel());
}
void generate_FUNCEND(quad *quad) {
  patchInstrLabel(t_functionretstack.top(),
                  nextinstructionlabel() -
                      1); // afto einai gia ta jumbs meta apo to return
  t_functionretstack.pop();
  instruction *temp = new_instruction(funcexit_v);
  temp->srcLine = quad->line;
  quad->taddress = nextinstructionlabel();
  make_operand(quad->result, temp->result);
  emit_instraction(temp);
  // patch_incomplete_jumps(); // afto einai gia ta RELATIONAL JUMPS
  // functionIndex.pop();
}

typedef void (*generator_func_t)(quad *);

generator_func_t generators[] = {
    generate_ADD,          generate_SUB,          generate_MUL,
    generate_DIV,          generate_MOD,          generate_NEWTABLE,
    generate_TABLEGETELEM, generate_TABLESETELEM, generate_ASSIGN,
    generate_UMINUS,       generate_JUMP,         generate_IF_EQ,
    generate_IF_NOTEQ,     generate_IF_GREATER,   generate_IF_GREATEREQ,
    generate_IF_LESS,      generate_IF_LESSEQ,    generate_PARAM,
    generate_CALL,         generate_GETRETVAL,    generate_FUNCSTART,
    generate_RETURN,       generate_FUNCEND,      generate_NOP};

void generate_all(void) {
  for (auto quad : quads)
    generators[quad->op](quad);
  patch_incomplete_jumps(); // afto einai gia ta RELATIONAL JUMPS
  print_tables();
}
void write_arrays(std::ofstream &abcCode) {
  abcCode << stringConst.size() << '\n';
  for (auto str : stringConst) {
    abcCode << str << '\n';
  }
  abcCode << numberConst.size() << '\n';
  for (auto num : numberConst) {
    abcCode << num << '\n';
  }
  abcCode << userfunctionConst.size() << '\n';
  for (auto fun : userfunctionConst) {
    abcCode << fun.address << ' ' << fun.localsize << ' ' << fun.id << '\n';
  }
  abcCode << libConst.size() << '\n';
  for (auto fun : libConst) {
    abcCode << fun << '\n';
  }
}
void write_code(std::ofstream &abcCode) {
  for (auto instruction : instructions) {
    abcCode << instruction->opcode << ' ' << instruction->result->type << ' '
            << instruction->result->val << ' ' << instruction->arg1->type << ' '
            << instruction->arg1->val << ' ' << instruction->arg2->type << ' '
            << instruction->arg2->val << ' ' << instruction->srcLine << '\n';
  }
}
void create_bytecode_file() {
  std::ofstream MyFile("code.abc");
  MyFile << 69696969 << '\n';
  MyFile << programVarOffset << '\n';
  write_arrays(MyFile);
  write_code(MyFile);
  MyFile.close();
}
