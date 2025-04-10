#ifndef AQUARIUM_HPP
#define AQUARIUM_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Enclosure.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"

class Aquarium : public Enclosure
{
public:
  Aquarium(int base_column, int base_row, int width, int height);
  Aquarium(const Aquarium&) = delete;
  ~Aquarium() override;

  EnclosureType getType() override;
  std::string getDisplayString() override;
  bool isAnimalAllowed(AnimalType animal) override;
  int calculateRating(const Zoo& zoo) override;
};


#endif