//
//  rbtree.hpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#ifndef rbtree_hpp
#define rbtree_hpp

#include <iostream>

#define BLACK 0
#define RED 1

using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  bool color;
};

class RBTree {
 private:
  Node *root = (Node *)malloc(sizeof(Node));
  Node *TNULL = (Node *)malloc(sizeof(Node));

  void leftRotate(Node *node);
  void rightRotate(Node *node);
  void transplant(Node *u, Node *v);
  void fixDelete(Node *node);
  void fixInsert(Node *node);
  void printHelper(Node *node, string indent, bool last);
  Node *createNode(int key);
  Node *searchTreeHelper(Node *node, int key);
  Node *searchTree(int key);
  Node *maximum(Node *node);

 public:
  RBTree();
  ~RBTree();

  void insert(int key);
  void remove(int key);
  void print();
};

#endif /* rbtree */
