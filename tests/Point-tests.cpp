#include <concepts>

#include <catch2/catch_test_macros.hpp>
#include "Point.hpp"
#include "Stone.hpp"

using namespace Go;

TEST_CASE("PointCoords are reasonable PODs", "[pointcoords-pods]") {
    STATIC_REQUIRE(std::constructible_from<PointCoords, size_t, size_t>);

    PointCoords defaultCoords;
    REQUIRE(defaultCoords.row == 0);
    REQUIRE(defaultCoords.column == 0);
}

TEST_CASE("Point constructors", "[point-ctors]") {
    STATIC_REQUIRE(std::constructible_from<Point>);

    Point defaultPoint;
    REQUIRE(defaultPoint.coordinates == PointCoords{0, 0});
}

TEST_CASE("A default Point can play a stone", "[point-default-canplay]") {
    Point defaultPoint;
    REQUIRE(defaultPoint.canPlayStone() == true);
}

TEST_CASE("A Point can have a stone played only if there is no existing stone", "[point-single-stone]") {
    Point defaultPoint;
    REQUIRE(defaultPoint.canPlayStone() == true);

    defaultPoint.playStone(std::make_unique<Stone>(StoneColor::WHITE));
    REQUIRE(defaultPoint.canPlayStone() == false);

    // TODO: This is broken. Nothing prevents this scenario other than a user checking `canPlayStone()`
    //REQUIRE_THROWS(defaultPoint.playStone(std::make_unique<Stone>(StoneColor::BLACK)));

    defaultPoint.removeStone();
    REQUIRE(defaultPoint.canPlayStone() == true);
}

TEST_CASE("Observing the Stone color on a Point", "[point-stonecolor]") {
    Point defaultPoint;

    REQUIRE(defaultPoint.getStoneColor() == StoneColor::NONE);

    defaultPoint.playStone(std::make_unique<Stone>(StoneColor::WHITE));
    REQUIRE(defaultPoint.getStoneColor() == StoneColor::WHITE);

    defaultPoint.removeStone();
    defaultPoint.playStone(std::make_unique<Stone>(StoneColor::BLACK));
    REQUIRE(defaultPoint.getStoneColor() == StoneColor::BLACK);
}