#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>

#include "GameController.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Stone.hpp"

using namespace std;

// ***************** PRIVATE HELPER FUNCTIONS *****************

bool didPlayerPass (const pair<size_t, size_t> & move)
{
    return move.first >= 19 || move.second >= 19;
}

// *************** END PRIVATE HELPER FUNCTIONS ***************

namespace Go {


GameController::GameController (IPlayer & one, IPlayer & two)
  : m_playerOne(one)
  , m_playerTwo(two)
{
    LOGFUNCTION(cout, "GameController::GameController");

    m_playerOne.setGameBoard(m_board);
    m_playerTwo.setGameBoard(m_board);
}

void GameController::doGameLoop (PlayerPair & playerPair)
{
    LOGFUNCTION(cout, "GameController::doGameLoop");

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
        currentPlayer.onTurn();

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
    LOGFUNCTION(cout, "GameController::doScoring");

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

void GameController::start ()
{
    LOGFUNCTION(cout, "GameController::start");

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

    Stone::Color colorOne = m_playerOne.chooseStoneColor();
    m_playerTwo.setStoneColor(getOpposingColor(colorOne));


    // Reorder the players according to the stone choices
    //
    if (Stone::Color::WHITE == colorOne)
        swap(playerPair.first, playerPair.second);


    // Signal to the players that the game is ready
    //
    playerPair.first.get().onGameReady();
    playerPair.second.get().onGameReady();


    // Start the move selection loop
    //
    doGameLoop(playerPair);
    

    // Game is over! Time to score
    //
    doScoring();
}

void GameController::stop ()
{
    LOGFUNCTION(cout, "GameController::stop");

}

void GameController::waitForStop ()
{
    LOGFUNCTION(cout, "GameController::waitForStop");

}

} // namespace Go

