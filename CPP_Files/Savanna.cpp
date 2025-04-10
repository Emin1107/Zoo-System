#include <iostream>
#include <string>
#include <vector>

#include "Savanna.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"
#include "Enclosure.hpp"

Savanna::Savanna(int base_column, int base_row, int width, int height) :
  Enclosure(base_column, base_row, width, height) {}

Savanna::~Savanna() {}

EnclosureType Savanna::getType() { return EnclosureType::Savanna; }

std::string Savanna::getDisplayString() { return "Savanna"; }

bool Savanna::isAnimalAllowed(AnimalType animal)
{
  if (animals_.empty())
  {
    return true;
  }
  
  for (auto& animal_check : animals_)
  {
    if (animal_check->getType() != animal)
    {
      return false;
    }
  }
  return true;
}

int Savanna::calculateRating(const Zoo& zoo)
{
  int final_rating = 0;
  int lion_counter = 0;
  int giraffe_counter = 0;

  int enclosure_area = width_ * height_;
  int zoo_area = zoo.getWidth() * zoo.getHeight();

  final_rating += (enclosure_area * 2);

  for (auto& animal : animals_)
  {
    if (animal != nullptr)
    {
      if (animal->getType() == AnimalType::Lion)
      {
        lion_counter++;
      }
      else
      {
        giraffe_counter++;
      }
    }
  }

  final_rating += (giraffe_counter * 3);

  if (lion_counter > (enclosure_area / 2))
  {
    final_rating += (lion_counter * 2);
  }
  else
  {
    final_rating += (lion_counter * 4);
  }

  if (enclosure_area > (zoo_area / 2))
  {
    final_rating *= 2;
  }

  return final_rating;
}
