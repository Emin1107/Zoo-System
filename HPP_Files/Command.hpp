#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>

enum class CommandType
{
  SHOP,
  INFO,
  MAP,
  BUILD,
  BUY,
  QUIT,
  RATE,
  INVALID,
  WRONG_PARAM
};

class Command
{
protected:
  CommandType type_;
  std::vector<std::string> parameters_;

public:
  Command(std::vector<std::string>& input);

  Command(CommandType type);

  Command(const Command& other) = default;
  Command& operator=(const Command& other) = default;
  ~Command() = default;

  bool isQuit() const;
  CommandType getType() const;
  std::vector<std::string>& getParameters();
  void setType(CommandType type);
};

#endif