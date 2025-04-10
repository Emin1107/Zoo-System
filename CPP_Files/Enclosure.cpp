#include <iostream>
#include <string>
#include <vector>

#include "Enclosure.hpp"
#include "Animal.hpp"
#include "Zoo.hpp"

Enclosure::Enclosure(int base_column, int base_row, int width, int height) :
  base_column_(base_column), base_row_(base_row), width_(width), height_(height) {}

Enclosure::~Enclosure()
{
  for (Animal* animal : animals_)
  {
    delete animal;
  }
}

std::string Enclosure::getFieldString()
{
  std::string field = "";
 
  field += this->getDisplayString()[0];

  try
  {
    std::string temp = animals_.at(map_animal_)->getDisplayString();
    field += temp[0];
    field += temp[1];

    map_animal_++;
  }
  catch(...)
  {
    field += "  ";
  }

  return field;
}

bool Enclosure::hasRoom()
{
  unsigned long size = height_ * width_;
  return (animals_.size() < size);
}

void Enclosure::addAnimal(Animal* animal)
{
  if (animal != nullptr)
  {
    animals_.push_back(animal);
  }
}

void Enclosure::resetMapAnimal()
{
  map_animal_ = 0;
}

int Enclosure::getMapAnimal() const
{
  return map_animal_;
}

void Enclosure::updateMapAnimal(int map_animal)
{
  map_animal_ = map_animal;
}

int Enclosure::getAnimalNumber() const
{
  return animals_.size();
}

void Enclosure::printAnimals() const
{
  for (auto* animal : animals_)
  {
    animal->printInformation();
  }
}

bool Enclosure::wasVisited() const
{
  return rate_visited;
}

void Enclosure::setVisitedToTrue()
{
  rate_visited = true;
}

void Enclosure::setVisitedToFalse()
{
  rate_visited = false;
}

