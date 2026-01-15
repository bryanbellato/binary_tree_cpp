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

void SearchTree::insertEntity(NodeType *& tree, Entity entity, bool& isTaller) {
  
  if (tree == NULL) {
    tree = new NodeType;
    tree->right = NULL;
    tree->left = NULL;
    tree->entity = entity;
    tree->factorB = 0;
    isTaller = true;
    return;
  }
  else if (entity.getNum() < tree->entity.getNum() ) {
    insertEntity(tree->left, entity, isTaller);
    if(isTaller) {
      tree->factorB = tree->factorB - 1;
    }
  }
  else {
    insertEntity(tree->right, entity, isTaller);
    if (isTaller) {
      tree->factorB = tree->factorB + 1;
    }
  }

  performRotation(tree);

  if(isTaller && tree->factorB == 0) {
    isTaller = false;
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
void SearchTree::deleteEntity(NodeType*& tree, int entity, bool& isShorter) {
  
  if (tree == NULL) {
    isShorter = false;
    return;
  }

  if (entity < tree->entity.getNum()) {
    deleteEntity(tree->left, entity, isShorter);
    if(isShorter) {
      tree->factorB = tree->factorB + 1;
    }
  }
  else if(entity > tree->entity.getNum()) {
    deleteEntity(tree->right, entity, isShorter);
    if(isShorter) {
      tree->factorB = tree->factorB - 1;
    }
  }
  else if (entity == tree->entity.getNum()) {
    deleteNode(tree, isShorter);
  }
  
  if(tree != NULL) {
    performRotation(tree);

    if(isShorter && tree->factorB == 0) {
      isShorter = true;
    }
    else if(isShorter && (tree->factorB == 1 || tree->factorB == -1)) {
      isShorter = false;
    }
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
void SearchTree::deleteNode(NodeType*& tree, bool& isShorter) {
  Entity data;
  NodeType* tempPtr;
  tempPtr = tree;
  
  if (tree->left == NULL){
    tree = tree->right;
    delete tempPtr;
    isShorter = true;
  }
  else if (tree->right == NULL) {
    tree = tree->left;
    delete tempPtr;
    isShorter = true;
  }
  else {
    getSuccessor(tree, data);
    tree->entity = data;
    deleteEntity(tree->right, data.getNum(), isShorter);
    
    if(isShorter) {
      tree->factorB = tree->factorB - 1;
    }
  }
}

/*
  - first, we create a temp pointer to the right child
  - then, it re-allocates the left child to substitute the
  place of the current right child
  - then, the father node becomes the left child of the
  mentioned right child
*/
void SearchTree::rotateToLeft(NodeType*& tree) const {
  NodeType* p = tree->right;
  tree->right = p->left;
  p->left = tree;
  tree = p;
}

/*
  - first, we create a temp pointer to the left child
  - then, it re-allocates the right child to substitute the
  place of the current left child
  - then, the father node becomes the right child of the
  mentioned left child
*/
void SearchTree::rotateToRight(NodeType*& tree) const {
  NodeType* p = tree->left;
  tree->left = p->right;
  p->right = tree;
  tree = p;
}

void SearchTree::rotateToLeftAndRight(NodeType*& tree) const {
  NodeType* child = tree->left;
  rotateToLeft(child);
  tree->left = child;
  rotateToRight(tree);
}

void SearchTree::rotateToRightAndLeft(NodeType*& tree) const {
  NodeType* child = tree->right;
  rotateToRight(child);
  tree->right = child;
  rotateToLeft(tree);
}

void SearchTree::performRotation(NodeType*& tree) const {

  if (tree == NULL) {
    return;
  }

  NodeType* child;
  NodeType* grandChild;

  if(tree->factorB == -2) {
    child = tree->left;

    switch (child->factorB) {
    case -1:
      tree->factorB = 0;
      child->factorB = 0;
      rotateToRight(tree);
      break;
    case 0:
      tree->factorB = -1;
      child->factorB = +1;
      rotateToRight(tree);
      break;
    case 1:
      grandChild = child->right;
      switch(grandChild->factorB) {
      case -1:
        tree->factorB = 1;
        child->factorB = 0;
        break;
      case 0:
        tree->factorB = 0;
        child->factorB = 0;
        break;
      case 1:
        tree->factorB = 0;
        child->factorB = -1;
        break;
      }
      grandChild->factorB = 0;
      rotateToLeftAndRight(tree);
      break;
    }
  }
  else if(tree->factorB == 2) {
    child = tree->right;

    switch (child->factorB) {
    case 1:
      tree->factorB = 0;
      child->factorB = 0;
      rotateToLeft(tree);
      break;
    case 0:
      tree->factorB = 1;
      child->factorB = -1;
      rotateToLeft(tree);
      break;
    case -1:
      grandChild = child->left;
      switch(grandChild->factorB) {
      case 1:
        tree->factorB = -1;
        child->factorB = 0;
        break;
      case 0:
        tree->factorB = 0;
        child->factorB = 0;
        break;
      case -1:
        tree->factorB = 0;
        child->factorB = 1;
        break;
      }
      grandChild->factorB = 0;
      rotateToRightAndLeft(tree);
      break;
    }
  }
}
