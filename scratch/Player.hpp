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

    virtual void addToCaptured (size_t numCaptured) = 0;
    virtual void chooseName () = 0;
    virtual Stone::Color chooseStoneColor () = 0;
    virtual const Board & getGameBoard () const = 0;
    virtual const std::string & getName () const = 0;
    virtual bool hasStones () const = 0;
    virtual void setGameBoard (Board & board) = 0;
    virtual void setStoneColor (Stone::Color color) = 0;
    virtual Stone::Color getStoneColor () = 0;

    virtual size_t calculateScore () = 0;
    virtual void lost () = 0;
    virtual void won () = 0;
    virtual void tied () = 0;

    virtual std::pair<size_t, size_t> playStone () = 0;

    virtual void onGameReady () = 0;
    virtual void onTurn () = 0;
};

//using PlayerPair = std::pair<std::reference_wrapper<IPlayer>, std::reference_wrapper<IPlayer>>;
#include "Player.fwd.hpp"

template <typename TyPlayerUI>	
class Player final : public IPlayer
{
 private:
    std::string m_name;

    Board * m_pBoard = nullptr; // Non-owning pointer... do NOT delete!

    Stones m_stones;
    Stone::Color m_stoneColor = Stone::Color::NONE;
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
    virtual Stone::Color chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::string & getName () const override;
    virtual bool hasStones () const override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (Stone::Color color) override;
    virtual Stone::Color getStoneColor () override;
    virtual std::pair<size_t, size_t> playStone () override;
    virtual void onGameReady () override;
    virtual void onTurn () override;

    virtual size_t calculateScore () override;
    virtual void lost () override;
    virtual void won () override;
    virtual void tied () override;

};

}

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
