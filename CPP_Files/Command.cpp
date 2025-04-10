#include <iostream>
#include <string>
#include <vector>

#include "Command.hpp"
#include "Utils.hpp"
#include "CommandLine.hpp"

Command::Command(std::vector<std::string>& input)
{
  std::string command_check = input[0];

  for (auto& letter : command_check)
  {
    letter = toupper(letter);
  }

  if (command_check == "SHOP")
    type_ = CommandType::SHOP;
  else if (command_check == "INFO")
    type_ = CommandType::INFO;
  else if (command_check == "MAP")
    type_ = CommandType::MAP;
  else if (command_check == "BUILD")
    type_ = CommandType::BUILD;
  else if (command_check == "BUY")
    type_ = CommandType::BUY;
  else if (command_check == "QUIT")
    type_ = CommandType::QUIT;
  else if (command_check == "RATE")
    type_ = CommandType::RATE;
  else
  {
    type_ = CommandType::INVALID;
    return;
  }

  if (input.size() > 1)
  {
    for (size_t i = 1; i < input.size(); i++)
    {
      parameters_.push_back(input[i]);
    }
  }
}

Command::Command(CommandType type) : type_(type) {};

bool Command::isQuit() const { return type_ == CommandType::QUIT; }

CommandType Command::getType() const { return type_; }

std::vector<std::string>& Command::getParameters() { return parameters_; }

void Command::setType(CommandType type) { type_ = type; }
