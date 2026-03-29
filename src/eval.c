#include "eval.h"

double eval(Node* n) {
  switch (n->type) {
    case NODE_NUM:
      return n->num;

    case NODE_BINOP: {
      double l = eval(n->binop.left);
      double r = eval(n->binop.right);

      switch (n->binop.op) {
        case TT_PLUS:
          return l + r;
        case TT_MINUS:
          return l - r;
        case TT_STAR:
          return l * r;
        case TT_SLASH:
          return l / r;
        default:
          return 0;
      }
    }
  }
  return 0;
}
