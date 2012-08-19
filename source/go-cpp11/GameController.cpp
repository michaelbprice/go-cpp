#include "GameController.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include "Board.hpp"
#include "IPlayer.hpp"
#include "Logger.hpp"
#include "Point.hpp"
#include "Stone.hpp"

using namespace std;

// ***************** PRIVATE HELPER FUNCTIONS *****************

bool didPlayerPass (const Go::PointCoords & move)
{
    return move.row >= Go::Board::BOARD_SIZE || move.column >= Go::Board::BOARD_SIZE;
}

// *************** END PRIVATE HELPER FUNCTIONS ***************

namespace Go {


GameController::GameController (IPlayer & one, IPlayer & two)
  : m_playerOne(one)
  , m_playerTwo(two)
{
    LOG_FUNCTION(cout, "GameController::GameController");

    m_playerOne.setGameBoard(m_board);
    m_playerTwo.setGameBoard(m_board);
}

void GameController::doGameLoop (PlayerPair & playerPair)
{
    LOG_FUNCTION(cout, "GameController::doGameLoop");

    // Counter used to determine the number of consecutive "pass" moves
    //
    unsigned short passCount = 0;


    // While there haven't been two consecutive passes, continue prompting
    // players for moves, execute the moves, and alternate players
    //
    while (passCount < 2)
    {
        IPlayer & currentPlayer = playerPair.first;
        IPlayer & waitingPlayer = playerPair.second;

        // Notify the current player that it is their turn
        //
        currentPlayer.notifyTurn();

        // If the player has stones left, have the current player make
        // a move; otherwise count as a pass
        //
        if (currentPlayer.hasStones())
        {
            // Make move
            //
            auto theMove = currentPlayer.playStone();

            // Remove captured stones and count them
            //
            size_t captureCount = m_board.removeCapturedStones(waitingPlayer.getStoneColor());

            // Add captured stones to current player's total (for scoring purposes)
            //
            currentPlayer.addToCaptured(captureCount);

            gLogger.log(LogLevel::kNone, cout, "Player ", currentPlayer.getName(),
                                               " captured ", captureCount, " stones");

            passCount = (didPlayerPass(theMove)) ? passCount + 1 : 0;
        }
        else
        {
            ++passCount;
        }

        // Swap the players so that on the next iteration, the current
        // player alternates
        //
        swap(playerPair.first, playerPair.second);
    }
}

void GameController::doScoring ()
{
    LOG_FUNCTION(cout, "GameController::doScoring");

    // Calculate scores
    //
    size_t playerOneScore = m_playerOne.calculateScore();
    size_t playerTwoScore = m_playerTwo.calculateScore();

    // Determine winner and notify players
    //
    if (playerOneScore == playerTwoScore)
    {
        m_playerOne.notifyTied();
        m_playerTwo.notifyTied();
    } 
    else if (playerOneScore > playerTwoScore)
    {
        m_playerOne.notifyWon();
        m_playerTwo.notifyLost();
    }
    else // (playerTwoScore > playerOneScore)
    {
        m_playerTwo.notifyWon();
        m_playerOne.notifyLost();
    }
}

void GameController::start ()
{
    LOG_FUNCTION(cout, "GameController::start");

    // Place the players into a 'flippable' container
    //
    PlayerPair playerPair = make_pair(ref(m_playerOne), ref(m_playerTwo));


    // Let the players enter their own names
    //
    gLogger.log(LogLevel::kMedium, cout, "Players choosing names");

    m_playerOne.chooseName();
    m_playerTwo.chooseName();


    // Assign stones, Player 1 gets to choose, Player 2 gets the remainder
    //
    gLogger.log(LogLevel::kMedium, cout, "Player 1 picking color");

    StoneColor colorOne = m_playerOne.chooseStoneColor();
    m_playerTwo.setStoneColor(getOpposingColor(colorOne));


    // Reorder the players according to the stone choices
    //
    if (StoneColor::WHITE == colorOne)
        swap(playerPair.first, playerPair.second);


    // Signal to the players that the game is ready
    //
    playerPair.first.get().notifyGameReady();
    playerPair.second.get().notifyGameReady();


    // Start the move selection loop
    //
    doGameLoop(playerPair);
    

    // Game is over! Time to score
    //
    doScoring();
}

} // namespace Go

