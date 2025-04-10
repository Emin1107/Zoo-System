#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Giraffe : public Animal
{
private:
  float neck_height_;

public:
  Giraffe(std::string name, int age, float neck_height);

  ~Giraffe() override;

  AnimalType getType() override;

  std::string getDisplayString() override;

  void printInformation() override;

  int getPrice() override;

};

#endif