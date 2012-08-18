#ifndef INCL_CONSOLEUI_HPP__
#define INCL_CONSOLEUI_HPP__

#include <string>
#include <utility>

#include "Player.fwd.hpp"
#include "Stone.fwd.hpp"

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

    void onInvalidMove(const std::pair<size_t, size_t> & invalidMove);
    void onWin ();
    void onLoss ();
    void onTie ();

    std::pair<size_t, size_t> promptForMove ();
    std::string promptForName ();
    StoneColor promptForStoneColor ();
    void updateGameState ();
};

}

#endif /* end of include guard: INCL_CONSOLEUI_HPP__ */
