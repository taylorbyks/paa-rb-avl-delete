//
//  avltree.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 26/06/22.
//

#include "avltree.hpp"

// void AVLTree::left_r(AVLNode* x) {
//   AVLNode* y = x->right;
//   x->right = y->left;
//   if (y->left != nullptr) {
//     y->left->parent = x;
//   }
//   y->parent = x->parent;
//   if (x->parent == nullptr) {
//     root = y;
//   }
//   else if (x == x->parent->left) {
//     x->parent->left = y;
//   }
//   else {
//     x->parent->right = y;
//   }
//   y->left = x;
//   x->parent = y;

//   x->height = x->height - 1 - max(0, y->height);
//   y->height = y->height - 1 + min(0, x->height);
// }

// void AVLTree::right_r(AVLNode* x) {
//   AVLNode* y = x->left;
//   x->left = y->right;
//   if (y->right != nullptr) {
//     y->right->parent = x;
//   }
//   y->parent = x->parent;
//   if (x->parent == nullptr) {
//     root = y;
//   }
//   else if (x == x->parent->right) {
//     x->parent->right = y;
//   }
//   else {
//     x->parent->left = y;
//   }
//   y->right = x;
//   x->parent = y;

//   x->height = x->height + 1 - min(0, y->height);
//   y->height = y->height + 1 + max(0, x->height);
// }

// void AVLTree::rebalance(AVLNode* n) {
//   if ((n->height < -1) || (n->height > 1)) {
//     if (n->height > 0) {
//       if (n->right->height < 0) {
//         right_r(n->right);
//         left_r(n);
//       }
//       else {
//         left_r(n);
//       }
//     }
//     else if (n->height < 0) {
//       if (n->left->height > 0) {
//         left_r(n->left);
//         right_r(n);
//       }
//       else {
//         right_r(n);
//       }
//     }
//     return;
//   }
//   if (n->parent != nullptr) {
//     if (n == n->parent->left) {
//       n->parent->height -= 1;
//     }
//     if (n == n->parent->right) {
//       n->parent->height += 1;
//     }
//     if (n->parent->height != 0) {
//       rebalance(n->parent);
//     }
//   }
// }

AVLNode *AVLTree::createNode(int key) {
  AVLNode *node = new AVLNode;
  node->data = key;
  node->parent = nullptr;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 0;

  return node;
}

AVLNode *AVLTree::minimum(AVLNode *node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

AVLTree::AVLTree() { root = nullptr; }

AVLTree::~AVLTree() {
  while (root != nullptr) {
    remove(root->data);
  }
}

AVLNode *AVLTree::searchTreeHelper(AVLNode *node, int key) {
  if (node == nullptr || key == node->data) {
    return node;
  }

  if (key < node->data) {
    return searchTreeHelper(node->left, key);
  } else {
    return searchTreeHelper(node->right, key);
  }
}

AVLNode *AVLTree::searchTree(int key) {
  return searchTreeHelper(root, key);
}

void AVLTree::insert(int key) {
  AVLNode *node = createNode(key);

  AVLNode *parent = nullptr;
  AVLNode *current = root;

  while (current != nullptr) {
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
  } else {
    if (node->data < parent->data) {
      parent->left = node;
    } else {
      parent->right = node;
    }
  }

  balance(node);
}

void AVLTree::remove(int data) { removeHelper(data, root); }

void AVLTree::removeHelper(const int &x, AVLNode *&t) {
  if (t == nullptr) return;

  if (x < t->data)
    removeHelper(x, t->left);
  else if (t->data < x)
    removeHelper(x, t->right);
  else if (t->left != nullptr && t->right != nullptr) {
    t->data = minimum(t->right)->data;
    removeHelper(t->data, t->right);
  } else {
    AVLNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }

  balance(t);
}

void AVLTree::printHelper(AVLNode *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "     ";
    } else {
      cout << "L----";
      indent += "|    ";
    }

    cout << root->data << "(" << root->height << ")" << endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}

void AVLTree::print() { printHelper(root, "", false); }

int AVLTree::height(AVLNode *t) {
  if (t == nullptr) {
    return -1;
  } else {
    return t->height;
  }
}

void AVLTree::balance(AVLNode *&t) {
  if (t == nullptr) return;

  if (height(t->left) - height(t->right) > 1)
    if (height(t->left->left) >= height(t->left->right))
      rotateWithLeftChild(t);
    else
      doubleWithLeftChild(t);
  else if (height(t->right) - height(t->left) > 1)
    if (height(t->right->right) >= height(t->right->left)) {
      rotateWithRightChild(t);
    } else {
      doubleWithRightChild(t);
    }

  t->height = max(height(t->left), height(t->right)) + 1;
}

void AVLTree::rotateWithLeftChild(AVLNode *&k2) {
  AVLNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = max(height(k2->left), height(k2->right)) + 1;
  k1->height = max(height(k1->left), k2->height) + 1;
  k2 = k1;
}

void AVLTree::rotateWithRightChild(AVLNode *&k1) {
  AVLNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max(height(k1->left), height(k1->right)) + 1;
  k2->height = max(height(k2->right), k1->height) + 1;
  k1 = k2;
}

void AVLTree::doubleWithLeftChild(AVLNode *&k3) {
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

void AVLTree::doubleWithRightChild(AVLNode *&k1) {
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}
