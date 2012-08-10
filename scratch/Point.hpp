#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <memory>
#include "Stone.hpp"

namespace Go
{

class Point final
{
 private:
    std::unique_ptr<Stone> m_stone = nullptr;

 public:
    Stone::Color getStoneColor () const;

    void playStone (std::unique_ptr<Stone> stone);

    bool canPlayStone () const;
};

}

#endif /* end of include guard: INCL_POINT_HPP__ */
