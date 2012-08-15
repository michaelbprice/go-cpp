#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include <ostream>
#include <utility>

namespace Go {

enum class LogLevel : unsigned char
{
    kNone = 0,
    kLow = 1,
    kMedium = 2,
    kHigh = 3
};

class Logger
{
 private:
    LogLevel m_level = LogLevel::kNone;

 public:
    Logger (LogLevel level)
      : m_level(level)
    { }

    template <typename ... Args>
    std::ostream & log (LogLevel level, std::ostream & out, Args && ...args)
    {    
        if (level <= m_level)
        {
            out << "LOG(" << static_cast<unsigned short>(level) << "): ";
            return doLog(level, out, std::forward<Args>(args)...);
        }

        return out;
    }

 private:

    template <typename T, typename ... Args>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t, Args && ...args)
    {    
        return doLog(level, out << t, std::forward<Args>(args)...);
    }

    template <typename T>
    std::ostream & doLog (LogLevel level, std::ostream & out, T && t)
    {
       return out << t << std::endl; 
    }
};

} // namespace Go

#ifdef MAIN_CPP
Go::Logger gLogger {Go::LogLevel::kHigh};
#else
extern Go::Logger gLogger;
#endif

namespace Go {

struct FunctionLogger
{
    FunctionLogger (std::ostream & out, const char * methodName)
      : m_out{out}
      , m_name{methodName}
    {
//        m_out << std::string(' ', kIndentSpaces * nestingLevel);
        gLogger.log(LogLevel::kHigh, m_out, "Entering ", m_name);
        ++nestingLevel;
    }

    ~FunctionLogger ()
    {
        --nestingLevel;
//        m_out << std::string(' ', kIndentSpaces * nestingLevel);
        gLogger.log(LogLevel::kHigh, m_out, "Exiting ", m_name);
    }

    std::ostream & m_out;
    const char * m_name;

    static const unsigned short kIndentSpaces = 4;
    static unsigned short nestingLevel;
};

#ifdef MAIN_CPP
unsigned short FunctionLogger::nestingLevel = 0;
#endif

#define LOGFUNCTION(stream, fnname) FunctionLogger _fnLogger {stream, fnname};

} // namespace Go

#endif // __LOGGER_HPP
