#include <iostream>
#include "error_messages.h"

void Warning(const std::string &message)
{
    std::cout << YELLOW << "Warning: " << message << RESET << std::endl;
}

void Error(const std::string &message)
{
    std::cout << RED << "Error: " << message << RESET << std::endl;
    exit(EXIT_FAILURE);
}