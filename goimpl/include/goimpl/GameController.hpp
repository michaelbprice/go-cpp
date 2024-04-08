#ifndef INCL_GAMECONTROLLER_HPP__
#define INCL_GAMECONTROLLER_HPP__

#include "goimpl/Board.hpp"

#include "goimpl/Player.fwd.hpp"

namespace Go {

class GameController final
{
 private:
    Board m_board;
    IPlayer & m_playerOne;
    IPlayer & m_playerTwo;

 public:
    GameController (IPlayer & one, IPlayer & two);

    void start ();

 private:

    void doGameLoop (PlayerPair & playerPair);
    void doScoring ();
};

} // namespace Go

#endif /* end of include guard: INCL_GAMECONTROLLER_HPP__ */

