#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include "Board.hpp"
#include "Chain.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Stone.hpp"

using namespace std;

namespace Go
{

template <typename TyPlayerUI>
Player<TyPlayerUI>::Player (const string & name)
  : m_ui(*this)
  , m_name(name)
{
    LOG_FUNCTION(cout, __func__);
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::addToCaptured (size_t numCaptured)
{
    LOG_FUNCTION(cout, "Player::addToCaptured");

    m_capturedCount += numCaptured;
}

template <typename TyPlayerUI>
size_t Player<TyPlayerUI>::calculateScore () const
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
StoneColor Player<TyPlayerUI>::getStoneColor ()
{
    LOG_FUNCTION(cout, "Player::getStoneColor");

    return m_stoneColor;
}

template <typename TyPlayerUI>
bool Player<TyPlayerUI>::hasStones () const
{
    LOG_FUNCTION(cout, "Player::hasStones");

    return !m_stones.empty();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyGameReady ()
{
    LOG_FUNCTION(cout, "Player::notifyGameReady");

    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyLost ()
{
    LOG_FUNCTION(cout, "Player::notifyLost");

    m_ui.onLoss();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyTied ()
{
    LOG_FUNCTION(cout, "Player::notifyTied");

    m_ui.onTie();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyTurn ()
{
    LOG_FUNCTION(cout, "Player::notifyTurn");

    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyWon ()
{
    LOG_FUNCTION(cout, "Player::notifyWon");

    m_ui.onWin();
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
        m_stones.emplace_back(std::make_unique<Stone>(m_stoneColor));
}

template <typename TyPlayerUI>
PointCoords Player<TyPlayerUI>::playStone ()
{
    LOG_FUNCTION(cout, "Player::playStone");

    assert(m_pBoard != nullptr);

    gLogger.log(LogLevel::kMedium, cout, "About to prompt for move input");
    auto theMove = m_ui.promptForMove();

    while (!m_pBoard->isValidMove(m_stones.back()->getColor(), theMove))
    {
        gLogger.log(LogLevel::kMedium, cout, "Invalid move");
        m_ui.onInvalidMove(theMove);
        theMove = m_ui.promptForMove();
    }

    m_pBoard->placeStoneAt(theMove, move(m_stones.back()));
    m_stones.pop_back();

    return theMove;
}

}
