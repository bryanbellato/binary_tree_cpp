#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "entity.h"

/*
  we store the entity object and the
  pointers for addresses on equivalent
  sub-trees of the node.
*/
struct NodeType {
  Entity entity;
  NodeType* left;
  NodeType* right;
};

class SearchTree {
 public:  
  // the constructor.
  // the root node will always be null when initialized. (duuuhhh)
  SearchTree() { root = NULL; }

  // the destructor.
  // when the object is out of the scope, it will clean our memory.
  ~SearchTree() { destroyTree(root); }

  bool isEmpty() const;
  bool isFull() const;

  // READ, CREATE, DELETE methods for the objects (duh)
  void retrieveEntity(Entity& item, bool& found) const {
    retrieveEntity(root, item, found);
  }
  void insertEntity(Entity item) { insertEntity(root, item); }
  void deleteEntity(int item) { deleteEntity(root, item); }

  // print methods with
  // traversal through different origins
  void printPreOrder() const { printPreOrder(root); }
  void printInOrder() const { printInOrder(root); }
  void printPostOrder() const { printPostOrder(root); }

 private:
  void destroyTree(NodeType*& tree);
  void retrieveEntity(NodeType* tree,
		      Entity& item,
		      bool& found) const;
  void insertEntity(NodeType*& tree, Entity item);
  void deleteEntity(NodeType*& tree, int item);
  void deleteNode(NodeType*& tree);

  // useful for deleting
  // it retrieves the lowest node value
  // on the right sub-tree as a substitute
  void getSuccessor(NodeType* tree, Entity& data);
  
  void printTree(NodeType *tree) const;
  void printPreOrder(NodeType* tree) const;
  void printInOrder(NodeType* tree) const;
  void printPostOrder(NodeType* tree) const;

  NodeType* root; // main pointer for the root node
};

#endif
