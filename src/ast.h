#ifndef AST_H_
#define AST_H_

#include "tokenizer.h"

typedef enum {
  NODE_NUM,
  NODE_BINOP,
} NodeType;

typedef struct Node {
  NodeType type;

  union {
    double num;

    struct {
      struct Node* left;
      struct Node* right;
      TokenType op;
    } binop;
  };
} Node;

Node* node_num(double value);
Node* node_binop(Node* left, TokenType op, Node* right);
void node_free(Node* n);

#endif  // AST_H_
