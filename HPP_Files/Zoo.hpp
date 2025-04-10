#ifndef ZOO_HPP
#define ZOO_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Animal.hpp"
#include "Shop.hpp"
#include "Command.hpp"
#include "Enclosure.hpp"

#define ERROR_INVALID_PARAMS "[ERROR] Wrong number of parameters for this command!"

#define ERROR_INVALID_ENCLOSURE "[ERROR] No enclosure with given type!"
#define ERROR_ANIMAL_NOT_IN_SHOP "[ERROR] No animal with given name in the shop!"
#define ERROR_INVALID_FIELD_POSITION "[ERROR] Invalid field position!"
#define ERROR_INVALID_ENCLOSURE_SIZE "[ERROR] Invalid width or height!"
#define ERROR_NOT_ENOUGH_MONEY "[ERROR] There is not enough money!"
#define ERROR_ENCLOSURE_DOESNT_FIT "[ERROR] Enclosure does not fit!"
#define ERROR_INVALID_FIELD_POSITION_IN_ENCLOSURE "[ERROR] Field is not part of an enclosure!"
#define ERROR_MAX_ANIMAL_AMOUNT "[ERROR] There is not enough space in this enclosure!"
#define ERROR_THAT_ANIMAL_CANT_BE_HERE "[ERROR] This animal is not allowed here!"

#define TOTAL_RATING_MESSAGE "Your zoo has an overall rating of "

class Zoo
{
protected:
  std::string name_;
  Shop& shop_;
  int money_;
  int width_;
  int height_;
  bool map_active_;
  int animal_count_ = 0;
  std::vector<std::vector<Enclosure*>> enclosures_;

public:
  Zoo(std::string name, Shop& shop, int money, int width, int height);

  ~Zoo();

  void processCommand(Command command);
  void printMap();
  int numberOfAnimals();
  int numberOfFields();
  int numberOfEmptyEnclosures();
  void printAllInfo();
  bool isEnclosureOverlapping(int enclosure_column, int enclosure_row,
    int enclosure_width, int enclosure_height);
  std::string stringToLower(std::string lower_string);
  void createNewEnclosure(std::string enclosure_type, int enclosure_column,
    int enclosure_row, int enclosure_width, int enclosure_height);

  int getWidth() const;
  int getHeight() const;
  const std::vector<std::vector<Enclosure*>>& getEnclosures() const;
  void setAllVisitedToFalse();
  bool isInteger(std::string input);

  // logic for commands
  void infoWrapper(std::vector<std::string>& parameters);
  void shopWrapper(std::vector<std::string>& parameters);
  void mapWrapper(std::vector<std::string>& parameters);
  void buildWrapper(std::vector<std::string>& parameters);
  void buyWrapper(std::vector<std::string>& parameters);
  void rateWrapper(std::vector<std::string>& parameters);
};

#endif
