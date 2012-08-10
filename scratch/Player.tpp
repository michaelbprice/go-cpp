#include "Player.hpp"
#include "Board.hpp"
#include <algorithm>
#include <cassert>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename ... Params>
std::unique_ptr<T> make_unique (Params && ... params)
{
   return std::unique_ptr<T>(new T(std::forward<Params>(params)...));
}

/////////////////////////////////////////////////////////////////////////////////////



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
const Board & Player<TyPlayerUI>::getGameBoard () const
{
    assert (m_pBoard != nullptr);

    return *m_pBoard;
}

template <typename TyPlayerUI>
const std::string & Player<TyPlayerUI>::getName () const
{
    return m_name;
}

template <typename TyPlayerUI>
bool Player<TyPlayerUI>::hasStones () const
{
    return !m_stones.empty();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setGameBoard (Board & board)
{
    assert(m_pBoard == nullptr);

    m_pBoard = &board;;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setStoneColor (Stone::Color color)
{
    m_stoneColor = color;

    size_t numberOfStones = 0;

    if (m_stoneColor == Stone::Color::BLACK)
    {
        numberOfStones = Stone::kDefaultBlackCount;
    }
    else
    {
        numberOfStones = Stone::kDefaultWhiteCount;
    }

    m_stones.reserve(numberOfStones);

/*
    std::generate_n(std::begin(m_stones), numberOfStones, [color] ()
    {
        return std::unique_ptr<Stone>{new Stone{color}};
    });
*/

//    std::fill(std::begin(m_stones), std::end(m_stones), make_unique<Stone>(m_stoneColor));

    for (size_t i = 0; i < numberOfStones; ++i)
        m_stones.emplace_back(make_unique<Stone>(m_stoneColor));
}

template <typename TyPlayerUI>
std::pair<size_t, size_t> Player<TyPlayerUI>::playStone ()
{
    assert(m_pBoard != nullptr);

    auto move = m_ui.promptForMove();

    while (m_pBoard->isOccupiedPoint(move.first, move.second))
    {
        m_ui.onInvalidMove(move);
        move = m_ui.promptForMove();
    }

    m_pBoard->placeStoneAt(move.first, move.second, std::move(m_stones.back()));
    m_stones.pop_back();

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
