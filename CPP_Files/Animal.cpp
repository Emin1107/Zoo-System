#include <iostream>
#include <string>

#include "Animal.hpp"

Animal::Animal(std::string name, int age) : name_{ name }, age_{ age } {}

Animal::~Animal() {}

std::string Animal::getName() const { return name_; }
int Animal::getAge() const { return age_; }

void Animal::setName(std::string name) { name_ = name; }
void Animal::setAge(int age) { age_ = age; }
