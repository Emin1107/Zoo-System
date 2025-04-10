#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

enum class AnimalType {
  Lion,
  Giraffe,
  Gorilla,
  Dolphin
};

class Animal
{
protected:
  std::string name_;
  int age_;

public:
  Animal(std::string name, int age);
  virtual ~Animal();

  Animal(const Animal&) = delete;

  virtual AnimalType getType() = 0;

  virtual std::string getDisplayString() = 0;

  virtual void printInformation() = 0;

  virtual int getPrice() = 0;

  std::string getName() const;

  int getAge() const;

  void setName(std::string name);

  void setAge(int age);
};

#endif
