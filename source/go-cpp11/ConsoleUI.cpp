#include "ConsoleUI.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include "Board.hpp"
#include "IPlayer.hpp"
#include "Stone.hpp"

using namespace std;

static const unsigned char kBorderTopLeftChar = '+';
static const unsigned char kBorderTopRightChar = '+';
static const unsigned char kBorderBottomLeftChar = '+';
static const unsigned char kBorderBottomRightChar = '+';
static const unsigned char kBorderTopChar = '=';
static const unsigned char kBorderRightChar = '=';
static const unsigned char kBorderBottomChar = '=';
static const unsigned char kBorderLeftChar = '=';
static const unsigned char kPointChar = '+';
static const unsigned char kPointSpacerChar = '-';

void printBoard (const Go::Board & board)
{
    using namespace Go;

    cout << "   ";
    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
        cout << " " << i;
    cout << endl;

    cout << "  " << kBorderTopLeftChar << string((9*2)+1, kBorderTopChar) << kBorderTopRightChar << endl;

    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
    {
        cout << i << " " << kBorderLeftChar;
        for (size_t j = 0; j < board.BOARD_SIZE; ++j)
        {
            cout << kPointSpacerChar;
            switch (board.getStoneColorAt({i, j}))
            {
             case StoneColor::NONE:  cout << kPointChar; break;
             case StoneColor::BLACK: cout << 'B'; break; //'○'; break;
             case StoneColor::WHITE: cout << 'W'; break; //'◙'; break;
            }
        }
        cout << kPointSpacerChar << kBorderRightChar << " " << i << endl;
    }

    cout << "  " << kBorderBottomLeftChar << string((9*2)+1, kBorderBottomChar) << kBorderBottomRightChar << endl;

    cout << "   ";
    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
        cout << " " << i;
    cout << endl;
}

namespace Go
{

ConsoleUI::ConsoleUI (const IPlayer & player)
  : m_player(player)
{ }

void ConsoleUI::onInvalidMove (const PointCoords & invalidMove)
{
    cout << "Invalid move [" << invalidMove.row << "," << invalidMove.column << "]. Try again!" << endl;
}

void ConsoleUI::onTie ()
{
    cout << m_player.getName() << " tied... So close." << endl;
}

void ConsoleUI::onLoss ()
{
    cout << m_player.getName() << " loses. Sorry!" << endl;
}

void ConsoleUI::onWin ()
{
    cout << m_player.getName() << " WINS!" << endl;
}

PointCoords ConsoleUI::promptForMove ()
{
    cout << m_player.getName() << "(" << m_player.calculateScore() << "), enter move: ";

    size_t x_coord = 0;
    size_t y_coord = 0;

    cin >> x_coord >> y_coord;

    return {x_coord, y_coord};
}

string ConsoleUI::promptForName ()
{
    cout << "Name for " << m_player.getName() << ": ";

    string playerName;
    cin >> playerName;

    return playerName;
}

StoneColor ConsoleUI::promptForStoneColor ()
{
    cout << m_player.getName() << ", would you like to play as Black (0) or White (1): ";

    unsigned short choice = 0;
    cin >> choice;

    assert(choice == 0 || choice == 1);

    return (choice == 0) ? StoneColor::BLACK : StoneColor::WHITE;
}

void ConsoleUI::updateGameState ()
{
    if (m_updateCount == 0)
      cout << m_player.getName() << " is ready!" << endl;
    else
    {
      printBoard(m_player.getGameBoard());
    }

    ++m_updateCount;
}

};
