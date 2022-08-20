#ifndef INCL_STD_FWD_HPP__
#define INCL_STD_FWD_HPP__

#include "Stone.fwd.hpp"

namespace std {

template <> struct hash<Go::StoneColor>
{
    size_t operator() (const Go::StoneColor & c) const
    {
        return hash<char>()(static_cast<char>(c));
    }
};

} // namespace std

#endif /* end of include guard: INCL_STD_FWD_HPP__ */

