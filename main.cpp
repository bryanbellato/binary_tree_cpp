#include <iostream>
#include <string>

#include "binary_tree.h"
#include "entity.h"

using namespace std;

const int NUM_ENTITIES = 8;

int main() {
  SearchTree searchTree;
  int nums[NUM_ENTITIES] = {20, 18, 58, 7, 19, 26, 25, 30};
  string names[NUM_ENTITIES] = {
    "Linus", "Stallman", "Bjarne",
    "Notch", "Daniel", "Fabry",
    "Gottfrid", "Dexter"};
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

  searchTree.deleteEntity(entities[0].getNum());
  
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
