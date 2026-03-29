#include <stdlib.h>

#include "ast.h"

Node* node_num(double value) {
  Node* n = malloc(sizeof(Node));
  n->type = NODE_NUM;
  n->num = value;
  return n;
}

Node* node_binop(Node* left, TokenType op, Node* right) {
  Node* n = malloc(sizeof(Node));
  n->type = NODE_BINOP;
  n->binop.left = left;
  n->binop.right = right;
  n->binop.op = op;
  return n;
}

void node_free(Node* n) {
  if (!n) return;

  if (n->type == NODE_BINOP) {
    node_free(n->binop.left);
    node_free(n->binop.right);
  }

  free(n);
}
