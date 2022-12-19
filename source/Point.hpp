#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <functional>
#include <iosfwd>
#include <memory>
#include <optional>
#include <unordered_set>

#include "Point.fwd.hpp"
#include "Stone.hpp"

std::ostream & operator<< (std::ostream & out, const Go::PointCoords & coords);
std::ostream & operator<< (std::ostream & out, const Go::Point & point);

namespace Go {

struct PointCoords final
{
    PointCoords () = default;
    PointCoords (size_t r, size_t c) : row(r), column(c) { }

    bool operator==(const PointCoords&) const = default;

    size_t row = 0;
    size_t column = 0;
};

class Point final
{
 friend std::ostream & ::operator<< (std::ostream & out, const Go::Point & point);

 private:
    std::optional<Stone> m_stone;

 public:
    PointCoords coordinates;

    const std::optional<Stone> & getStone() const;

    void playStone (const Stone & stone);

    bool canPlayStone () const;

    void removeStone ();
};

//using PointSet = std::unordered_set<Point*>;
//using ConstPointSet = std::unordered_set<const Point*>;

//using PointVisitorFn = std::function<void(const Point &)>;

} // namespace Go



#endif /* end of include guard: INCL_POINT_HPP__ */
