#ifndef DOLPHIN_HPP
#define DOLPHIN_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

class Dolphin : public Animal
{
private:
  int fish_eaten_per_day_;

public:
  Dolphin(std::string name, int age, int fish_eaten_per_day);

  ~Dolphin() override;

  AnimalType getType() override;

  std::string getDisplayString() override;

  void printInformation() override;

  int getPrice() override;

};

#endif