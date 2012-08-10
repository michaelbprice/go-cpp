#ifndef INCL_GAMECONTROLLER_HPP__
#define INCL_GAMECONTROLLER_HPP__

#include "Board.hpp"
//#include "Point.hpp"
//#include "Stone.hpp"
//#include "Player.hpp"


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

namespace Go
{

class IPlayer;

class GameController final
{
 private:
    bool m_shouldPlayAnother = false;

    Board m_board;
    IPlayer & m_playerOne;
    IPlayer & m_playerTwo;

 public:
    GameController (IPlayer & one, IPlayer & two);

    void playAnother ();

    bool shouldPlayAnother ();

    void start ();

    void stop ();

    void waitForStop ();

 private:
    void scoreGame ();
};

}



#endif /* end of include guard: INCL_GAMECONTROLLER_HPP__ */
