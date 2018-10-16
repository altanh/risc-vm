#include <cctype>
#include <string>

#include "lexer.h"
#include "token.h"

Lexer::Lexer() : _tokens() {

}

Lexer::~Lexer() {
  for(tok::Token *ptr : _tokens)
    if(ptr)
      delete ptr;
}

void Lexer::tokenize(std::istream &is) {
  std::string line;
  while(std::getline(is, line)) {
    tokenizeLine(line);
  }
}

void Lexer::tokenizeLine(const std::string &line) {
  bool in_string = false;
  bool in_lexeme = false;
  size_t lexeme_start = 0; 

  for(size_t i = 0; i < line.size(); ++i) {
    // quote and not escaped
    if(line[i] == '\"' && (i == 0 || (line[i - 1] != '\\'))) {
      if(in_string) {
        // TODO: process escape sequences
        _tokens.push_back(new tok::LitString(line.substr(lexeme_start, i - lexeme_start)));

        in_lexeme = false;
      }

      in_string = !in_string;

      _tokens.push_back(new tok::Quote());
    } else if(line[i] == ';') {
      // done, rest of the line is a comment
      break;
    } else if((std::isspace(line[i]) || line[i] == ',') && !in_string) {
      if(in_lexeme)
        _tokens.push_back(tok::fromLexeme(line.substr(lexeme_start, i - lexeme_start)));

      if(line[i] == ',')
        _tokens.push_back(new tok::Comma());

      in_lexeme = false;
    } else {
      if(!in_lexeme) {
        lexeme_start = i;
        in_lexeme = true;
      }
    }
  }

  if(in_lexeme)
    _tokens.push_back(tok::fromLexeme(line.substr(lexeme_start, std::string::npos)));

  _tokens.push_back(new tok::Newline());
}

const std::vector<tok::Token*> &Lexer::getTokens() const {
  return _tokens;
}