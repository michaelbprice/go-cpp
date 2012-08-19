#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include <string>
#include <utility>
#include "IPlayer.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"

namespace Go {

template <typename TyPlayerUI>	
class Player final : public IPlayer
{
 private:
    TyPlayerUI m_ui;

    Board * m_pBoard = nullptr; // Non-owning pointer... do NOT delete!

    StoneColor m_stoneColor;
    std::string m_name;
    Stones m_stones;
    size_t m_capturedCount = 0;
 	
 public:
    Player (const std::string & name);
    ~Player () = default;

    Player (const Player &) = delete;
    Player & operator= (const Player &) = delete;

    Player (Player &&) = default;
    Player & operator= (Player &&) = default;

    virtual void addToCaptured (size_t numCaptured) override;
    virtual size_t calculateScore () const override;
    virtual void chooseName () override;
    virtual StoneColor chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::string & getName () const override;
    virtual StoneColor getStoneColor () override;
    virtual bool hasStones () const override;
    virtual void notifyGameReady () override;
    virtual void notifyLost () override;
    virtual void notifyTied () override;
    virtual void notifyTurn () override;
    virtual void notifyWon () override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (StoneColor color) override;
    virtual PointCoords playStone () override;
};

} // namespace Go

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
