#include "Player.hpp"
#include <algorithm>

namespace Go
{

template <typename TyPlayerUI>
Player<TyPlayerUI>::Player (const std::string & name)
  : m_ui(*this)
  , m_name(name)
{

}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::chooseName ()
{
    m_name =  m_ui.promptForName();
}

template <typename TyPlayerUI>
Stone::Color Player<TyPlayerUI>::chooseStoneColor ()
{
    setStoneColor(m_ui.promptForStoneColor());

    return m_stoneColor;
}

template <typename TyPlayerUI>
const std::string & Player<TyPlayerUI>::getName () const
{
    return m_name;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setGameBoard (Board & board) const
{
    m_pBoard = &board;;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setStoneColor (Stone::Color color)
{
    m_stoneColor = color;

    if (m_stoneColor == Stone::Color::BLACK)
    {
        m_stones.reserve(181);
    }
    else
    {
        m_stones.reserve(180);
    }

    std::fill(std::begin(m_stones), std::end(m_stones), m_stoneColor);
}



template <typename TyPlayerUI>
std::pair<size_t, size_t> Player<TyPlayerUI>::playStone ()
{
    assert(m_pBoard != nullptr);

    auto move = m_ui.promptForMove();

    if (m_pBoard->isOccupiedPoint(move.first, move.second))
    {
        //m_ui.onInvalidMove(move);
        move = m_ui.promptForMove();
    }

    m_pBoard->placeStoneAt(move.first, move.second, );

    return move;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::onGameReady ()
{
    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::onTurn ()
{
    m_ui.updateGameState();
}

}
