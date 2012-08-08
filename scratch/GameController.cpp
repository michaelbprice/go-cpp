#include "GameController.hpp"

namespace Go
{

GameController::GameController (unique_ptr<IPlayer> one, unique_ptr<IPlayer> two)
  : m_playerOne(one)
  , m_playerTwo(two)
  // , m_blackStones(181, Stone::Color::BLACK)
  // , m_whiteStones(180, Stone::Color::WHITE)
{ }

void GameController::playAnother ()
{
	//assert(m_shouldPlayAnother = false);
	m_shouldPlayAnother = true;
}

bool GameController::shouldPlayAnother ()
{
	return m_shouldPlayAnother;
}

void GameController::start ()
{

}

void GameController::stop ()
{

}

void GameController::waitForStop ()
{

}

}