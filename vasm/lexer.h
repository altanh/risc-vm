#ifndef _RISC_V_ASM_LEXER_H_
#define _RISC_V_ASM_LEXER_H_

#include <iostream>
#include <vector>

#include "token.h"

class Lexer {
public:
  Lexer();
  ~Lexer();

  void tokenize(std::istream &is);
  void tokenizeLine(const std::string &line);

  const std::vector<Token> &getTokens() const;

private:
  std::vector<Token> _tokens;
};

#endif