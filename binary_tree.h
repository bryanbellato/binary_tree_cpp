#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "entity.h"
/*
  we store the entity object and the
  pointers for addresses on equivalent
  sub-trees of the node.
  for factorB, it means the balacing factor
  of the respective tree.
  =========================================
  the equation:
  FB = left subtree height - right subtree height

  for instance:
  FB = 0 -> same height for both, perfectly balanced.
    10
   /  \
  5   15
  ---------------------------------------------------
  FB = 1 -> left subtree is one level higher.
  still well-balanced.
      10
     /  \
    5   15
   /
  3
  ---------------------------------------------------
  FB = -1 -> right subtree is one level higher.
  still well-balanced.
    10
      \
      15
        \
        20
  ---------------------------------------------------
  FB = 2 -> left subtree is two levels higher.
  UNBALANCED.
        10
       /
      5
     /
    3
  ---------------------------------------------------
  FB = -2 -> right subtree is two levels higher.
  UNBALANCED.
    10
      \
      15
        \
        20
  ---------------------------------------------------  
*/  
struct NodeType {
  Entity entity;
  int factorB;
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
  void insertEntity(Entity item) {
    bool isTaller; // indicates if our tree grew up
    insertEntity(root, item, isTaller);
  }
  void deleteEntity(int item) {
    bool isShorter; // indicates if our tree has been decreased
    deleteEntity(root, item, isShorter);
  }
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
  void insertEntity(NodeType*& tree, Entity item, bool& isTaller);
  void deleteEntity(NodeType*& tree, int item, bool& isShorter);
  void deleteNode(NodeType*& tree, bool& isShorter);
  // useful for deleting
  // it retrieves the lowest node value
  // on the right sub-tree as a substitute
  void getSuccessor(NodeType* tree, Entity& data);

  void printTree(NodeType *tree) const;
  void printPreOrder(NodeType* tree) const;
  void printInOrder(NodeType* tree) const;
  void printPostOrder(NodeType* tree) const;
  // for balancing the tree
  void rotateToLeft(NodeType*& tree) const;
  void rotateToRight(NodeType*& tree) const;
  void rotateToLeftAndRight(NodeType*& tree) const;
  void rotateToRightAndLeft(NodeType*& tree) const;
  void performRotation(NodeType*& tree) const;
  NodeType* root; // main pointer for the root node
};
#endif
