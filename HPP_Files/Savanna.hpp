#ifndef SAVANNA_HPP
#define SAVANNA_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Enclosure.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"

class Savanna : public Enclosure
{
public:
  Savanna(int base_column, int base_row, int width, int height);
  Savanna(const Savanna&) = delete;
  ~Savanna() override; // Destructor is defaulted

  EnclosureType getType() override;
  std::string getDisplayString() override;
  bool isAnimalAllowed(AnimalType animal) override;
  int calculateRating(const Zoo& zoo) override;
};


#endif