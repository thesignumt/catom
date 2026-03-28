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

#define LEXER_AT_END(l) ((l)->cur >= (l)->end)

#define LEXER_PEEK(l) *(l)->cur

#define LEXER_PEEK_AHEAD(l, n) \
  (((l)->cur + (n) < (l)->end) ? *((l)->cur + (n)) : '\0')

#define LEXER_ADVANCE(l)   \
  do {                     \
    char _c = *(l)->cur++; \
    if (_c == '\n') {      \
      (l)->line++;         \
      (l)->col = 1;        \
    } else                 \
      (l)->col++;          \
                           \
  } while (0)

#define LEXER_ADVANCE_RET(l, c) \
  do {                          \
    c = *(l)->cur++;            \
    if (c == '\n') {            \
      (l)->line++;              \
      (l)->col = 1;             \
    } else                      \
      (l)->col++;               \
  } while (0)

// for read_ident_or_kw
#define MATCH_KEYWORD(len_val, str_val, token_type)                   \
  if (len == (len_val) && strncmp(l->tok, (str_val), (len_val)) == 0) \
    return lexer_emit(l, (token_type));

static inline bool match_ch(Lexer *lexer, char e) {
  if (LEXER_AT_END(lexer)) return false;
  if (LEXER_PEEK(lexer) != e) return false;
  LEXER_ADVANCE(lexer);
  return true;
}

#define IS_DIGIT(c) ((unsigned)((c) - '0') <= 9)
#define IS_ALPHA(c) (((unsigned)((c) | 32) - 'a') <= 25)
#define IS_ALNUM(c) (IS_ALPHA(c) || IS_DIGIT(c))

#endif  // TOKENIZER_H_
