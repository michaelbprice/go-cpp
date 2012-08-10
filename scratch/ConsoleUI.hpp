#ifndef INCL_CONSOLEUI_HPP__
#define INCL_CONSOLEUI_HPP__

#include "Player.hpp"
#include "Stone.hpp"
#include <string>

namespace Go
{
	
class ConsoleUI
{
 private:
    const IPlayer & m_player;
    short m_updateCount = 0;

 public:
    ConsoleUI () = delete;
    ConsoleUI (const ConsoleUI &) = delete;
    ConsoleUI & operator= (const ConsoleUI &) = delete;

    ~ConsoleUI () = default;
    ConsoleUI (ConsoleUI &&) = default;
    ConsoleUI & operator= (ConsoleUI &&) = default;

    ConsoleUI (const IPlayer & player);

    std::pair<size_t, size_t> promptForMove ();
    std::string promptForName ();
    Stone::Color promptForStoneColor ();
    void updateGameState ();
};

}

#endif /* end of include guard: INCL_CONSOLEUI_HPP__ */
