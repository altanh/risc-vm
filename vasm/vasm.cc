#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>

#include "parser.h"
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

  std::cout << "-- running lexical analysis on \"" << argv[1] << "\"" << std::endl;
  lex.tokenize(file);

  std::cout << "-- tokens:" << std::endl;
  for(const auto &tok : lex.getTokens()) {
    std::cout << "{" << tok->lexeme << ", " << tok::kTypeNames[tok->type] << "}" << std::endl;
  }

  Parser par;

  if(!par.parse(lex.getTokens())) {
    std::cerr << "-- parsing failed, terminating." << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}