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

void skip_whitespaces_and_comments(Lexer* l) {
  while (!lexer_at_end(l)) {
    char c = lexer_peek(l);

    // Skip spaces, tabs, carriage returns
    if (c == ' ' || c == '\r' || c == '\t') {
      lexer_advance(l);
      continue;
    }

    // Skip newlines
    if (c == '\n') {
      lexer_advance(l);  // updates line/col
      continue;
    }

    // Skip single-line comments
    if (c == '/' && lexer_peek_ahead(l, 1) == '/') {
      while (lexer_peek(l) != '\n' && !lexer_at_end(l)) lexer_advance(l);

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
