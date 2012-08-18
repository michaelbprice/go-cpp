#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include <string>
#include <utility>
#include "IPlayer.hpp"
#include "Board.fwd.hpp"
#include "Stone.fwd.hpp"

namespace Go {

template <typename TyPlayerUI>	
class Player final : public IPlayer
{
 private:
    std::string m_name;

    Board * m_pBoard = nullptr; // Non-owning pointer... do NOT delete!

    Stones m_stones;
    StoneColor m_stoneColor = StoneColor::NONE;
    size_t m_capturedCount = 0;
 	
    TyPlayerUI m_ui;

 public:
    Player () = delete;
    Player (const Player &) = delete;
    Player & operator= (const Player &) = delete;

    ~Player () = default;
    Player (Player &&) = default;
    Player & operator= (Player &&) = default;

    Player (const std::string & name);

    virtual void addToCaptured (size_t numCaptured) override;
    virtual void chooseName () override;
    virtual StoneColor chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::string & getName () const override;
    virtual bool hasStones () const override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (StoneColor color) override;
    virtual StoneColor getStoneColor () override;
    virtual std::pair<size_t, size_t> playStone () override;
    virtual void onGameReady () override;
    virtual void onTurn () override;

    virtual size_t calculateScore () override;
    virtual void lost () override;
    virtual void won () override;
    virtual void tied () override;
};

} // namespace Go

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
