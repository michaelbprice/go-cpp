#ifndef INCL_STONE_FWD_HPP__
#define INCL_STONE_FWD_HPP__

#include <memory>
#include <vector>

namespace Go {

class Stone;
enum class StoneColor : unsigned char;

using Stones = std::vector<std::unique_ptr<Stone>>;

} // namesapce Go

#endif /* end of include guard: INCL_STONE_FWD_HPP__ */
