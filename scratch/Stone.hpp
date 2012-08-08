#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class vector { public: vector (int, const T&);};

///////////////////////////////////////////////////////////////////////////////

namespace Go
{
	
class Stone final
{
 public:

 	enum class Color : char
 	{
 		BLACK,
 		WHITE
 	};

 private:
 	Color m_color;

 public:
 	Stone (Color color) : m_color(color) { }
 	~Stone () = default;

 	Stone(const Stone&) = delete;
 	Stone & operator= (const Stone&) = delete;

 	Stone(Stone && other) = default;
 	Stone & operator= (Stone && other) = default;

};

using Stones = vector<Stone>;

}

#endif /* end of include guard: INCL_STONE_HPP__ */