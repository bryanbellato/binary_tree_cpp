#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

/*
  basically our model file,
  just like the model concept
  on other OOP languages.
*/

// we will receive the entity name using the num as a query.
class Entity{
 private:
  int num;
  std::string name;
 public:
  // constructors (duh)
  Entity();
  Entity(int num, std::string name);

  // getters methods (duh)
  std::string getName() const;
  int getNum() const;
};

#endif
