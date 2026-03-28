#include <stdio.h>

#include "da.h"
#include "tokenizer.h"

const char *token_type_to_string(TokenType type) {
  switch (type) {
    // literals
    case TT_IDENT:
      return "IDENT";
    case TT_NUM:
      return "NUM";
    case TT_STR:
      return "STR";

    // keywords
    case TT_IF:
      return "IF";
    case TT_ELSE:
      return "ELSE";
    case TT_WHILE:
      return "WHILE";
    case TT_RETURN:
      return "RETURN";

    // operators
    case TT_PLUS:
      return "PLUS";
    case TT_MINUS:
      return "MINUS";
    case TT_STAR:
      return "STAR";
    case TT_SLASH:
      return "SLASH";
    case TT_EQ:
      return "EQ";
    case TT_EQ_EQ:
      return "EQ_EQ";

    // punctuation
    case TT_LPAREN:
      return "LPAREN";
    case TT_RPAREN:
      return "RPAREN";
    case TT_LBRACE:
      return "LBRACE";
    case TT_RBRACE:
      return "RBRACE";
    case TT_SEMI:
      return "SEMI";

    case TT_EOF:
      return "EOF";
    case TT_ERROR:
      return "ERROR";

    default:
      return "UNKNOWN";
  }
}
void print_token(Token *t) {
  if (!t) return;

  printf("Token {\n");

  printf("  type    : %s\n", token_type_to_string(t->type));

  printf("  lexeme  : \"");
  if (t->start && t->length > 0) {
    fwrite(t->start, 1, t->length, stdout);
  }
  printf("\"\n");

  printf("  length  : %zu\n", t->length);
  printf("  line    : %zu\n", t->line);
  printf("  col     : %zu\n", t->col);

  printf("  message : %s\n", t->message ? t->message : "(null)");

  printf("}\n");
}

int main(void) {
  Token *tokens = Tokenize("if (foo == 42) { return 0; }");

  for (int i = 0; i < (int)da_len(tokens); ++i) {
    print_token(&tokens[i]);
  }

  da_free(tokens);
  return 0;
}
