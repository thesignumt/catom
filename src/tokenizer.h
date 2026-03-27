#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stddef.h>
#include <stdint.h>

typedef enum {
  // literals
  TT_IDENT,
  TT_NUM,
  TT_STR,

  // keywords
  TT_IF,
  TT_ELSE,
  TT_WHILE,
  TT_RETURN,

  // operators
  TT_PLUS,
  TT_MINUS,
  TT_STAR,
  TT_SLASH,
  TT_EQ,
  TT_EQ_EQ,

  // punctuation
  TT_LPAREN,
  TT_RPAREN,
  TT_LBRACE,
  TT_RBRACE,
  TT_SEMI,

  TT_EOF,
} TokenType;

typedef struct {
  TokenType type;
  const char *start;
  size_t length;
  size_t line;
  size_t col;
} Token;

typedef struct {
  const char *start;  // beginning of input
  const char *cur;    // current position
  const char *end;    // end of input

  size_t line;
  size_t col;
} LexState;

#endif  // TOKENIZER_H_
