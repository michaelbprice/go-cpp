#ifndef INCL_STONE_FWD_HPP__
#define INCL_STONE_FWD_HPP__

namespace Go {

class Stone;
enum class StoneColor : unsigned char;

} // namesapce Go

namespace std {

template <> struct hash<Go::StoneColor>;

} // namespace std

#endif /* end of include guard: INCL_STONE_FWD_HPP__ */

