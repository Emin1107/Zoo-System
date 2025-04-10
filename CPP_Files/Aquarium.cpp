#include <iostream>
#include <string>
#include <vector>

#include "Aquarium.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"
#include "Enclosure.hpp"

Aquarium::Aquarium(int base_column, int base_row, int width, int height) :
  Enclosure(base_column, base_row, width, height) {}

Aquarium::~Aquarium() {}

EnclosureType Aquarium::getType() { return EnclosureType::Aquarium; }

std::string Aquarium::getDisplayString() { return "Aquarium"; }

bool Aquarium::isAnimalAllowed(AnimalType animal)
{
  return animal == AnimalType::Dolphin;
}

int Aquarium::calculateRating(const Zoo& zoo)
{
  int final_rating = 0;
  int forest_counter = 0;

  int enclosure_area = width_ * height_;
  
  final_rating += (enclosure_area * 3);
  final_rating += (animals_.size() * 4);

  std::vector<Enclosure*> forest_visited;

  for (int row = base_row_ - 1; row <= base_row_ + height_; row++)
  {
    for (int column = base_column_ - 1; column <= base_column_ + width_; column++)
    {
      if (row >= 0 && row < zoo.getHeight() && column >= 0 && column < zoo.getWidth())
      {
        auto& enclosure = zoo.getEnclosures()[row][column];

        if (enclosure != nullptr && enclosure != this && 
            enclosure->getType() == EnclosureType::Forest)
        {
          bool visited = false;
          for (auto& forest : forest_visited)
          {
            if (forest == enclosure)
            {
              visited = true;
              break;
            }
          }

          if (!visited)
          {
            forest_visited.push_back(enclosure);
            forest_counter++;
          }
        }
      }
    }
  }

  final_rating /= (1 + forest_counter);

  return final_rating;
}
