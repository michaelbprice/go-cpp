#include "goimpl/Logger.hpp"
Go::Logger gLogger {Go::LogLevel::kNone};
std::size_t Go::FunctionLogger::nestingLevel = 1;