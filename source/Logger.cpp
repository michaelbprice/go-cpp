#include "Logger.hpp"
Go::Logger gLogger {Go::LogLevel::kNone};
unsigned short Go::FunctionLogger::nestingLevel = 1;