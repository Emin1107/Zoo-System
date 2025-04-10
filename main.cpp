#include <iostream>
#include "Zoo.hpp"
#include "Shop.hpp"
#include "Utils.hpp"
#include "CommandLine.hpp"
#include "Command.hpp"
#include "Enclosure.hpp"

enum ReturnValues
{
  SUCCESSFUL = 0,
  WRONG_NUMBER_OF_PARAMETERS = 1,
  INVALID_FILE = 2,
  INVALID_MONEY_AMOUNT = 3,
  INVALID_DIMENSIONS = 4,
  
};

//----------------------------------------------------------------------------------------------------------------------
// The main program. Controls the application on a high level view.
// Creates the game and a command line interface, handles the user input and execution of commands.
//
//
// @param argc, argument count, has to be exactly 5
// @param argv, argument vector, contains the name of the zoo, the path to the csv-file, the amount of start money, the width and the
//         height of the zoo
// @return 0 (SUCCESSFUL), if the application was closed without errors
//         a non-zero number is returned in the case of failure
//
int main(int argc, char* argv[])
{
  if (argc != 6)
  {
    std::cout << "[ERROR] Wrong number of parameters!" << std::endl;
    return WRONG_NUMBER_OF_PARAMETERS;
  }

  Shop shop;
  if (!shop.tryLoadConfig(argv[2]))
  {
    std::cout << "[ERROR] Invalid file!" << std::endl;
    return INVALID_FILE;
  }

  int money = 0;
  int width = 0;
  int height = 0;
  if (!Utils::decimalStringToInt(argv[3], money))
  {
    std::cout << "[ERROR] Invalid amount of starting money!" << std::endl;
    return INVALID_MONEY_AMOUNT;
  }
    
  if (!Utils::decimalStringToInt(argv[4], width) || !Utils::decimalStringToInt(argv[5], height))
  {
    std::cout << "[ERROR] Invalid zoo dimensions!" << std::endl;
    return INVALID_DIMENSIONS;
  }
    
  if (width <= 0 || width >= 10 || height <= 0 || height >= 10)
  {
    std::cout << "[ERROR] Invalid zoo dimensions!" << std::endl;
    return INVALID_DIMENSIONS;
  }
  
  Zoo zoo(argv[1], shop, money, width, height);

  CommandLine cli;
  while (true)
  {
    Command command = cli.readCommand();
    if (command.isQuit())
      break;
    zoo.processCommand(command);
  }

  return SUCCESSFUL;
}
