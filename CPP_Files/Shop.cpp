#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Shop.hpp"
#include "Animal.hpp"
#include "Utils.hpp"
#include "Lion.hpp"
#include "Giraffe.hpp"
#include "Gorilla.hpp"
#include "Dolphin.hpp"

bool Shop::tryLoadConfig(std::string path)
{
  std::ifstream file(path);
  if (!file.is_open()) { return false; }

  std::string line;

  std::getline(file, line);
  if (line != "OOP") { return false; }

  std::getline(file, line);
  name_ = line;

  while (std::getline(file, line))
  {
    int position = 0;
    position = line.find(';');
    std::string name = line.substr(0, position);
    line.erase(0, position + 1);

    position = line.find(';');
    std::string type = line.substr(0, position);
    line.erase(0, position + 1);

    position = line.find(';');
    std::string age = line.substr(0, position);
    line.erase(0, position + 1);

    std::string animal_info = line;

    if (type == "Lion")
    {
      Animal* animal = new Lion(name, std::stoi(age), std::stoi(animal_info));
      available_animals_.push_back(animal);
    }
    else if(type == "Giraffe")
    {
      float temp = 0;
      Utils::decimalStringToFloat(animal_info, temp);
      Animal* animal = new Giraffe(name, std::stoi(age), temp);
      available_animals_.push_back(animal);
    }
    else if(type == "Gorilla")
    {
      float temp = 0;
      Utils::decimalStringToFloat(animal_info, temp);
      Animal* animal = new Gorilla(name, std::stoi(age), temp);
      available_animals_.push_back(animal);
    }
    else if(type == "Dolphin")
    {
      Animal* animal = new Dolphin(name, std::stoi(age), std::stoi(animal_info));
      available_animals_.push_back(animal);
    }
  }
  return true;
}

void Shop::buy(Animal* animal)
{
  for (auto checker = available_animals_.begin(); checker != available_animals_.end(); checker++)
  {
    if ((*checker)->getName() == animal->getName())
    {
      available_animals_.erase(checker);
      break;
    }
  }
}

Animal* Shop::getAnimal(std::string name)
{
  name[0] = toupper(name[0]);
  for (auto letter = 1; letter < name.length(); letter++)
  {
    name[letter] = tolower(name[letter]);
  }
  
  for (auto animal : available_animals_)
  {
    if (name == animal->getName())
    {
      return animal;
    }
  }
  return nullptr;
}

void Shop::printInfo()
{
  std::cout << "Welcome to the \"" << name_ << "\"!" << std::endl << std::endl;
  std::cout << "The following are our prices for the given enclosure types per field:" << std::endl;
  std::cout << "- Savanna:   1000 coins" << std::endl;
  std::cout << "- Forest:  3000 coins" << std::endl;
  std::cout << "- Aquarium: 10000 coins" << std::endl << std::endl;
  std::cout << "We have the following animals for sale:" << std::endl;
  for (auto animal : available_animals_)
  {
    if (animal->getType() == AnimalType::Lion)
    {
      std::cout << "- Lion \"" << animal->getName() << "\": " << animal->getPrice() << " coins" << std::endl;
    }
    else if (animal->getType() == AnimalType::Giraffe)
    {
      std::cout << "- Giraffe \"" << animal->getName() << "\": " << animal->getPrice() << " coins" << std::endl;
    }
    else if (animal->getType() == AnimalType::Gorilla)
    {
      std::cout << "- Gorilla \"" << animal->getName() << "\": " << animal->getPrice() << " coins" << std::endl;
    }
    else if (animal->getType() == AnimalType::Dolphin)
    {
      std::cout << "- Dolphin \"" << animal->getName() << "\": " << animal->getPrice() << " coins" << std::endl;
    }
  }
}

int Shop::getEnclosurePrice(std::string type)
{
  if (type == "savanna")
    return 1000;
  else if (type == "forest")
    return 3000;
  else if (type == "aquarium")
    return 10000;

  return 0;
}

int Shop::getAnimalPrice(std::string name)
{
  for (auto& animal : available_animals_)
  {
    if (animal->getName() == name)
    {
      return animal->getPrice();
    }
  }
  return 0;
}
