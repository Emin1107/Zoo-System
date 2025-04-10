#include <iostream>
#include <string>
#include <vector>

#include "Zoo.hpp"
#include "Animal.hpp"

#include "Utils.hpp"

#include "Shop.hpp"
#include "Enclosure.hpp"
#include "Savanna.hpp"
#include "Forest.hpp"
#include "Aquarium.hpp"
#include "Command.hpp"
#include "Lion.hpp"

Zoo::Zoo(std::string name, Shop& shop, int money, int width, int height) : 
  name_(name), shop_(shop), money_(money), width_(width), height_(height), map_active_(true)
{
  std::cout << std::endl;
  std::cout << "Welcome to your Zoo \"" << name_ << "\"!" << std::endl;
  std::cout << "This zoo has a size of " << width_ << " x " << height_ << "!" << std::endl;

  enclosures_.resize(height_);
  for (unsigned long row = 0; row < enclosures_.size(); row++)
  {
    enclosures_[row].resize(width_);
    for (unsigned long column = 0; column < enclosures_[row].size(); column++)
    {
      enclosures_[row][column] = nullptr;
    }
  }

  printMap();
}

Zoo::~Zoo()
{
  std::vector<Enclosure*> check_deleted;

  for (auto& row : enclosures_)
  {
    for (auto& enclosure : row)
    {
      if (enclosure != nullptr)
      {
        bool is_deleted = false;

        for (auto& check : check_deleted)
        {
          if (check == enclosure)
          {
            is_deleted = true;
            break;
          }
        }

        if (!is_deleted)
        {
          check_deleted.push_back(enclosure);
          delete enclosure;
        }
      }
    }
  }
}

void Zoo::printMap()
{
  std::cout << std::endl;
  std::cout << "  ";
  for (int column = 0; column < width_; column++)
  {
    std::cout << "  " << (column + 1) << " ";
  }
  std::cout << " ";
  std::cout << std::endl;

  std::cout << "  +";

  for (int column = 0; column < width_; column++)
  {
    std::cout << "---+";
  }
  std::cout << std::endl;

  for (int row = 0; row < height_; row++)
  {
    std::cout << (row + 1) << " |";
    for (int column = 0; column < width_; column++)
    {
      auto& enclosure = enclosures_[row][column];

      std::string field = "   ";
      if (enclosure != nullptr)
      {
        field = enclosure->getFieldString();
      }
      std::cout << field;

      bool does_it_have_wall = false;
      auto& left_wall = enclosures_.at(row).at(column);
      try
      {
        auto& right_wall = enclosures_.at(row).at(column + 1);
        does_it_have_wall = (left_wall == right_wall) ? false : true;
      }
      catch (...)
      {
        does_it_have_wall = true;
      }
      if (!does_it_have_wall)
        std::cout << " ";
      else
        std::cout << "|";
    }

    std::cout << std::endl;
    std::cout << "  +";
    for (int column = 0; column < width_; column++)
    {
      bool does_it_have_fence = false;
      auto& high = enclosures_.at(row).at(column);
      try
      {
        auto& low = enclosures_.at(row + 1).at(column);
        does_it_have_fence = (high == low) ? false : true;
      }
      catch (...)
      {
        does_it_have_fence = true;
      }
      if (!does_it_have_fence)
        std::cout << "   ";
      else
        std::cout << "---";

      std::cout << "+";
    }
    std::cout << std::endl;
  }

  for (auto& row : enclosures_)
  {
    for (auto& enclosure : row)
    {
      if (enclosure != nullptr)
      {
        enclosure->resetMapAnimal();
      }
    }
  }
}

void Zoo::processCommand(Command command)
{
  if (command.getType() == CommandType::INFO)
  {
    auto& parameters = command.getParameters();
    infoWrapper(parameters);
  }
  else if (command.getType() == CommandType::SHOP)
  {
    auto& parameters = command.getParameters();
    shopWrapper(parameters);
  }
  else if (command.getType() == CommandType::MAP)
  {
    auto& parameters = command.getParameters();
    mapWrapper(parameters);
    if (map_active_) { printMap(); }
  }
  else if (command.getType() == CommandType::BUILD)
  {
    auto& parameters = command.getParameters();
    buildWrapper(parameters);
  }
  else if (command.getType() == CommandType::BUY)
  {
    auto& parameters = command.getParameters();
    buyWrapper(parameters);
  }
  else if (command.getType() == CommandType::RATE)
  {
    auto& parameters = command.getParameters();
    rateWrapper(parameters);
  }
}

void Zoo::printAllInfo()
{
  std::cout << "Zoo Name: " << name_ << std::endl;
  std::cout << "Money: " << money_ << " coin(s)" << std::endl;
  std::cout << "Number of Animals: " << numberOfAnimals() << std::endl;
  std::cout << "Empty fields: " << numberOfFields() << std::endl;
  std::cout << "Empty enclosures: " << numberOfEmptyEnclosures() << std::endl;
}

int Zoo::numberOfAnimals()
{
  return animal_count_;
}

int Zoo::numberOfFields()
{
  int number = 0;
  for (auto& row : enclosures_)
  {
    for (auto* enclosure : row)
    {
      if (enclosure == nullptr)
      {
        number++;
      }
    }
  }

  return number;
}

int Zoo::numberOfEmptyEnclosures()
{
  int number = 0;
  for (auto& row : enclosures_)
  {
    for (auto* enclosure : row)
    {
      if (enclosure != nullptr && enclosure->getAnimalNumber() == 0 &&
          !enclosure->wasVisited())
      {
        enclosure->setVisitedToTrue();
        number++;
      }
    }
  }

  setAllVisitedToFalse();
  return number;
}

bool Zoo::isEnclosureOverlapping(int enclosure_column, int enclosure_row, int enclosure_width, int enclosure_height)
{
  for (int row = enclosure_row; row < enclosure_row + enclosure_height; row++)
  {
    for (int column = enclosure_column; column < enclosure_column + enclosure_width; column++)
    {
      if (enclosures_[row][column] != nullptr)
      {
        return true;
      }
    }
  }
  return false;
}

std::string Zoo::stringToLower(std::string lower_string)
{
  for (unsigned long i = 0; i < lower_string.length(); i++)
  {
    lower_string[i] = tolower(lower_string[i]);
  }

  return lower_string;
}

void Zoo::createNewEnclosure(std::string enclosure_type, int enclosure_column,
  int enclosure_row, int enclosure_width, int enclosure_height)
{
  Enclosure* new_enclosure = nullptr;

  if (enclosure_type == "savanna")
  {
    new_enclosure = new Savanna(enclosure_column, enclosure_row, enclosure_width, enclosure_height);
  }
  else if (enclosure_type == "forest")
  {
    new_enclosure = new Forest(enclosure_column, enclosure_row, enclosure_width, enclosure_height);
  }
  else if (enclosure_type == "aquarium")
  {
    new_enclosure = new Aquarium(enclosure_column, enclosure_row, enclosure_width, enclosure_height);
  }

  if (new_enclosure != nullptr)
  {
    for (int row = enclosure_row; row < enclosure_row + enclosure_height; row++)
    {
      for (int column = enclosure_column; column < enclosure_column + enclosure_width; column++)
      {
        enclosures_[row][column] = new_enclosure;
      }
    }
  }
}

int Zoo::getWidth() const { return width_; }

int Zoo::getHeight() const { return height_; }

const std::vector<std::vector<Enclosure*>>& Zoo::getEnclosures() const { return enclosures_; }

void Zoo::setAllVisitedToFalse()
{
  for (auto& row : enclosures_)
  {
    for (auto& enclosure : row)
    {
      if (enclosure != nullptr)
      {
        enclosure->setVisitedToFalse();
      }
    }
  }
}

void Zoo::infoWrapper(std::vector<std::string>& parameters)
{
  if (parameters.empty())
  {
    printAllInfo();
  }
  else if (parameters.size() == 2)
  {
    if (!isInteger(parameters[0]) || !isInteger(parameters[1]))
    {
      std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
      return;
    }

    int field_column = 0;
    int field_row = 0;
    Utils::decimalStringToInt(parameters[0], field_column);
    Utils::decimalStringToInt(parameters[1], field_row);
    --field_column;
    --field_row;

    if (field_column < 0 || field_column >= width_ ||
      field_row < 0 || field_row >= height_)
    {
      std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
      return;
    }
    else if (enclosures_[field_row][field_column] == nullptr)
    {
      std::cout << ERROR_INVALID_FIELD_POSITION_IN_ENCLOSURE << std::endl;
      return;
    }

    std::cout << "Enclosure: " << enclosures_[field_row][field_column]->getDisplayString() << std::endl;
    std::cout << "List of inhabitants:" << std::endl;
    enclosures_[field_row][field_column]->printAnimals();
  }
  else
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }
}

void Zoo::shopWrapper(std::vector<std::string>& parameters)
{
  if (parameters.empty())
  {
    shop_.printInfo();
  }
  else
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }
}

void Zoo::mapWrapper(std::vector<std::string>& parameters)
{
  if (parameters.empty())
  {
    if (map_active_)
    {
      map_active_ = false;
    }
    else
    {
      map_active_ = true;
    }
  }
  else
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }
}

void Zoo::buildWrapper(std::vector<std::string>& parameters)
{
  if (parameters.size() != 5)
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }

  std::string enclosure_type = stringToLower(parameters[0]);
  if (enclosure_type != "savanna" && enclosure_type != "forest" && enclosure_type != "aquarium")
  {
    std::cout << ERROR_INVALID_ENCLOSURE << std::endl;
    return;
  }

  if (!isInteger(parameters[1]) || !isInteger(parameters[2]))
  {
    std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
    return;
  }

  int enclosure_column = 0;
  int enclosure_row = 0;
  Utils::decimalStringToInt(parameters[1], enclosure_column);
  Utils::decimalStringToInt(parameters[2], enclosure_row);
  --enclosure_column;
  --enclosure_row;

  if (enclosure_column < 0 || enclosure_column >= width_ ||
        enclosure_row < 0 || enclosure_row >= height_)
  {
    std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
    return;
  }

  if (!isInteger(parameters[3]) || !isInteger(parameters[4]))
  {
  std::cout << ERROR_INVALID_ENCLOSURE_SIZE << std::endl;
  return;
  }

  int enclosure_width = 0;
  int enclosure_height = 0;
  Utils::decimalStringToInt(parameters[3], enclosure_width);
  Utils::decimalStringToInt(parameters[4], enclosure_height);

  int potential_price = ((enclosure_width * enclosure_height) * shop_.getEnclosurePrice(enclosure_type));
  
  if (money_ < potential_price)
  {
    std::cout << ERROR_NOT_ENOUGH_MONEY << std::endl;
    return;
  }
  else if (enclosure_column + enclosure_width > width_ ||
        enclosure_row + enclosure_height > height_)
  {
    std::cout << ERROR_ENCLOSURE_DOESNT_FIT << std::endl;
    return;
  }
  else if (isEnclosureOverlapping(enclosure_column, enclosure_row, enclosure_width, enclosure_height))
  {
    std::cout << ERROR_ENCLOSURE_DOESNT_FIT << std::endl;
    return;
  }
  else if (enclosure_width > width_ || enclosure_height > height_ || 
          enclosure_width <= 0 || enclosure_height <= 0)
  {
    std::cout << ERROR_INVALID_ENCLOSURE_SIZE << std::endl;
    return;
  }

  money_ -= potential_price;
  createNewEnclosure(enclosure_type, enclosure_column, enclosure_row, enclosure_width, enclosure_height);

  if (map_active_) { printMap(); }
}

void Zoo::buyWrapper(std::vector<std::string>& parameters)
{
  if (parameters.size() != 3)
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }

  std::string animal_name = stringToLower(parameters[0]);
  animal_name[0] = toupper(animal_name[0]);

  Animal* animal = shop_.getAnimal(animal_name);
  if (animal == nullptr)
  {
    std::cout << ERROR_ANIMAL_NOT_IN_SHOP << std::endl;
    return;
  }

  if (!isInteger(parameters[1]) || !isInteger(parameters[2]))
  {
    std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
    return;
  }

  int enclosure_column = 0;
  int enclosure_row = 0;
  Utils::decimalStringToInt(parameters[1], enclosure_column);
  Utils::decimalStringToInt(parameters[2], enclosure_row);
  --enclosure_column;
  --enclosure_row;

  int potential_price = shop_.getAnimalPrice(animal_name);

  if (enclosure_column < 0 || enclosure_column >= width_ ||
    enclosure_row < 0 || enclosure_row >= height_)
  {
    std::cout << ERROR_INVALID_FIELD_POSITION << std::endl;
    return;
  }
  else if (enclosures_[enclosure_row][enclosure_column] == nullptr)
  {
    std::cout << ERROR_INVALID_FIELD_POSITION_IN_ENCLOSURE << std::endl;
    return;
  }
  else if (money_ < potential_price)
  {
    std::cout << ERROR_NOT_ENOUGH_MONEY << std::endl;
    return;
  }
  else if (!enclosures_[enclosure_row][enclosure_column]->hasRoom())
  {
    std::cout << ERROR_MAX_ANIMAL_AMOUNT << std::endl;
    return;
  }
  else if (!enclosures_[enclosure_row][enclosure_column]->isAnimalAllowed(animal->getType()))
  {
    std::cout << ERROR_THAT_ANIMAL_CANT_BE_HERE << std::endl;
    return;
  }

  money_ -= potential_price;
  animal_count_++;
  shop_.buy(animal);
  enclosures_[enclosure_row][enclosure_column]->addAnimal(animal);
  if (map_active_) { printMap(); }
}

void Zoo::rateWrapper(std::vector<std::string>& parameters)
{
  if (parameters.size() != 0)
  {
    std::cout << ERROR_INVALID_PARAMS << std::endl;
    return;
  }

  setAllVisitedToFalse();
  int final_rating = 0;

  std::cout << "Individual ratings of enclosures:" << std::endl;
  for (int row = 0; row < height_; row++)
  {
    for (int column = 0; column < width_; column++)
    {
      auto& enclosure = enclosures_[row][column];
      if (enclosure != nullptr && !enclosure->wasVisited())
      {
        enclosure->setVisitedToTrue();

        int rating_of_enclosure = enclosure->calculateRating(*this);
        final_rating += rating_of_enclosure;

        std::cout << "- " << enclosure->getDisplayString() << " (" << (column + 1) << "/" <<
          (row + 1) << "): " << rating_of_enclosure << std::endl;
      }
    }
  }
  std::cout << TOTAL_RATING_MESSAGE << final_rating << "!" << std::endl;

  setAllVisitedToFalse();

  if (map_active_) { printMap(); }
}

bool Zoo::isInteger(std::string input)
{
  for (auto& letter : input)
  {
    if (!isdigit(letter))
    {
      return false;
    }
  }
  return true;
}
