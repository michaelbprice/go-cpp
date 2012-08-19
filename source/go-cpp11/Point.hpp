#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <functional>
#include <iosfwd>
#include <memory>
#include <unordered_set>
#include "Stone.fwd.hpp"

namespace Go {

struct PointCoords final
{
    size_t row = 0;
    size_t column = 0;
};

class Point final
{
 friend ostream & operator<< (ostream & out, const Point & point);

 private:
    std::unique_ptr<Stone> m_stone = nullptr;

 public:
    PointCoords coordinates;

    StoneColor getStoneColor () const;

    void playStone (std::unique_ptr<Stone> stone);

    bool canPlayStone () const;

    void removeStone ();
};

using PointSet = std::unordered_set<Point*>;
using ConstPointSet = std::unordered_set<const Point*>;

using std::function<void(const Point &)> = PointVisitorFn;

} // namespace Go

ostream & operator<< (ostream & out, const Go::PointCoords & coords);
ostream & operator<< (ostream & out, const Go::Point & point);


#endif /* end of include guard: INCL_POINT_HPP__ */
