#include "avm.hpp"
#define VERBOSE

int main(int argc, char *argv[]) {
  binary_parser();
  printInstructions();
	  
  amv_initstack();
  while (!execute_cycle())
    ;
  return 0;
}
