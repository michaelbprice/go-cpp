#ifndef INCL_GAMECONTROLLER_HPP__
#define INCL_GAMECONTROLLER_HPP__

#include "Board.hpp"

namespace Go {

// Forward Declarations
//
#include "Player.fwd.hpp"

class GameController final
{
 private:
    Board m_board;
    IPlayer & m_playerOne;
    IPlayer & m_playerTwo;

 public:
    GameController (IPlayer & one, IPlayer & two);

    void doGameLoop (PlayerPair & playerPair);
    void doScoring ();
    void start ();
    void stop ();
    void waitForStop ();

 private:
    void scoreGame ();
};

} // namespace Go

#endif /* end of include guard: INCL_GAMECONTROLLER_HPP__ */

