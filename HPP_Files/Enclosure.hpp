#ifndef ENCLOSURE_HPP
#define ENCLOSURE_HPP

#include <iostream>
#include <vector>
#include <string>

#include "Animal.hpp"

class Zoo;

enum class EnclosureType
{
  Savanna,
  Forest,
  Aquarium
};

class Enclosure
{
protected:
  int base_column_;
  int base_row_;
  int width_;
  int height_;
  int map_animal_ = 0;
  bool rate_visited = false;
  std::vector<Animal*> animals_;

public:
  Enclosure(int base_column, int base_row, int width, int height);

  Enclosure(const Enclosure&) = delete;
  virtual ~Enclosure();

  virtual EnclosureType getType() = 0;
  virtual std::string getDisplayString() = 0;
  virtual bool isAnimalAllowed(AnimalType animal) = 0;
  virtual int calculateRating(const Zoo& zoo) = 0;
  std::string getFieldString();
  bool hasRoom();
  void addAnimal(Animal* animal);
  void resetMapAnimal();
  int getMapAnimal() const;
  void updateMapAnimal(int map_animal);
  int getAnimalNumber() const;
  void printAnimals() const;
  bool wasVisited() const;
  void setVisitedToTrue();
  void setVisitedToFalse();
};

#endif