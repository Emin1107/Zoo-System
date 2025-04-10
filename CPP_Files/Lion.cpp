#include <iostream>
#include <string>

#include "Lion.hpp"
#include "Animal.hpp"

Lion::Lion(std::string name, int age, int mane_length) :
  Animal(name, age), mane_length_{ mane_length } {}

Lion::~Lion() {}

AnimalType Lion::getType() { return AnimalType::Lion;}

std::string Lion::getDisplayString() { return "Lion"; }

void Lion::printInformation() {
  std::cout << "- Lion \"" << getName() << "\" of age " << getAge() <<
    ": Mane length is " << mane_length_ << " cm!" << std::endl;
}

int Lion::getPrice() { return (5000 + (mane_length_ * 100)); }
