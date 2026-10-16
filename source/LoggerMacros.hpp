#ifndef INCL_LOGGER_MACROS_HPP__
#define INCL_LOGGER_MACROS_HPP__

#define LOG_FUNCTION(stream, fnname) Go::FunctionLogger _fnLogger {Go::LogLevel::kHigh, stream, fnname};
#define LOG_BUSY_FUNCTION(stream, fnname) Go::FunctionLogger _fnLogger {Go::LogLevel::kFirehose, stream, fnname};

#endif
