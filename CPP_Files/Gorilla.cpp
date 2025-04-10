#include <iostream>
#include <string>
#include <iomanip> // std::fixed, std::setprecision 
#include <cmath> // std::abs

#include "Gorilla.hpp"
#include "Animal.hpp"

Gorilla::Gorilla(std::string name, int age, float weight) :
  Animal(name, age), weight_{ weight } {}

Gorilla::~Gorilla() {}

AnimalType Gorilla::getType() { return AnimalType::Gorilla; }

std::string Gorilla::getDisplayString() { return "Gorilla"; }

void Gorilla::printInformation() {
  std::cout << "- Gorilla \"" << getName() << "\" of age " << getAge() <<
    ": Weight is " << std::fixed << std::setprecision(2)
    << weight_ << " kg!" << std::endl;
}

int Gorilla::getPrice() { return (2000 - std::abs(150 - weight_)); }
