#ifndef _VASM_PARSER_H_
#define _VASM_PARSER_H_

#include <cstdint>
#include <vector>

#include "lexer.h"
#include "token.h"

class Parser {
public:
  Parser();
  ~Parser();

  bool parse(const std::vector<tok::Token*> &tokens);
  void clear();
private:
  uint64_t _pc;
  std::vector<tok::Token*> _tokens;
  std::vector<tok::Instruction*> _instructions;
  std::vector<tok::Label*> _labels;

  bool _readTokens(std::vector<tok::Token*>::const_iterator &it, 
    const std::vector<tok::Token*>::const_iterator &end, const std::vector<TokenType> &sig,
    std::vector<tok::Token*> &arg_ptrs);
};

#endif