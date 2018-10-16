#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "token.h"

using tok::LitString;
using tok::Token;
using tok::LitInteger;
using tok::Label;
using tok::Identifier;
using tok::Instruction;
using tok::Register;
using tok::Newline;
using tok::Comma;
using tok::Quote;
using tok::Illegal;

const std::vector<std::string> Instruction::kNames = {
  "add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and",
  "addi", "slti", "sltiu", "xori", "ori", "andi", "slli", "srli", "srai"
};

const std::vector<std::string> Instruction::kOpNames = {
  "add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and"
};

const std::vector<TokenType> Instruction::kOpSignature = {
  TokenType::kRegister, TokenType::kComma,
  TokenType::kRegister, TokenType::kComma,
  TokenType::kRegister
};

const std::vector<std::string> Instruction::kOpImmNames = {
  "addi", "slti", "sltiu", "xori", "ori", "andi", "slli", "srli", "srai"
};

const std::vector<TokenType> Instruction::kOpImmSignature = {
  TokenType::kRegister, TokenType::kComma,
  TokenType::kRegister, TokenType::kComma,
  TokenType::kLitInteger
};

const std::vector<std::string> Register::kNames = {
   "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",
   "x8",  "x9", "x10", "x11", "x12", "x13", "x14", "x15",
  "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
  "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31"
};

static bool _member(const std::string &s, const std::vector<std::string> &vec) {
  return std::find(vec.begin(), vec.end(), s) != vec.end();
}

Token::Token(const std::string &lex, TokenType t) : lexeme(lex), type(t) {}

Token::~Token() {}

Token* Token::clone() const {
  return new Token(this->lexeme, this->type);
}

bool tok::isDec(const std::string &s) {
  const std::regex dec_reg("-?([[:digit:]]+)");

  return std::regex_match(s, dec_reg);
}

bool tok::isHex(const std::string &s) {
  const std::regex hex_reg("-?(0x[[:xdigit:]]+)");

  return std::regex_match(s, hex_reg);
}

bool tok::isInteger(const std::string &s) {
  return isDec(s) || isHex(s);
}

bool tok::isLabel(const std::string &s) {
  const std::regex label_reg("[[:alpha:]_]+[[:alnum:]_]*:");

  return std::regex_match(s, label_reg);
}

bool tok::isIdentifier(const std::string &s) {
  const std::regex ident_reg("[[:alpha:]]+[[:alnum:]]*");

  return std::regex_match(s, ident_reg);
}

bool tok::isInstruction(const std::string &s) {
  return _member(s, Instruction::kNames);
}

bool tok::isRegister(const std::string &s) {
  return _member(s, Register::kNames);
}

Token* tok::fromLexeme(const std::string &lex) {
  // LitString not supported
  if(isInteger(lex)) {
    std::stringstream ss;
    int64_t val;

    ss << lex;
    if(isHex(lex)) {
      ss >> std::hex >> val;
    } else {
      ss >> val;
    }

    return new LitInteger(lex, (uint64_t) val);
  } else if(isLabel(lex)) {
    return new Label(lex.substr(0, lex.size() - 1), UINT64_MAX);
  } else if(isInstruction(lex)) {
    return new Instruction(lex, {});
  } else if(isRegister(lex)) {
    auto num = std::distance(std::begin(Register::kNames),
      std::find(std::begin(Register::kNames), std::end(Register::kNames), lex));
    return new Register(lex, num);
  } else if(isIdentifier(lex)) {
    return new Identifier(lex);
  } else if(lex == "\n") { 
    return new Newline();
  } else if(lex == ",") {
    return new Comma();
  } else if(lex == "\"") {
    return new Quote();
  } else {
    return new Illegal(lex);
  }
}

LitString::LitString(const std::string &lex) : Token(lex, TokenType::kLitString), str(lex) {}

LitString *LitString::clone() const {
  return new LitString(this->lexeme);
}

LitInteger::LitInteger(const std::string &lex, uint64_t v)
    : Token(lex, TokenType::kLitInteger), val(v) {}

LitInteger *LitInteger::clone() const {
  return new LitInteger(this->lexeme, this->val);
}

Label::Label(const std::string &lex, uint64_t address) : Token(lex, TokenType::kLabel), addr(address) {}

Label *Label::clone() const {
  return new Label(this->lexeme, this->addr);
}

Identifier::Identifier(const std::string &lex) : Token(lex, TokenType::kIdentifier) {}

Instruction::Instruction(const std::string &lex, const std::vector<Token*> &arguments)
  : Token(lex, TokenType::kInstruction),  args(arguments) {}

Instruction *Instruction::clone() const {
  return new Instruction(this->lexeme, this->args);
}

bool Instruction::getSignature(const std::string &lex, std::vector<TokenType> &sig_dest) {
  if(_member(lex, Instruction::kOpNames)) {
    sig_dest = Instruction::kOpSignature;
    return true;
  } else if(_member(lex, Instruction::kOpImmNames)) {
    sig_dest = Instruction::kOpImmSignature;
    return true;
  }

  return false;
}

Register::Register(const std::string &lex, size_t n) : Token(lex, TokenType::kRegister), num(n) {}

Register *Register::clone() const {
  return new Register(this->lexeme, this->num);
}

Newline::Newline() : Token("\\n", TokenType::kNewline) {}
Comma::Comma() : Token(",", TokenType::kComma) {}
Quote::Quote() : Token("\"", TokenType::kQuote) {}
Illegal::Illegal(const std::string &lex) : Token(lex, TokenType::kIllegal) {}
