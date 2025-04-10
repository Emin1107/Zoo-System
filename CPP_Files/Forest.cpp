#include <iostream>
#include <string>
#include <vector>

#include "Forest.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"
#include "Enclosure.hpp"

Forest::Forest(int base_column, int base_row, int width, int height) :
  Enclosure(base_column, base_row, width, height) {}

Forest::~Forest() {}

EnclosureType Forest::getType() { return EnclosureType::Forest; }

std::string Forest::getDisplayString() { return "Forest"; }

bool Forest::isAnimalAllowed(AnimalType animal)
{
  return animal == AnimalType::Gorilla;
}

int Forest::calculateRating(const Zoo& zoo)
{
  int final_rating = 0;
  int gorilla_counter = 0;

  int enclosure_area = width_ * height_;
  
  final_rating += enclosure_area;
  final_rating += (animals_.size() * 2);

  if (base_row_ == 0 || base_row_ == zoo.getHeight() - 1 || base_column_ == 0 || base_column_ == zoo.getWidth() - 1)
  {
    final_rating *= 2;
  }

  return final_rating;
}
