#ifndef _VASM_LEXER_H_
#define _VASM_LEXER_H_

#include <iostream>
#include <vector>

#include "token.h"

class Lexer {
public:
  Lexer();
  ~Lexer();

  void tokenize(std::istream &is);
  void tokenizeLine(const std::string &line);

  const std::vector<tok::Token*> &getTokens() const;

private:
  std::vector<tok::Token*> _tokens;
};

#endif