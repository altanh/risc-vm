#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <stack>

#include "parser.h"
#include "token.h"

Parser::Parser() : _pc(0), _tokens(), _instructions(), _labels() {

}

Parser::~Parser() {
  for(tok::Token* tok_ptr : _tokens)
    if(tok_ptr)
      delete tok_ptr;

  for(tok::Instruction* inst_ptr : _instructions)
    if(inst_ptr)
      delete inst_ptr;

  for(tok::Label* label_ptr : _labels)
    if(label_ptr)
      delete label_ptr;
}

bool Parser::parse(const std::vector<tok::Token*> &tokens) {
  for(auto it = tokens.cbegin(); it != tokens.cend(); it++) {
    const tok::Token *tok = *it;
    _tokens.push_back(tok->clone());

    if(tok->type == TokenType::kInstruction) {
      std::vector<TokenType> sig;
      if(!tok::Instruction::getSignature(tok->lexeme, sig)) {
        std::cerr << "error: unsupported instruction \"" << tok->lexeme << "\"" << std::endl;
        clear();
        return false;
      }

      std::vector<tok::Token*> args;
      if(!_readTokens(it, tokens.cend(), sig, args)) {
        std::cerr << "error: parsing failed for instruction \"" 
                  << tok->lexeme << "\"" << std::endl;
        clear();
        return false;
      }

      _instructions.push_back(new tok::Instruction(tok->lexeme, args));
      _pc += 4;
    } else if(tok->type == TokenType::kLabel) {
      _labels.push_back(new tok::Label(tok->lexeme, _pc));
    } else if(tok->type == TokenType::kNewline) {
      // do nothing
    } else {
      std::cerr << "error: unexpected token \"" << tok->lexeme 
                << "\" of type " << tok::kTypeNames[tok->type] << std::endl;

      clear();

      return false;
    }
  }

  for(auto &i : _instructions) {
    std::cout << "instruction: " << i->lexeme << std::endl
              << "\targs:";

    for(auto &a : i->args) {
      std::cout << " " << a->lexeme;
    }

    std::cout << std::endl;
  }

  for(auto &l : _labels) {
    std::cout << "label: " << l->lexeme << "[0x" << std::hex << l->addr << std::dec << "]" << std::endl;
  }

  return true;
}

bool Parser::_readTokens(std::vector<tok::Token*>::const_iterator &it, 
  const std::vector<tok::Token*>::const_iterator &end, const std::vector<TokenType> &sig,
  std::vector<tok::Token*> &arg_ptrs) {
  for(const auto &type : sig) {
    ++it;
    if(it == end) {
      if(type != TokenType::kNewline) {
        std::cerr << "error: expected token of type " << tok::kTypeNames[type]
                << ", but got nothing" << std::endl;

        return false;
      }

      // let's treat a missing newline as alright if there are no more tokens
      return true;
    }

    if((*it)->type != type) {
      std::cerr << "error: expected token of type " << tok::kTypeNames[type]
                << ", but got \"" << (*it)->lexeme << "\" of type " << tok::kTypeNames[(*it)->type]
                << " instead" << std::endl;

      return false;
    }

    _tokens.push_back((*it)->clone());
    if(type != TokenType::kNewline && type != TokenType::kComma) {
      arg_ptrs.push_back(_tokens.back());
    }
  }

  return true;
}

void Parser::clear() {
  _tokens.clear();
  _labels.clear();
  _instructions.clear();
}
