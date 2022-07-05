//
//  rbtree.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#include "rbtree.hpp"

void RBTree::leftRotate(RBNode *node) {
  RBNode *rightNode = node->right;
  node->right = rightNode->left;

  if (rightNode->left != TNULL) {
    rightNode->left->parent = node;
  }
  rightNode->parent = node->parent;

  if (node->parent == nullptr) {
    root = rightNode;
  } else if (node == node->parent->left) {
    node->parent->left = rightNode;
  } else {
    node->parent->right = rightNode;
  }

  rightNode->left = node;
  node->parent = rightNode;
}

void RBTree::rightRotate(RBNode *node) {
  RBNode *leftNode = node->left;
  node->left = leftNode->right;

  if (leftNode->right != TNULL) {
    leftNode->right->parent = node;
  }
  leftNode->parent = node->parent;

  if (node->parent == nullptr) {
    root = leftNode;
  } else if (node == node->parent->right) {
    node->parent->right = leftNode;
  } else {
    node->parent->left = leftNode;
  }

  leftNode->right = node;
  node->parent = leftNode;
}

void RBTree::transplant(RBNode *x, RBNode *y) {
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->parent = x->parent;
}

void RBTree::fixDelete(RBNode *node) {
  RBNode *current;

  while (node != root && node->color == BLACK) {
    if (node == node->parent->left) {
      current = node->parent->right;

      if (current->color == RED) {
        current->color = BLACK;
        node->parent->color = RED;
        leftRotate(node->parent);
        current = node->parent->right;
      }

      if (current->left->color == BLACK && current->right->color == BLACK) {
        current->color = RED;
        node = node->parent;
      } else {
        if (current->right->color == BLACK) {
          current->left->color = BLACK;
          current->color = RED;
          rightRotate(current);
          current = node->parent->right;
        }

        current->color = node->parent->color;
        node->parent->color = BLACK;
        current->right->color = BLACK;
        leftRotate(node->parent);
        node = root;
      }
    } else {
      current = node->parent->left;
      if (current->color == RED) {
        current->color = BLACK;
        node->parent->color = RED;
        rightRotate(node->parent);
        current = node->parent->left;
      }

      if (current->right->color == BLACK && current->left->color == BLACK) {
        current->color = RED;
        node = node->parent;
      } else {
        if (current->left->color == BLACK) {
          current->right->color = BLACK;
          current->color = RED;
          leftRotate(current);
          current = node->parent->left;
        }

        current->color = node->parent->color;
        node->parent->color = BLACK;
        current->left->color = BLACK;
        rightRotate(node->parent);
        node = root;
      }
    }
  }

  node->color = BLACK;
}

void RBTree::fixInsert(RBNode *node) {
  RBNode *uncle;

  while (node->parent->color == RED) {
    if (node->parent == node->parent->parent->right) {
      uncle = node->parent->parent->left;

      if (uncle->color == RED) {
        uncle->color = BLACK;
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rightRotate(node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        leftRotate(node->parent->parent);
      }
    } else {
      uncle = node->parent->parent->right;

      if (uncle != nullptr && uncle->color == RED) {
        uncle->color = BLACK;
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          leftRotate(node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        rightRotate(node->parent->parent);
      }
    }

    if (node == root) {
      break;
    }
  }

  root->color = BLACK;
}

void RBTree::printHelper(RBNode *root, string indent, bool last) {
  if (root != TNULL) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "     ";
    } else {
      cout << "L----";
      indent += "|    ";
    }

    string color = root->color ? "R" : "B";
    cout << root->data << "(" << color << ")" << endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}

RBNode *RBTree::createNode(int key) {
  RBNode *node = new RBNode;
  node->data = key;
  node->parent = TNULL;
  node->left = TNULL;
  node->right = TNULL;
  node->color = RED;

  return node;
}

RBNode *RBTree::searchTreeHelper(RBNode *node, int key) {
  if (node == TNULL || key == node->data) {
    return node;
  }

  if (key < node->data) {
    return searchTreeHelper(node->left, key);
  } else {
    return searchTreeHelper(node->right, key);
  }
}

RBNode *RBTree::searchTree(int key) {
  return searchTreeHelper(root, key);
}

RBNode *RBTree::maximum(RBNode *node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

RBTree::RBTree() {
  TNULL = new RBNode;
  TNULL->color = BLACK;
  TNULL->left = nullptr;
  TNULL->right = nullptr;
  root = TNULL;
}

RBTree::~RBTree() {
  while (root != TNULL) {
    remove(root->data);
  }
}

void RBTree::insert(int key) {
  RBNode *node = createNode(key);

  RBNode *parent = nullptr;
  RBNode *current = root;

  while (current != TNULL) {
    parent = current;
    if (node->data < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  node->parent = parent;
  if (parent == nullptr) {
    root = node;
  } else if (node->data < parent->data) {
    parent->left = node;
  } else {
    parent->right = node;
  }

  if (node->parent == nullptr) {
    node->color = BLACK;
    return;
  } else if (node->parent->parent == nullptr) {
    return;
  } else {
    fixInsert(node);
  }
}

void RBTree::remove(int key) {
  RBNode *node = searchTree(key);

  if (node == TNULL) {
    cout << "Key: " << key << " can't be found" << endl;
    return;
  }

  RBNode *x, *y;
  bool color = node->color;
  y = node;

  if (node->left == TNULL) {
    x = node->right;
    transplant(node, node->right);
  } else if (node->right == TNULL) {
    x = node->left;
    transplant(node, node->left);
  } else {
    y = maximum(node->left);
    color = y->color;
    x = y->left;
    if (y->parent == node) {
      x->parent = y;
    } else {
      transplant(y, y->left);
      y->left = node->left;
      y->left->parent = y;
    }

    transplant(node, y);
    y->right = node->right;
    y->right->parent = y;
    y->color = node->color;
  }

  delete node;

  if (color == BLACK) {
    fixDelete(x);
  }
}

void RBTree::print() {
  printHelper(root, "", false);
}

void RBTree::removePostorderHelper(RBNode* node) {
  if (node == TNULL){
    return;
  }
 
  removePostorderHelper(node->left);
  removePostorderHelper(node->right);

  delete node;
}

void RBTree::removePostorder(){
  removePostorderHelper(root);
}
