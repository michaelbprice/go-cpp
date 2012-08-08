#ifndef INCL_GAMECONTROLLER_HPP__
#define INCL_GAMECONTROLLER_HPP__

#include "Board.hpp"
//#include "Point.hpp"
//#include "Stone.hpp"
#include "Player.hpp"

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class unique_ptr
{
};

///////////////////////////////////////////////////////////////////////////////

namespace Go
{

class GameController final
{
 private:
    bool m_shouldPlayAnother = false;

    Board m_board;
    unique_ptr<IPlayer> m_playerOne;
    unique_ptr<IPlayer> m_playerTwo;
    // Stones m_blackStones;
    // Stones m_whiteStones;

 public:
 	GameController (unique_ptr<IPlayer> one, unique_ptr<IPlayer> two);

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