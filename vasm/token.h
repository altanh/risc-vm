#ifndef _VASM_TOKEN_H_
#define _VASM_TOKEN_H_

#include <string>

enum TokenType {
  kLitString = 0,
  kLitInteger,
  kLitFloat,
  kLabel,
  kIdentifier,
  kInstruction,
  kRegister,
  kNewline,
  kComma,
  kQuote,
  kIllegal
};

namespace tok {

// virtual
struct Token {
  std::string lexeme;
  TokenType type;

  Token();
  Token(const std::string &lex, TokenType t);

  virtual ~Token();

  virtual Token *clone() const;
};

static const std::vector<std::string> kTypeNames = {
  "kLitString",
  "kLitInteger",
  "kLitFloat",
  "kLabel",
  "kIdentifier",
  "kInstruction",
  "kRegister",
  "kNewline",
  "kComma",
  "kQuote",
  "kIllegal"
};

bool isString(const std::string &s);

bool isDec(const std::string &s);
bool isHex(const std::string &s);
bool isInteger(const std::string &s);

bool isLabel(const std::string &s);
bool isIdentifier(const std::string &s);
bool isInstruction(const std::string &s);
bool isRegister(const std::string &s);

// allocates a new Token of the correct type, must be freed by caller later
Token* fromLexeme(const std::string &lex);

struct LitString : Token {
  // escape sequences should be processed
  std::string str;

  LitString(const std::string &lex);

  virtual LitString *clone() const;
};

struct LitInteger : Token {
  uint64_t val;

  LitInteger(const std::string &lex, uint64_t v);

  virtual LitInteger *clone() const;
};

struct Label : Token {
  uint64_t addr;

  Label(const std::string &lex, uint64_t address);

  virtual Label *clone() const;
};

struct Identifier : Token {
  Identifier(const std::string &lex);
};

struct Instruction : Token {
  std::vector<Token*> args;

  static const std::vector<std::string> kNames;

  static const std::vector<std::string> kOpNames;
  static const std::vector<TokenType> kOpSignature;

  static const std::vector<std::string> kOpImmNames;
  static const std::vector<TokenType> kOpImmSignature;

  Instruction(const std::string &lex, const std::vector<Token*> &arguments);
  virtual Instruction *clone() const;

  static bool getSignature(const std::string &lex, std::vector<TokenType> &sig_dest);
};

struct Register : Token {
  /* 0 <= num <= 31 */
  size_t num;

  static const std::vector<std::string> kNames;

  Register(const std::string &lex, size_t n);

  virtual Register *clone() const;
};

struct Newline : Token {
  Newline();
};

struct Comma : Token {
  Comma();
};

struct Quote : Token {
  Quote();
};

struct Illegal : Token {
  Illegal(const std::string &lex);
};

}

#endif