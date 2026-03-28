// #include "da.h"

#include "tokenizer.h"

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

// Token next_token(Lexer* ls) { ; }
//
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
