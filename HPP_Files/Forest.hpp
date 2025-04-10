#ifndef FOREST_HPP
#define FOREST_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Enclosure.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"

class Forest : public Enclosure
{
public:
  Forest(int base_column, int base_row, int width, int height);
  Forest(const Forest&) = delete;
  ~Forest() override; // Destructor is defaulted

  EnclosureType getType() override;
  std::string getDisplayString() override;
  bool isAnimalAllowed(AnimalType animal) override;
  int calculateRating(const Zoo& zoo) override;
};


#endif