// #include "da.h"

#include <stdlib.h>

#include "tokenizer.h"

static Token* make_token(TokenType type, const char* start, size_t length,
                         size_t line, size_t col) {
  Token* tok = (Token*)malloc(sizeof(Token));
  if (!tok) return NULL;

  tok->type = type;
  tok->start = start;  // points into lexer source
  tok->length = length;
  tok->line = line;
  tok->col = col;

  return tok;
}
static Token* lexer_emit(Lexer* lex, TokenType type) {
  size_t len = (size_t)(lex->cur - lex->tok);
  return make_token(type, lex->tok, len, lex->line, lex->col - len);
}

Lexer lexer_init(const char* src) {
  const char* end = src;
  while (*end) end++;

  return (Lexer){
      .src = src,
      .cur = src,
      .end = end,
      .tok = src,
      .line = 1,
      .col = 1,
  };
}

static char* slice(const char* tok, size_t cur) {
  if (!tok) return NULL;

  size_t len = strlen(tok);
  if (cur < 0) cur = 0;
  if ((size_t)cur > len) cur = len;

  size_t slice_len = len - cur;
  char* result = malloc(slice_len + 1);  // +1 for null terminator
  if (!result) return NULL;

  memcpy(result, tok + cur, slice_len);
  result[slice_len] = '\0';
  return result;
}

void skip_whitespaces_and_comments(Lexer* l) {
  while (!LEXER_AT_END(l)) {
    char c = LEXER_PEEK(l);

    // Skip spaces, tabs, carriage returns
    if (c == ' ' || c == '\r' || c == '\t') {
      LEXER_ADVANCE(l);
      continue;
    }

    // Skip newlines
    if (c == '\n') {
      LEXER_ADVANCE(l);  // updates line/col
      continue;
    }

    // Skip single-line comments
    if (c == '/' && LEXER_PEEK_AHEAD(l, 1) == '/') {
      while (LEXER_PEEK(l) != '\n' && !LEXER_AT_END(l)) LEXER_ADVANCE(l);

      continue;
    }

    // Anything else: stop
    break;
  }
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
