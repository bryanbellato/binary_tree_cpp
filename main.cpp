#include <iostream>
#include <string>

#include "binary_tree.h"
#include "entity.h"

using namespace std;

const int NUM_ENTITIES = 11;

int main() {
  SearchTree searchTree;
  int nums[NUM_ENTITIES] = {20, 11, 7, 8, 9, 17, 32, 67, 89, 24, 128};
  string names[NUM_ENTITIES] = {
    "20", "11", "7", "8", "9", "17", "32", "67", "89", "24", "128"};
  Entity entities[NUM_ENTITIES];

  for (int i = 0; i < NUM_ENTITIES; i++) {
    Entity entity = Entity(nums[i], names[i]);
    entities[i] = entity;
    searchTree.insertEntity(entity);
  }
  
  cout << "==============" << endl;
  
  cout << "Pre: ";
  searchTree.printPreOrder();
  cout << endl;

  cout << "In: ";
  searchTree.printInOrder();
  cout << endl;

  cout << "Post: ";
  searchTree.printPostOrder();
  cout << endl;

  searchTree.deleteEntity(entities[3].getNum());
  searchTree.deleteEntity(entities[0].getNum());
  searchTree.deleteEntity(entities[7].getNum());
  searchTree.deleteEntity(entities[5].getNum());
  
  cout << "==============" << endl;

  cout << "Pre: ";
  searchTree.printPreOrder();
  cout << endl;

  cout << "In: ";
  searchTree.printInOrder();
  cout << endl;

  cout << "Post: ";
  searchTree.printPostOrder();
  cout << endl;  
  
  return 0;
}
