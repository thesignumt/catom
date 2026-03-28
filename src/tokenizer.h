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
  const char *src;  // start of input
  const char *cur;  // current position
  const char *end;  // one past last char
  const char *tok;  // start of current token

  size_t line;
  size_t col;
} Lexer;

Lexer lexer_init(const char *src);

#define lexer_at_end(l) ((l)->cur >= (l)->end)

#define lexer_peek(l) *(l)->cur

#define lexer_peek_ahead(l, n) \
  (((l)->cur + (n) < (l)->end) ? *((l)->cur + (n)) : '\0')

#define lexer_advance(l, c) \
  do {                      \
    c = *(l)->cur++;        \
    if (c == '\n') {        \
      (l)->line++;          \
      (l)->col = 1;         \
    } else                  \
      (l)->col++;           \
  } while (0)

#endif  // TOKENIZER_H_
