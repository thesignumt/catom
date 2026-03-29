#include <stdlib.h>
#include <string.h>

#include "parser.h"

static Token* peek(Parser* p) { return &p->tokens[p->pos]; }

static int match(Parser* p, TokenType t) {
  if (peek(p)->type != t) return 0;
  p->pos++;
  return 1;
}

static Node* parse_expr(Parser* p);

static Node* parse_factor(Parser* p) {
  Token* t = peek(p);

  if (match(p, TT_NUM)) {
    char buf[64];
    memcpy(buf, t->start, t->length);
    buf[t->length] = '\0';

    double val = strtod(buf, NULL);
    return node_num(val);
  }

  if (match(p, TT_LPAREN)) {
    Node* n = parse_expr(p);
    match(p, TT_RPAREN);
    return n;
  }

  return NULL;
}

static Node* parse_term(Parser* p) {
  Node* left = parse_factor(p);

  while (peek(p)->type == TT_STAR || peek(p)->type == TT_SLASH) {
    TokenType op = peek(p)->type;
    p->pos++;

    Node* right = parse_factor(p);
    left = node_binop(left, op, right);
  }

  return left;
}

static Node* parse_expr(Parser* p) {
  Node* left = parse_term(p);

  while (peek(p)->type == TT_PLUS || peek(p)->type == TT_MINUS) {
    TokenType op = peek(p)->type;
    p->pos++;

    Node* right = parse_term(p);
    left = node_binop(left, op, right);
  }

  return left;
}

Node* parse(Token* tokens) {
  Parser p = {.tokens = tokens, .pos = 0};
  return parse_expr(&p);
}
