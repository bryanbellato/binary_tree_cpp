#include "binary_tree.h"
#include <iostream>

void SearchTree::destroyTree(NodeType*& tree) {

  /* recursively, in post order,
     unnalocate each sub-tree
     out of the memory.
  */
  if(tree != NULL) {
    destroyTree(tree->left);
    destroyTree(tree->right);
    delete tree;
  }
  
}

// verifies if the root node is pointing to null.
bool SearchTree::isEmpty() const {
  return root == NULL;
}

// tries to allocate a memory.
// if it's possible, it is not full.
bool SearchTree::isFull() const {
  NodeType* location;
  try {
    location = new NodeType;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception) {
    return true;
  }
}

/*
  we receive a tree, initially.
  
  if the query num value is lower than the root/current node value:
  the query moves for the left node.

  if the query num value is greater than the root/current node value:
  the query moves for the right node.
*/
void SearchTree::retrieveEntity(NodeType* tree,
				Entity& entity,
				bool& found) const {
  if (tree == NULL) {
    found = false;
  }
  else if (entity.getNum() < tree->entity.getNum()) {
    retrieveEntity(tree->left, entity, found);
  }
  else if(entity.getNum() > tree->entity.getNum()) {
    retrieveEntity(tree->right, entity, found);
  }
  else {
    entity = tree->entity;
    found = true;
  }
    
}

void SearchTree::insertEntity(NodeType *& tree, Entity entity) {
  
  if (tree == NULL) {
    tree = new NodeType;
    tree->right = NULL;
    tree->left = NULL;
    tree->entity = entity;
  }
  else if (entity.getNum() < tree->entity.getNum() ) {
    insertEntity(tree->left, entity);    
  }
  else {
    insertEntity(tree->right, entity);
  }
  
}

void SearchTree::printPreOrder(NodeType* tree) const {
  if (tree != NULL) {
    std::cout << tree->entity.getName() << " , ";
    printPreOrder(tree->left);
    printPreOrder(tree->right);    
  }
}

void SearchTree::printInOrder(NodeType* tree) const {
  if (tree != NULL) {
    printInOrder(tree->left);
    std::cout << tree-> entity.getName() << " , ";
    printInOrder(tree->right);
  }
}

void SearchTree::printPostOrder(NodeType* tree) const {
  if (tree != NULL) {
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    std::cout << tree->entity.getName() << " , ";
  }
}

// traverse over the tree for deleting a node with
// a entity as a parameter
void SearchTree::deleteEntity(NodeType*& tree, int entity) {
  
  if (entity < tree->entity.getNum()) {
    deleteEntity(tree->left, entity);
  }
  else if(entity > tree->entity.getNum() ) {
    deleteEntity(tree->right, entity);
  }
  else if (entity == tree->entity.getNum()) {
    deleteNode(tree);
  }
  
}

/*
  this case considers if the node will be removed, but
  it has two children.

  - it moves to the higher value children
  - then it traverse over the lowest value om the
  sub-tree of the children node
  - finally, it moves the lowest value to the node that
  will be removed.
*/
void SearchTree::getSuccessor(NodeType* tree, Entity& data) {
  tree = tree->right;
  while (tree->left != NULL){
    tree = tree->left;
  }
  data = tree->entity;
}

/*
  takes a node by parameter and delete it considering these cases:
  1. the node is a leaf (no children)
  2. the node has a child
  3. the node has two children

  if either one of the sides has a child:
   - the selected node is deleted
   - the children node of the selected node will be hold
   by the father node of the selected node

   if both sides doesn't have children:
   - the selected node is deleted
   - it has no children, no re-allocation.

   read the comments for getSuccessor method if
   you want to know more about the case
   where it has two children.
   
*/
void SearchTree::deleteNode(NodeType*& tree) {
  Entity data;
  NodeType* tempPtr;
  tempPtr = tree;
  
  if (tree->left == NULL){
    tree = tree->right;
    delete tempPtr;
  }
  else if (tree->right == NULL) {
    tree = tree->left;
    delete tempPtr;
  }
  else {
    getSuccessor(tree, data);
    tree->entity = data;
    deleteEntity(tree->right, data.getNum());
  }
  
}


