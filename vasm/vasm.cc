#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "lexer.h"
#include "token.h"

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cout << "usage: ./vasm file" << std::endl;

    return EXIT_FAILURE;
  }

  std::ifstream file(argv[1]);

  if(!file.is_open()) {
    std::cerr << "error: could not open " << argv[1] << " for reading" << std::endl;

    return EXIT_FAILURE;
  }

  Lexer lex;

  lex.tokenize(file);

  std::cout << "Tokens:" << std::endl;
  for(const auto &tok : lex.getTokens()) {
    std::cout << "{" << tok.lexeme << ", " << TokenTypeStrings[tok.type] << "}" << std::endl;
  }

  return EXIT_SUCCESS;
}