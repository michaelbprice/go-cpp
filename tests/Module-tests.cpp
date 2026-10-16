#include <catch2/catch_test_macros.hpp>

import std;
import goimpl;

namespace {

struct TestUI
{
    TestUI (const Go::IPlayer &) { }
    void onInvalidMove (const Go::PointCoords &) { }
    void onWin () { }
    void onLoss () { }
    void onTie () { }
    Go::PointCoords promptForMove () { return {0, 0}; }
    std::string promptForName () { return "Module player"; }
    Go::StoneColor promptForStoneColor () { return Go::StoneColor::BLACK; }
    void updateGameState () { }
};

}

TEST_CASE("Module consumers can use board chains and callbacks", "[modules]")
{
    Go::Board board;
    auto chains = board.getAllEmptyChains();

    REQUIRE(chains.size() == 1);
    REQUIRE(!chains.front().color().has_value());
    REQUIRE(chains.front().size() == Go::Board::BOARD_SIZE * Go::Board::BOARD_SIZE);

    std::size_t visited = 0;
    chains.front().forEachPoint([&](const Go::Point & point)
    {
        REQUIRE(!point.getStone().has_value());
        ++visited;
    });
    REQUIRE(visited == chains.front().size());
}

TEST_CASE("Module consumers can instantiate Player with their own UI", "[modules]")
{
    Go::Player<TestUI> one {"One"};
    Go::Player<TestUI> two {"Two"};
    Go::GameController controller {one, two};

    REQUIRE(&one.getGameBoard() == &two.getGameBoard());
    one.chooseName();
    REQUIRE(one.getName() == "Module player");
    REQUIRE(one.chooseStoneColor() == Go::StoneColor::BLACK);
    one.addToCaptured(2);
    REQUIRE(one.calculateScore() == 2);
    REQUIRE(one.hasStones());

    one.placeStoneAt({0, 0});
    REQUIRE(one.getGameBoard().getStoneAt({0, 0})->getColor() == Go::StoneColor::BLACK);
}

TEST_CASE("Module stream operators are found by dependent template calls", "[modules]")
{
    Go::Point point;
    point.coordinates = {2, 3};
    point.playStone(Go::Stone {Go::StoneColor::WHITE});

    Go::Logger logger {Go::LogLevel::kLow};
    std::ostringstream out;
    logger.log(Go::LogLevel::kLow, out, point, " ", point.coordinates, " ", point.getStone());

    REQUIRE(out.str() == "LOG(1): Point: {[2,3], Stone: {White}} [2,3] Stone: {White}\n");
}
