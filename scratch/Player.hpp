#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include "Stone.hpp"
#include <utility>
#include <string>

namespace Go
{

class Board;

class IPlayer
{
 public:

    virtual void chooseName () = 0;
    virtual Stone::Color chooseStoneColor () = 0;
    virtual const Board & getGameBoard () const = 0;
    virtual const std::string & getName () const = 0;
    virtual bool hasStones () const = 0;
    virtual void setGameBoard (Board & board) = 0;
    virtual void setStoneColor (Stone::Color color) = 0;

    virtual std::pair<size_t, size_t> playStone () = 0;

    virtual void onGameReady () = 0;
    virtual void onTurn () = 0;
};

template <typename TyPlayerUI>	
class Player final : public IPlayer
{
 private:
    std::string m_name;

    Board * m_pBoard = nullptr; // Non-owning pointer... do NOT delete!

    Stones m_stones;
    Stone::Color m_stoneColor;
 	
    TyPlayerUI m_ui;

 public:
    Player () = delete;
    Player (const Player &) = delete;
    Player & operator= (const Player &) = delete;

    ~Player () = default;
    Player (Player &&) = default;
    Player & operator= (Player &&) = default;

    Player (const std::string & name);

    virtual void chooseName () override;
    virtual Stone::Color chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::string & getName () const override;
    virtual bool hasStones () const override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (Stone::Color color) override;
    virtual std::pair<size_t, size_t> playStone () override;
    virtual void onGameReady () override;
    virtual void onTurn () override;
};

}

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
