#ifndef INCL_CONSOLEUI_HPP__
#define INCL_CONSOLEUI_HPP__

#include <string>

#include "goimpl/Player.fwd.hpp"
#include "goimpl/Point.fwd.hpp"
#include "goimpl/Stone.fwd.hpp"

namespace Go
{

class ConsoleUI
{
 private:
    const IPlayer & m_player;
    short m_updateCount = 0;

 public:
    ConsoleUI (const IPlayer & player);

    void onInvalidMove(const PointCoords & invalidMove);
    void onWin ();
    void onLoss ();
    void onTie ();

    PointCoords promptForMove ();
    std::string promptForName ();
    StoneColor promptForStoneColor ();
    void updateGameState ();
};

}

#endif /* end of include guard: INCL_CONSOLEUI_HPP__ */
