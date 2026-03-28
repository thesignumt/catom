#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdbool.h>
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
  TT_ERROR
} TokenType;

typedef struct {
  TokenType type;
  const char *start;
  size_t length;
  size_t line;
  size_t col;
  const char *message;
} Token;

typedef struct {
  const char *src;  // start of input
  const char *cur;  // current position
  const char *end;  // one past last char
  const char *tok;  // start of current token

  size_t line;
  size_t col;
} Lexer;

Lexer lexer_init(const char *src);

Token lexer_next(Lexer *l);

#define IS_DIGIT(c) ((unsigned)((c) - '0') <= 9)
#define IS_ALPHA(c) (((unsigned)((c) | 32) - 'a') <= 25)
#define IS_ALNUM(c) (IS_ALPHA(c) || IS_DIGIT(c))

Token *Tokenize(const char *src);

#endif  // TOKENIZER_H_
