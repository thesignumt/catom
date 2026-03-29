#ifndef PARSER_H_
#define PARSER_H_

#include "ast.h"
#include "tokenizer.h"

typedef struct {
  Token* tokens;
  size_t pos;
} Parser;

Node* parse(Token* tokens);

#endif  // PARSER_H_
