#ifndef INCL_PLAYER_FWD_HPP__
#define INCL_PLAYER_FWD_HPP__

#include <functional>

class IPlayer;
using PlayerPair = std::pair<std::reference_wrapper<IPlayer>, std::reference_wrapper<IPlayer>>;

#endif /* end of include guard: INCL_PLAYER_FWD_HPP__ */
