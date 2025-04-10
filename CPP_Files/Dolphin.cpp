#include <iostream>
#include <string>
#include <iomanip> // std::fixed, std::setprecision 
#include <cmath> // std::abs

#include "Dolphin.hpp"
#include "Animal.hpp"

Dolphin::Dolphin(std::string name, int age, int fish_eaten_per_day) :
  Animal(name, age), fish_eaten_per_day_{ fish_eaten_per_day } {}

Dolphin::~Dolphin() {}

AnimalType Dolphin::getType() { return AnimalType::Dolphin; }

std::string Dolphin::getDisplayString() { return "Dolphin"; }

void Dolphin::printInformation() {
  std::cout << "- Dolphin \"" << getName() << "\" of age " << getAge() <<
    fish_eaten_per_day_ << " fish eaten per day!" << std::endl;
}

int Dolphin::getPrice() { return (10000 - (fish_eaten_per_day_ * 10)); }
