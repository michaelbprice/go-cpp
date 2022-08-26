#include <concepts>

#include <catch2/catch_test_macros.hpp>
#include "Stone.hpp"

using namespace Go;

TEST_CASE("Black/White are opposite and NONE is opposite neither", "[stone-color]") {
    REQUIRE(getOpposingColor(StoneColor::BLACK) == StoneColor::WHITE);
    REQUIRE(getOpposingColor(StoneColor::WHITE) == StoneColor::BLACK);
    REQUIRE(getOpposingColor(StoneColor::NONE) == StoneColor::NONE);
}

TEST_CASE("Stones are movable and non-copyable", "[stone-specials]") {
    STATIC_REQUIRE(std::movable<Stone>);
    STATIC_REQUIRE(!std::copyable<Stone>);
}

TEST_CASE("Stones require a valid StoneColor on construction", "[stone-ctors]") {
    STATIC_REQUIRE(!std::constructible_from<Stone>);
    STATIC_REQUIRE(std::constructible_from<Stone, StoneColor>);
    REQUIRE_NOTHROW(Stone{StoneColor::BLACK});
    REQUIRE_NOTHROW(Stone{StoneColor::WHITE});
}

TEST_CASE("Stone color is accessible and immutable", "[stone-confirm]") {
    Stone b{StoneColor::BLACK};
    Stone w{StoneColor::WHITE};
    REQUIRE(b.getColor() == StoneColor::BLACK);
    REQUIRE(w.getColor() == StoneColor::WHITE);

    STATIC_REQUIRE(!std::is_reference_v<decltype(b.getColor())>);
}