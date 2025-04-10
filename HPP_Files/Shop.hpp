#ifndef SHOP_HPP
#define SHOP_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Animal.hpp"
#include "Enclosure.hpp"

class Shop
{
protected:
  std::string name_;
  std::vector<Animal*> available_animals_;

public:
  Shop() = default;
  Shop(const Shop&) = delete;
  ~Shop() = default;

  bool tryLoadConfig(std::string path);
  void buy(Animal* animal);
  Animal* getAnimal(std::string name);
  void printInfo();
  int getEnclosurePrice(std::string type);
  int getAnimalPrice(std::string name);
};

#endif