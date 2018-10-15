#ifndef _RISC_VM_ASM_TOKEN_H
#define _RISC_VM_ASM_TOKEN_H

#include <string>

enum TokenType {
  kLitString = 0,
  kLitInteger,
  kLitFloat,
  kLabel,
  kIdentifier,
  kNewline,
  kComma,
  kQuote,
  kIllegal
};

static const std::string TokenTypeStrings[] = {
  "kLitString",
  "kLitInteger",
  "kLitFloat",
  "kLabel",
  "kIdentifier",
  "kNewline",
  "kComma",
  "kQuote",
  "kIllegal"
};

struct Token {
  std::string lexeme;
  TokenType type;

  static Token fromLexeme(const std::string &lex);
  static bool isString(const std::string &s);
  static bool isInteger(const std::string &s);
  static bool isLabel(const std::string &s);
  static bool isIdentifier(const std::string &s);
};

#endif