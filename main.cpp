//
//  main.cpp
//  paa-rb-avl-delete
//
//  Created by Taylor Schinvelski on 23/06/22.
//

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

#include "rbtree.hpp"
#include "avltree.hpp"

using namespace std;

int readFile(int* array, int size) {
  string folder = "./inputs/";
  string extension = ".txt";
  string filename = folder + to_string(size) + extension;

  ifstream file;
  file.open(filename);

  if (!file.is_open()) {
    throw runtime_error("Error opening file.");
  }

  for (int i = 0; file >> array[i]; i++) {
    if (i == size) {
      break;
    }
  }

  file.close();
  return 0;
}

int removeTree(int size) {
  cout << "Remove Balance: " << endl;
  RBTree *rbTree = new RBTree();
  AVLTree *avlTree = new AVLTree();
  int array[size];
  double time;

  try {
    readFile(array, size);

    for (int i = 0; i < size; i++) {
      rbTree->insert(array[i]);
    }
    
    for (int i = 0; i < size; i++) {
      avlTree->insert(array[i]);
    }

    clock_t ticks[2];
    ticks[0] = clock();

    for (int i = 0; i < size; i++) {
      rbTree->remove(array[i]);
    }
    
    ticks[1] = clock();
    time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        cout << "RB: " << time << " ms" << endl;
    
    ticks[0] = clock();

    for (int i = 0; i < size; i++) {
        avlTree->remove(array[i]);
    }

    ticks[1] = clock();
    time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    cout << "AVL: " << time << " ms" << endl;

  } catch (const runtime_error& error) {
    cerr << "Error: " << error.what() << endl;
  }

  return 0;
}

int removeTreePostorder(int size) {
  cout << "Remove Postorder: " << endl;
  RBTree *rbTree = new RBTree();
  AVLTree *avlTree = new AVLTree();
  int array[size];
  double time;

  try {
    readFile(array, size);

    for (int i = 0; i < size; i++) {
      rbTree->insert(array[i]);
    }
    
    for (int i = 0; i < size; i++) {
      avlTree->insert(array[i]);
    }

    clock_t ticks[2];
    ticks[0] = clock();

    rbTree->removePostorder();
    
    ticks[1] = clock();
    time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
        cout << "RB: " << time << " ms" << endl;
    
    ticks[0] = clock();

    avlTree->removePostorder();

    ticks[1] = clock();
    time = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    cout << "AVL: " << time << " ms" << endl;

  } catch (const runtime_error& error) {
    cerr << "Error: " << error.what() << endl;
  }

  return 0;
}

int main() {
   
  cout << "50: " << endl;
  removeTree(50);
  removeTreePostorder(50);
  cout << "100: " << endl;
  removeTree(100);
  removeTreePostorder(100);
  cout << "200: " << endl;
  removeTree(200);
  removeTreePostorder(200);
  cout << "300: " << endl;
  removeTree(300);
  removeTreePostorder(300);
  cout << "500: " << endl;
  removeTree(500);
  removeTreePostorder(500);
  cout << "750: " << endl;
  removeTree(750);
  removeTreePostorder(750);
  cout << "1000: " << endl;
  removeTree(1000);
  removeTreePostorder(1000);
  cout << "2000: " << endl;
  removeTree(2000);
  removeTreePostorder(2000);
  cout << "3000: " << endl;
  removeTree(3000);
  removeTreePostorder(3000);
  cout << "5000: " << endl;
  removeTree(5000);
  removeTreePostorder(5000);
  cout << "7500: " << endl;
  removeTree(7500);
  removeTreePostorder(7500);
  cout << "10000: " << endl;
  removeTree(10000);
  removeTreePostorder(125000);
  cout << "12500: " << endl;
  removeTree(12500);
  removeTreePostorder(12500);
  cout << "20000: " << endl;
  removeTree(20000);
  removeTreePostorder(20000);
  cout << "25000: " << endl;
  removeTree(25000);
  removeTreePostorder(25000);
  cout << "30000: " << endl;
  removeTree(30000);
  removeTreePostorder(30000);
  cout << "40000: " << endl;
  removeTree(40000);
  removeTreePostorder(125000);
  cout << "50000: " << endl;
  removeTree(50000);
  removeTreePostorder(50000);
  cout << "75000: " << endl;
  removeTree(75000);
  removeTreePostorder(75000);
  cout << "100000: " << endl;
  removeTree(100000);
  removeTreePostorder(125000);
  cout << "125000: " << endl;
  removeTree(125000);
  removeTreePostorder(125000);
  
  return 0;
}
