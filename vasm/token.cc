#include <string>
#include <regex>

#include "token.h"

bool Token::isInteger(const std::string &s) {
  const std::regex decReg("-?([[:digit:]]+)");
  const std::regex hexReg("-?(0x[[:xdigit:]]+)");

  return std::regex_match(s, decReg) || std::regex_match(s, hexReg);
}

bool Token::isLabel(const std::string &s) {
  const std::regex labelReg("[[:alpha:]_]+[[:alnum:]_]*:");

  return std::regex_match(s, labelReg);
}

bool Token::isIdentifier(const std::string &s) {
  const std::regex identReg("[[:alpha:]]+[[:alnum:]]*");

  return std::regex_match(s, identReg);
}

Token Token::fromLexeme(const std::string &lex) {
  if(isInteger(lex)) {
    return {lex, TokenType::kLitInteger};
  } else if(isLabel(lex)) {
    return {lex.substr(0, lex.size() - 1), TokenType::kLabel};
  } else if(isIdentifier(lex)) {
    return {lex, TokenType::kIdentifier};
  } else if(lex == ",") {
    return {lex, TokenType::kComma};
  } else {
    return {lex, TokenType::kIllegal};
  }
}