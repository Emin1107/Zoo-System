#ifndef LION_HPP
#define LION_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Lion : public Animal
{
private:
  int mane_length_;

public:
  Lion(std::string name, int age, int mane_length);

  ~Lion() override;

  AnimalType getType() override;

  std::string getDisplayString() override;

  void printInformation() override;

  int getPrice() override;

};

#endif