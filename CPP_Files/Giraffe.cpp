#include <iostream>
#include <string>
#include <iomanip> // for std::setprecision

using std::fixed;
using std::setprecision;

#include "Giraffe.hpp"
#include "Animal.hpp"

Giraffe::Giraffe(std::string name, int age, float neck_height) :
  Animal(name, age), neck_height_{ neck_height } {}

Giraffe::~Giraffe() {}

AnimalType Giraffe::getType() { return AnimalType::Giraffe;}

std::string Giraffe::getDisplayString() { return "Giraffe"; }

void Giraffe::printInformation() {
  std::cout << "- Giraffe \"" << getName() << "\" of age " << getAge() <<
    ": Neck height is " << std::fixed << std::setprecision(2)
    << neck_height_ << " m!" << std::endl;
}

int Giraffe::getPrice() { return (4000 + (neck_height_ * 1000)); }
