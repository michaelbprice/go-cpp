#include "Player.hpp"

namespace Go
{

template <typename TyPlayerUI>
Player<TyPlayerUI>::Player ()
{

}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::chooseStoneColor ()
{
	Stone::Color stoneChoice = m_ui.promptForStoneColor();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::playStone ()
{

}

}