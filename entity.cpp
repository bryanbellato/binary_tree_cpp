#include "entity.h"

/*
  for our entity constructor,
  without parameters:

  -1 as a num is for being recognized as
  a invalid input on a query system.

  so on, the name would be blank.
*/
Entity::Entity() {
  this->num = -1;
  this->name = "";
}

Entity::Entity(int num, std::string name){
  this->num = num;
  this->name = name;
}

std::string Entity::getName() const {
  return name;
}

int Entity::getNum() const {
  return num;
}

