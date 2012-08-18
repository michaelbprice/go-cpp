#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

#include "Board.hpp"
#include "Chain.hpp"
#include "Logger.hpp"
#include "Player.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename ... Params>
unique_ptr<T> make_unique (Params && ... params)
{
   return unique_ptr<T>(new T(forward<Params>(params)...));
}

/////////////////////////////////////////////////////////////////////////////////////


namespace Go
{

template <typename TyPlayerUI>
Player<TyPlayerUI>::Player (const string & name)
  : m_ui(*this)
  , m_name(name)
{
    LOG_FUNCTION(cout, "Player::Player");
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::addToCaptured (size_t numCaptured)
{
    LOG_FUNCTION(cout, "Player::addToCaptured");

    m_capturedCount += numCaptured;
}


template <typename TyPlayerUI>
void Player<TyPlayerUI>::chooseName ()
{
    LOG_FUNCTION(cout, "Player::chooseName");

    m_name =  m_ui.promptForName();
}

template <typename TyPlayerUI>
StoneColor Player<TyPlayerUI>::chooseStoneColor ()
{
    LOG_FUNCTION(cout, "Player::chooseStoneColor");

    setStoneColor(m_ui.promptForStoneColor());

    return m_stoneColor;
}

template <typename TyPlayerUI>
const Board & Player<TyPlayerUI>::getGameBoard () const
{
    LOG_FUNCTION(cout, "Player::getGameBoard");

    assert (m_pBoard != nullptr);

    return *m_pBoard;
}

template <typename TyPlayerUI>
const string & Player<TyPlayerUI>::getName () const
{
    LOG_FUNCTION(cout, "Player::getName");

    return m_name;
}

template <typename TyPlayerUI>
bool Player<TyPlayerUI>::hasStones () const
{
    LOG_FUNCTION(cout, "Player::hasStones");

    return !m_stones.empty();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setGameBoard (Board & board)
{
    LOG_FUNCTION(cout, "Player::setGameBoard");

    assert(m_pBoard == nullptr);

    m_pBoard = &board;;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setStoneColor (StoneColor color)
{
    LOG_FUNCTION(cout, "Player::setStoneColor");

    m_stoneColor = color;

    size_t numberOfStones = 0;

    if (m_stoneColor == StoneColor::BLACK)
    {
        numberOfStones = Stone::kDefaultBlackCount;
    }
    else
    {
        numberOfStones = Stone::kDefaultWhiteCount;
    }

    m_stones.reserve(numberOfStones);

    for (size_t i = 0; i < numberOfStones; ++i)
        m_stones.emplace_back(make_unique<Stone>(m_stoneColor));
}

template <typename TyPlayerUI>
StoneColor Player<TyPlayerUI>::getStoneColor ()
{
    LOG_FUNCTION(cout, "Player::getStoneColor");

    return m_stoneColor;
}

template <typename TyPlayerUI>
pair<size_t, size_t> Player<TyPlayerUI>::playStone ()
{
    LOG_FUNCTION(cout, "Player::playStone");

    assert(m_pBoard != nullptr);

    gLogger.log(LogLevel::kMedium, cout, "About to prompt for move input");
    auto theMove = m_ui.promptForMove();

    while (!m_pBoard->isValidMove(m_stones.back()->getColor(), theMove.first, theMove.second))
    {
        gLogger.log(LogLevel::kMedium, cout, "Invalid move");
        m_ui.onInvalidMove(theMove);
        theMove = m_ui.promptForMove();
    }

    m_pBoard->placeStoneAt(theMove.first, theMove.second, move(m_stones.back()));
    m_stones.pop_back();

    return theMove;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::onGameReady ()
{
    LOG_FUNCTION(cout, "Player::onGameReady");

    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::onTurn ()
{
    LOG_FUNCTION(cout, "Player::onTurn");

    m_ui.updateGameState();
}


template <typename TyPlayerUI>
size_t Player<TyPlayerUI>::calculateScore ()
{
    LOG_FUNCTION(cout, "Player::calculateScore");

    size_t territoryCount = 0;

    for (auto & chain : m_pBoard->getAllEmptyChains())
    {
        assert(chain.color() == StoneColor::NONE);

        StoneColor opponentColor = getOpposingColor(m_stoneColor);

        if (chain.borderCountOf(opponentColor) > 0)
            continue;

        if (chain.borderCountOf(m_stoneColor) > 0)
            territoryCount += chain.size();
    }

    return territoryCount + m_capturedCount;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::lost ()
{
    LOG_FUNCTION(cout, "Player::lost");

    m_ui.onLoss();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::tied ()
{
    LOG_FUNCTION(cout, "Player::tied");

    m_ui.onTie();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::won ()
{
    LOG_FUNCTION(cout, "Player::won");

    m_ui.onWin();
}

}
