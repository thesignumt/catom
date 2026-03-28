// #include "da.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

// +----------------------------------------------------------+
// [                Token creation (no malloc)                ]
// +----------------------------------------------------------+

static inline Token make_token(TokenType type, const char* start, size_t length,
                               size_t line, size_t col, const char* message) {
  return (Token){
      .type = type,
      .start = start,
      .length = length,
      .line = line,
      .col = col,
      .message = message,
  };
}

static inline Token lexer_emit(Lexer* l, TokenType type) {
  size_t len = (size_t)(l->cur - l->tok);
  return make_token(type, l->tok, len, l->line, l->col - len, NULL);
}

static inline Token error_token(Lexer* l, const char* message) {
  size_t len = (size_t)(l->cur - l->tok);
  return make_token(TT_ERROR, l->tok, len, l->line, l->col - len, message);
}

// +----------------------------------------------------------+
// [                           init                           ]
// +----------------------------------------------------------+

Lexer lexer_init(const char* src) {
  return (Lexer){
      .src = src,
      .cur = src,
      .end = src + strlen(src),
      .tok = src,
      .line = 1,
      .col = 1,
  };
}

// +----------------------------------------------------------+
// [                         skipping                         ]
// +----------------------------------------------------------+

void skip_whitespaces_and_comments(Lexer* l) {
  const char* cur = l->cur;

  for (;;) {
    char c = *cur;

    if (c == ' ' || c == '\r' || c == '\t') {
      cur++;
      l->col++;
      continue;
    }

    if (c == '\n') {
      cur++;
      l->line++;
      l->col = 1;
      continue;
    }

    if (c == '/' && cur[1] == '/') {
      cur += 2;
      l->col += 2;

      while (cur < l->end && *cur != '\n') {
        cur++;
        l->col++;
      }
      continue;
    }

    break;
  }

  l->cur = cur;
}

// +----------------------------------------------------------+
// [                         readers                          ]
// +----------------------------------------------------------+

Token read_ident_or_kw(Lexer* l) {
  const char* start = l->tok;

  while (IS_ALNUM(*l->cur) || *l->cur == '_') {
    l->cur++;
    l->col++;
  }

  size_t len = (size_t)(l->cur - start);

  switch (len) {
    case 2:
      if (memcmp(start, "if", 2) == 0) return lexer_emit(l, TT_IF);
      break;
    case 4:
      if (memcmp(start, "else", 4) == 0) return lexer_emit(l, TT_ELSE);
      break;
    case 5:
      if (memcmp(start, "while", 5) == 0) return lexer_emit(l, TT_WHILE);
      break;
    case 6:
      if (memcmp(start, "return", 6) == 0) return lexer_emit(l, TT_RETURN);
      break;
  }

  return lexer_emit(l, TT_IDENT);
}

Token read_number(Lexer* l) {
  while (IS_DIGIT(*l->cur)) {
    l->cur++;
    l->col++;
  }

  if (*l->cur == '.' && IS_DIGIT(l->cur[1])) {
    l->cur++;
    l->col++;

    while (IS_DIGIT(*l->cur)) {
      l->cur++;
      l->col++;
    }
  }

  return lexer_emit(l, TT_NUM);
}

Token read_string(Lexer* l) {
  while (*l->cur != '"' && l->cur < l->end) {
    if (*l->cur == '\n') {
      l->line++;
      l->col = 1;
    } else {
      l->col++;
    }
    l->cur++;
  }

  if (l->cur >= l->end) {
    return error_token(l, "Unterminated string");
  }

  /* consume closing quote */
  l->cur++;
  l->col++;

  return lexer_emit(l, TT_STR);
}

// +----------------------------------------------------------+
// [                        main lexer                        ]
// +----------------------------------------------------------+

Token lexer_next(Lexer* l) {
  skip_whitespaces_and_comments(l);

  l->tok = l->cur;

  if (l->cur >= l->end) {
    return lexer_emit(l, TT_EOF);
  }

  char c = *l->cur++;
  l->col++;

  if (IS_ALPHA(c) || c == '_') return read_ident_or_kw(l);
  if (IS_DIGIT(c)) return read_number(l);
  if (c == '"') return read_string(l);

  switch (c) {
    case '+':
      return lexer_emit(l, TT_PLUS);
    case '-':
      return lexer_emit(l, TT_MINUS);
    case '*':
      return lexer_emit(l, TT_STAR);
    case '/':
      return lexer_emit(l, TT_SLASH);

    case '=':
      if (*l->cur == '=') {
        l->cur++;
        l->col++;
        return lexer_emit(l, TT_EQ_EQ);
      }
      return lexer_emit(l, TT_EQ);

    case '(':
      return lexer_emit(l, TT_LPAREN);
    case ')':
      return lexer_emit(l, TT_RPAREN);
    case '{':
      return lexer_emit(l, TT_LBRACE);
    case '}':
      return lexer_emit(l, TT_RBRACE);
    case ';':
      return lexer_emit(l, TT_SEMI);
  }

  return error_token(l, "Unexpected character");
}

// Token* Tokenize(const char* src) {
//   Lexer lexer = lexer_init(src);
//   Token* ts = NULL;
//
//   while (1) {
//     Token token = next_token(&lexer);
//
//     da_push(ts, token);
//
//     if (token.type == TT_EOF) break;
//   }
//
//   return ts;
// }
