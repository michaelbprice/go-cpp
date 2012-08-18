#ifndef INCL_IPLAYER_HPP__
#define INCL_IPLAYER_HPP__

#include <utility>
#include <string>

#include "Stone.fwd.hpp"

namespace Go {

class IPlayer
{
 public:

    virtual void addToCaptured (size_t numCaptured) = 0;
    virtual void chooseName () = 0;
    virtual StoneColor chooseStoneColor () = 0;
    virtual const Board & getGameBoard () const = 0;
    virtual const std::string & getName () const = 0;
    virtual bool hasStones () const = 0;
    virtual void setGameBoard (Board & board) = 0;
    virtual void setStoneColor (StoneColor color) = 0;
    virtual StoneColor getStoneColor () = 0;

    virtual size_t calculateScore () = 0;
    virtual void lost () = 0;
    virtual void won () = 0;
    virtual void tied () = 0;

    virtual std::pair<size_t, size_t> playStone () = 0;

    virtual void onGameReady () = 0;
    virtual void onTurn () = 0;
};

} // namespace Go

#endif /* end of include guard: INCL_IPLAYER_HPP__ */
