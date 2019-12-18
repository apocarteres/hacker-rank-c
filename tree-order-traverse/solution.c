//https://www.hackerrank.com/challenges/tree-level-order-traversal/problem
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct node *insert(struct node *root, int data) {
  if (root == NULL) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
  } else {
    struct node *cur;
    if (data <= root->data) {
      cur = insert(root->left, data);
      root->left = cur;
    } else {
      cur = insert(root->right, data);
      root->right = cur;
    }
    return root;
  }
}

char isLeaf(struct node *node) { return node == NULL; }

void levelOrderWithLimit(struct node *root, int level, int limit) {
  if (level < limit) {
    if (!isLeaf(root->left)) {
      levelOrderWithLimit(root->left, level + 1, limit);
    }
    if (!isLeaf(root->right)) {
      levelOrderWithLimit(root->right, level + 1, limit);
    }
  }
  if (!isLeaf(root) && level == limit) {
    printf("%d ", root->data);
  }
}

int tree_height(struct node *root, int height) {
  int right_h =
      isLeaf(root->right) ? height : tree_height(root->right, height + 1);
  int left_h =
      isLeaf(root->left) ? height : tree_height(root->left, height + 1);
  return right_h > left_h ? right_h : left_h;
}

void levelOrder(struct node *root) {
  int height = tree_height(root, 1);
  for (int i = 0; i < height; ++i) {
    levelOrderWithLimit(root, 0, i);
  }
}

int main(int argc, char **argv) {
  struct node *root = NULL;
  ++argv;
  int t = atoi(*argv);
  ++argv;
  int data;
  while (t-- > 0) {
    data = atoi(*argv);
    root = insert(root, data);
    ++argv;
  }

  levelOrder(root);
  return 0;
}
