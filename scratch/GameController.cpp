#include "GameController.hpp"
#include "Player.hpp"
#include "Stone.hpp"

//#include <array>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>

bool didPlayerPass (const std::pair<size_t, size_t> & move)
{
    return move.first >= 19 || move.second >= 19;
}

namespace Go
{

GameController::GameController (IPlayer & one, IPlayer & two)
  : m_playerOne(one)
  , m_playerTwo(two)
{
    m_playerOne.setGameBoard(m_board);
    m_playerTwo.setGameBoard(m_board);
}

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
    // Place the players into a 'flippable' container
    //
    //auto playerPair = std::make_pair(std::ref(m_playerOne), std::ref(m_playerTwo));
    std::pair<std::reference_wrapper<IPlayer>,std::reference_wrapper<IPlayer>> playerPair = std::make_pair(std::ref(m_playerOne), std::ref(m_playerTwo));

    // Let the players enter their own names
    //
    m_playerOne.chooseName();
    m_playerTwo.chooseName();

    // Assign stones, Player 1 gets to choose, Player 2 gets the remainder
    //
    Stone::Color colorOne = m_playerOne.chooseStoneColor();
    m_playerTwo.setStoneColor(getOpposingColor(colorOne));

    // Reorder the players according to the stone choices
    //
    if (Stone::Color::WHITE == colorOne)
        std::swap(playerPair.first, playerPair.second);

    // Signal to the players that the game is ready
    //
    playerPair.first.get().onGameReady();
    playerPair.second.get().onGameReady();


    unsigned short passCount = 0;

    while (passCount < 2)
    {
        IPlayer & currentPlayer = playerPair.first;

        currentPlayer.onTurn();

        if (currentPlayer.hasStones())
        {
            auto theMove = currentPlayer.playStone();

            currentPlayer.addToCaptured(m_board.removeCapturedStones());


            passCount = (didPlayerPass(theMove)) ? passCount + 1 : 0;
        }
        else
        {
            ++passCount;
        }

        std::swap(playerPair.first, playerPair.second);
    }

    // Game is over! Time to score
    //
    
    size_t playerOneScore = m_playerOne.calculateScore();
    size_t playerTwoScore = m_playerTwo.calculateScore();

    if (playerOneScore == playerTwoScore)
    {
        m_playerOne.tied();
        m_playerTwo.tied();
    } 
    else if (playerOneScore > playerTwoScore)
    {
        m_playerOne.won();
        m_playerTwo.lost();
    }
    else // (playerTwoScore > playerOneScore)
    {
        m_playerTwo.won();
        m_playerOne.lost();
    }
    

}

void GameController::stop ()
{

}

void GameController::waitForStop ()
{

}

}
