#ifndef GORILLA_HPP
#define GORILLA_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Gorilla : public Animal
{
private:
  float weight_;

public:
  Gorilla(std::string name, int age, float weight);

  ~Gorilla() override;

  AnimalType getType() override;

  std::string getDisplayString() override;

  void printInformation() override;

  int getPrice() override;

};

#endif