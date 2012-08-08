#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include "Stone.hpp"

namespace Go
{

class IPlayer
{
 public:
 	virtual void chooseStoneColor () = 0;

 	virtual void playStone () = 0;
};

template <typename TyPlayerUI>	
class Player : public IPlayer
{
 private:
 	Stones m_stones;
 	Stone::Color m_stoneColor;
 	
 	TyPlayerUI m_ui;

 public:
 	Player ();

 	virtual void chooseStoneColor () override;
 	virtual void playStone () override;
};

}

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */