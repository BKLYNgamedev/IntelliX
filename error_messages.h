#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#include <string>

// ANSI escape codes for colors
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";

// Function prototypes
void Warning(const std::string &message);
void Error(const std::string &message);

#endif // ERROR_MESSAGES_H